#include <avr/pgmspace.h>
#include <math.h>

#include "avrlib/adc.h"
#include "avrlib/avrlib.h"
#include "avrlib/devices/mcp492x.h"
#include "avrlib/gpio.h"
#include "avrlib/spi.h"
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

typedef AdcInputScanner AnalogInputs;

#define NUM_CHANNELS 4

uint16_t volume[NUM_CHANNELS];
uint16_t pan[NUM_CHANNELS];

int main(void)
{
  Dac1::Init();
  Dac2::Init();
  Dac3::Init();
  Dac4::Init();

  AnalogInputs::Init();
  AnalogInputs::set_num_inputs(8);

  while (true) {
    ResetWatchdog();

    AnalogInputs::Scan();
    for (int i = 0; i < NUM_CHANNELS; i++) {
      volume[i] = pgm_read_word_near(lut_res_linear_to_exp + AnalogInputs::Read(i));
      if(volume[i] < 7) // some ADSRs dont seem to close completely, lets gate very low voltages...
        volume[i] = 0;
      pan[i] = AnalogInputs::Read(i + NUM_CHANNELS);
    }

    Dac1::Write(((uint32_t)(volume[0]) * pgm_read_word(lut_res_left_sin_pan  + pan[0])) >> 8, 0);
    Dac1::Write(((uint32_t)(volume[0]) * pgm_read_word(lut_res_right_cos_pan + pan[0])) >> 8, 1);
    Dac2::Write(((uint32_t)(volume[1]) * pgm_read_word(lut_res_left_sin_pan  + pan[1])) >> 8, 0);
    Dac2::Write(((uint32_t)(volume[1]) * pgm_read_word(lut_res_right_cos_pan + pan[1])) >> 8, 1);
    Dac3::Write(((uint32_t)(volume[2]) * pgm_read_word(lut_res_left_sin_pan  + pan[2])) >> 8, 0);
    Dac3::Write(((uint32_t)(volume[2]) * pgm_read_word(lut_res_right_cos_pan + pan[2])) >> 8, 1);
    Dac4::Write(((uint32_t)(volume[3]) * pgm_read_word(lut_res_left_sin_pan  + pan[3])) >> 8, 0);
    Dac4::Write(((uint32_t)(volume[3]) * pgm_read_word(lut_res_right_cos_pan + pan[3])) >> 8, 1);
  }
}
