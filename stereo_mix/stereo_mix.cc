#include "avrlib/adc.h"
#include "avrlib/avrlib.h"
#include "avrlib/boot.h"
#include "avrlib/devices/mcp492x.h"
#include "avrlib/gpio.h"
#include "avrlib/spi.h"
#include "avrlib/time.h"
#include "avrlib/watchdog_timer.h"
#include "stereo_mix/resources.h"

#define degToRad(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)

using namespace avrlib;
using namespace stereo_mix;

typedef SpiMaster<NumberedGpio<0>, MSB_FIRST, 2> dac1Spi;
typedef Dac<dac1Spi, BUFFERED_REFERENCE, 1> Dac1;
typedef SpiMaster<NumberedGpio<1>, MSB_FIRST, 2> dac2Spi;
typedef Dac<dac2Spi, BUFFERED_REFERENCE, 1> Dac2;
typedef SpiMaster<NumberedGpio<2>, MSB_FIRST, 2> dac3Spi;
typedef Dac<dac3Spi, BUFFERED_REFERENCE, 1> Dac3;
typedef SpiMaster<NumberedGpio<3>, MSB_FIRST, 2> dac4Spi;
typedef Dac<dac4Spi, BUFFERED_REFERENCE, 1> Dac4;

typedef SpiMaster<NumberedGpio<4>, MSB_FIRST, 2> oDac1Spi;
typedef Dac<oDac1Spi, BUFFERED_REFERENCE, 0> oDac1;
typedef SpiMaster<NumberedGpio<5>, MSB_FIRST, 2> oDac2Spi;
typedef Dac<oDac2Spi, BUFFERED_REFERENCE, 0> oDac2;
typedef SpiMaster<NumberedGpio<6>, MSB_FIRST, 2> oDac3Spi;
typedef Dac<oDac3Spi, BUFFERED_REFERENCE, 0> oDac3;
typedef SpiMaster<NumberedGpio<7>, MSB_FIRST, 2> oDac4Spi;
typedef Dac<oDac4Spi, BUFFERED_REFERENCE, 0> oDac4;

typedef AdcInputScanner AnalogInputs;

#define NUM_CHANNELS 4

uint32_t volume[NUM_CHANNELS];
uint16_t pan[NUM_CHANNELS * 2];

int main(void)
{
  Boot(true);
  Dac1::Init();
  Dac2::Init();
  Dac3::Init();
  Dac4::Init();

  oDac1::Init();
  oDac2::Init();
  oDac3::Init();
  oDac4::Init();

  AnalogInputs::Init();

  AnalogInputs::set_num_inputs(8);

#define WRITE(DAC, ODAC, N)                                    \
  DAC::Write((volume[N] * pan[N * NUM_CHANNELS]) >> 8, 0);     \
  ODAC::Write((volume[N] * pan[N * NUM_CHANNELS]) >> 8, 0);    \
  DAC::Write((volume[N] * pan[N * NUM_CHANNELS + 1]) >> 8, 1); \
  ODAC::Write((volume[N] * pan[N * NUM_CHANNELS + 1]) >> 8, 1);

  while (true) {
    ResetWatchdog();

    int i = AnalogInputs::current_pin() % NUM_CHANNELS;
    volume[i] = pgm_read_word_near(lut_res_linear_to_exp + (AnalogInputs::Read(i) >> 1)) << 1;
    pan[i * NUM_CHANNELS] = pgm_read_word(lut_res_left_sin_pan + (AnalogInputs::Read(i + NUM_CHANNELS) >> 1)) << 1;
    pan[i * NUM_CHANNELS + 1] = pgm_read_word(lut_res_right_cos_pan + (AnalogInputs::Read(i + NUM_CHANNELS) >> 1)) << 1;

    switch (i) {
    case 0:
      WRITE(Dac1, oDac1, i);
      break;
    case 1:
      WRITE(Dac2, oDac2, i);
      break;
    case 2:
      WRITE(Dac3, oDac3, i);
      break;
    case 3:
      WRITE(Dac4, oDac4, i);
      break;
    }
    AnalogInputs::Scan();
  }
}

TIMER_0_TICK
{
  TickSystemClock();
}
