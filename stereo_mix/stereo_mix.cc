#include <avr/pgmspace.h>

#include "avrlib/adc.h"
#include "avrlib/avrlib.h"
#include "avrlib/boot.h"
#include "avrlib/deprecated/devices/input_array.h"
#include "avrlib/devices/mcp492x.h"
#include "avrlib/gpio.h"
#include "avrlib/spi.h"
#include "avrlib/watchdog_timer.h"
#include "stereo_mix/resources.h"
#include "avrlib/time.h"

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

typedef AdcInputScanner AnalogInputs;
typedef InputArray<AnalogInputs, 8, 4> Pots;

Pots pots;

#define NUM_CHANNELS 4

uint16_t volume[NUM_CHANNELS];
uint16_t pan[NUM_CHANNELS];

int main(void)
{
  Boot(true);
  Dac1::Init();
  Dac2::Init();
  Dac3::Init();
  Dac4::Init();

  pots.Init();
  //Adc::set_reference(ADC_DEFAULT);
  //Adc::set_alignment(ADC_LEFT_ALIGNED);
  AnalogInputs::set_num_inputs(8);
  while (true) {
    ResetWatchdog();

    Pots::Event event = pots.Read();
    if (event.event != EVENT_NONE) {
      if (event.id < NUM_CHANNELS) {    // volume pots
        volume[event.id] = event.value; //pgm_read_word_near(lut_res_linear_to_exp + (event.value >> 6));
      } else {                          // pan pots
        pan[event.id - NUM_CHANNELS] = event.value >> 6;
      }
    } else {
      //volume[1] = 4095;
    }
    AnalogInputs::Scan();
    /*AnalogInputs.Scan();
    for (int i = 0; i < NUM_CHANNELS; i++) {
      volume[i] = pgm_read_word_near(lut_res_linear_to_exp + (AnalogInputs.Read8(i) << 2));
      if (volume[i] < 7) // some ADSRs dont seem to close completely, lets gate very low voltages...
        volume[i] = 0;
      pan[i] = AnalogInputs.Read8(i + NUM_CHANNELS) << 2;
    }*/

    Dac1::Write(4095, 0);
    Dac1::Write(4095, 1);
    //Dac1::Write(((uint32_t)(volume[0]) * /*pgm_read_word_near(lut_res_left_sin_pan + */ (pan[0])) >> 8, 0);
    //Dac1::Write(((uint32_t)(volume[0]) * /*pgm_read_word_near(lut_res_right_cos_pan +*/ (1024 - pan[0])) >> 8, 1);
    Dac2::Write(volume[1] >> 4, 0);
    Dac2::Write(volume[1] >> 4, 1);
    //Dac2::Write(((uint32_t)(volume[1]) * /*pgm_read_word_near(lut_res_left_sin_pan + */ (pan[1])) >> 8, 0);
    //Dac2::Write(((uint32_t)(volume[1]) * /*pgm_read_word_near(lut_res_right_cos_pan +*/ (1024 - pan[1])) >> 8, 1);
    //Dac3::Write(((uint32_t)(volume[2]) * /*pgm_read_word_near(lut_res_left_sin_pan + */ (pan[2])) >> 8, 0);
    //Dac3::Write(((uint32_t)(volume[2]) * /*pgm_read_word_near(lut_res_right_cos_pan +*/ (1024 - pan[2])) >> 8, 1);
    //Dac4::Write(((uint32_t)(volume[3]) * /*pgm_read_word_near(lut_res_left_sin_pan + */ (pan[3])) >> 8, 0);
    //Dac4::Write(((uint32_t)(volume[3]) * /*pgm_read_word_near(lut_res_right_cos_pan +*/ (1024 - pan[3])) >> 8, 1);
  }
}

TIMER_0_TICK {
  TickSystemClock();
}

