#include "avrlib/adc.h"
#include "avrlib/avrlib.h"
#include "avrlib/boot.h"
#include "avrlib/devices/mcp492x.h"
#include "avrlib/gpio.h"
#include "avrlib/spi.h"
#include "avrlib/time.h"
#include "avrlib/timer.h"
#include "avrlib/watchdog_timer.h"
#include "pure_adsr/drivers/gate_input.h"
#include "pure_adsr/drivers/switches.h"
#include "pure_adsr/gate_processor.h"
#include "pure_adsr/io_buffer.h"
#include "pure_adsr/mini_sequencer.h"
#include "pure_adsr/multistage_envelope.h"
#include "pure_adsr/tides.h"

using namespace avrlib;
using namespace pure_adsr;

typedef enum {
  MODE_ADSR,
  MODE_SEQ,
  MODE_TIDES
} Mode;

typedef SpiMaster<Gpio<PortB, 2>, MSB_FIRST, 2> dac1Spi;
typedef Dac<dac1Spi, UNBUFFERED_REFERENCE, 1> dac;

GateInput<DigitalInput<Gpio<PortD, 2>>> gate_input;
GateFlags gate_flags;

DigitalInput<Gpio<PortD, 6>> switchIn0;
DigitalInput<Gpio<PortD, 7>> switchIn1;

Switch<DigitalInput<Gpio<PortD, 3>>> button_input;

typedef AdcInputScanner AnalogInputs;

MultistageEnvelope envelope;
MiniSequencer sequencer;
Tides tides;

IOBuffer io_buffer;
int16_t output_buffer[kBlockSize];
const size_t kNumPots = 4;

uint16_t pot_values[kNumPots];

Mode mode;

void Process(IOBuffer::Block* block, size_t size)
{
  for (size_t i = 0; i < kNumPots; i++) {
    uint16_t read_value = AnalogInputs::Read(kNumPots - 1 - i) << 6;
    if (read_value != pot_values[i]) { // TODO: apply filtering
      pot_values[i] = read_value;
      envelope.Configure(pot_values, CONTROL_MODE_FULL);
      sequencer.Configure(pot_values, CONTROL_MODE_FULL);
      tides.Configure(pot_values, CONTROL_MODE_FULL);
    }
  }

  for (size_t i = 0; i < kNumChannels; ++i) {

    switch (mode) {
    case MODE_ADSR:
      envelope.Process(block->input[i], output_buffer, size);
      break;
    case MODE_SEQ:
      sequencer.Process(block->input[i], output_buffer, size);
      break;
    case MODE_TIDES:
      tides.Process(block->input[i], output_buffer, size);
      break;
    }

    for (size_t j = 0; j < size; ++j) {
      block->output[i][j] = output_buffer[j] >> 3;
    }
  }
}

void Init()
{

  Timer<2>::set_prescaler(1); // 9.765 kHz??????
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);

  dac::Init();
  AnalogInputs::Init();

  AnalogInputs::set_num_inputs(4);

  gate_input.Init();
  button_input.Init();
  switchIn0.Init();
  switchIn1.Init();

  io_buffer.Init();
  envelope.Init();
  sequencer.Init();

  uint16_t pots[4];
  for (size_t i = 0; i < 4; i++)
    pots[4 - (i + 1)] = AnalogInputs::Read8(i) << 8;
  envelope.Configure(pots, CONTROL_MODE_FULL);
  sequencer.Configure(pots, CONTROL_MODE_FULL);
  tides.Configure(pots, CONTROL_MODE_FULL);

  Timer<2>::Start();
}

int main(void)
{
  Boot(true);

  Init();

  while (true) {
    ResetWatchdog();
    io_buffer.Process(&Process);
    AnalogInputs::Scan();
  }
}

TIMER_0_TICK
{
  TickSystemClock();
  button_input.Debounce();
  uint8_t mode_value = switchIn1.Read() << 1 | switchIn0.Read();
  switch (mode_value) {
  case 0:
    mode = MODE_SEQ;
    break;
  case 1:
    mode = MODE_TIDES;
    break;
  case 2:
    mode = MODE_ADSR;
    break;
  }
}

TIMER_2_TICK
{
  static uint8_t clock_divider_midi = 0;

  --clock_divider_midi;
  if (!clock_divider_midi) {
    uint32_t gate_inputs = gate_input.Read();

    if (mode == MODE_ADSR || mode == MODE_SEQ)
      gate_inputs |= button_input.pressed();

    IOBuffer::Slice slice = io_buffer.NextSlice(1);
    for (size_t i = 0; i < kNumChannels; ++i) {
      gate_flags = ExtractGateFlags(
          gate_flags,
          gate_inputs & (1 << i));
      dac::Write(slice.block->output[i][slice.frame_index]);
      slice.block->input[i][slice.frame_index] = gate_flags;
    }
    clock_divider_midi = 16;
  }
}
