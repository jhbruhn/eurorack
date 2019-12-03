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
float pan[NUM_CHANNELS];

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
      int16_t panRead = AnalogInputs::Read(i + NUM_CHANNELS);
      pan[i] = (panRead / 1024.0) * M_PI_2; // convert 0 to 90° to radians
    }

    Dac1::Write((uint16_t)((volume[0]) * sin(pan[0])) << 2, 0);
    Dac1::Write((uint16_t)((volume[0]) * cos(pan[0])) << 2, 1);
    Dac2::Write((uint16_t)((volume[1]) * sin(pan[1])) << 2, 0);
    Dac2::Write((uint16_t)((volume[1]) * cos(pan[1])) << 2, 1);
    Dac3::Write((uint16_t)((volume[2]) * sin(pan[2])) << 2, 0);
    Dac3::Write((uint16_t)((volume[2]) * cos(pan[2])) << 2, 1);
    Dac4::Write((uint16_t)((volume[3]) * sin(pan[3])) << 2, 0);
    Dac4::Write((uint16_t)((volume[3]) * cos(pan[3])) << 2, 1);
  }
}
