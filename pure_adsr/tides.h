// Copyright 2013 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Multistage envelope.

#ifndef PEAKS_MODULATIONS_TIDES_H_
#define PEAKS_MODULATIONS_TIDES_H_

#include "pure_adsr/gate_processor.h"
#include "pure_adsr/hysteresis_quantizer.h"
#include "pure_adsr/multistage_envelope.h"
#include <avrlib/avrlib.h>
#include <stddef.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))

namespace pure_adsr {

class Tides {
  public:
  Tides() {}
  ~Tides() {}

  void Init();
  void Process(const GateFlags* gate_flags, int16_t* out, size_t size);

  void Configure(uint16_t* parameter, ControlMode control_mode)
  {
    uint16_t param = parameter[2];
    uint16_t hold_high_length = 0;
    uint16_t hold_low_length = 0;
    if(param > 32768) {
      hold_high_length = (param - 32768) >> 0;
    } else {
      hold_low_length = (32768 - param) >> 0;
    }

    set_ad_f_loop(parameter[0], parameter[1], hold_high_length, hold_low_length);
    uint8_t waveform_mode = quant.Process(parameter[3] / 65536.0f, 5);

    switch (waveform_mode) {
    case 0:
      shape_[0] = ENV_SHAPE_QUARTIC;
      shape_[2] = ENV_SHAPE_EXPONENTIAL;
      break;
    case 1:
      shape_[0] = ENV_SHAPE_QUARTIC;
      shape_[2] = ENV_SHAPE_QUARTIC;
      break;
    case 2:
      shape_[0] = ENV_SHAPE_LINEAR;
      shape_[2] = ENV_SHAPE_LINEAR;
      break;
    case 3:
      shape_[0] = ENV_SHAPE_EXPONENTIAL;
      shape_[2] = ENV_SHAPE_EXPONENTIAL;
      break;
    case 4:
      shape_[0] = ENV_SHAPE_EXPONENTIAL;
      shape_[2] = ENV_SHAPE_QUARTIC;
      break;
    }

    if (segment_ > num_segments_) {
      segment_ = 0;
      phase_ = 0;
      value_ = 0;
    }
  }

  inline void set_time(uint16_t segment, uint16_t time)
  {
    time_[segment] = time;
  }

  inline void set_level(uint16_t segment, int16_t level)
  {
    level_[segment] = level;
  }

  inline void set_num_segments(uint16_t num_segments)
  {
    num_segments_ = num_segments;
  }

  inline void set_sustain_point(uint16_t sustain_point)
  {
    sustain_point_ = sustain_point;
  }

  inline void set_adsr(
      uint16_t attack,
      uint16_t decay,
      uint16_t sustain,
      uint16_t release)
  {
    num_segments_ = 3;
    sustain_point_ = 2;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = sustain;
    level_[3] = 0;

    time_[0] = attack;
    time_[1] = decay;
    time_[2] = release;

    shape_[0] = ENV_SHAPE_QUARTIC;
    shape_[1] = ENV_SHAPE_EXPONENTIAL;
    shape_[2] = ENV_SHAPE_EXPONENTIAL;

    loop_start_ = loop_end_ = 0;
  }

  inline void set_ad(uint16_t attack, uint16_t decay)
  {
    num_segments_ = 2;
    sustain_point_ = 0;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = 0;

    time_[0] = attack;
    time_[1] = decay;

    shape_[0] = ENV_SHAPE_EXPONENTIAL;
    shape_[1] = ENV_SHAPE_EXPONENTIAL;

    loop_start_ = loop_end_ = 0;
  }

  inline void set_adr(
      uint16_t attack,
      uint16_t decay,
      uint16_t sustain,
      uint16_t release)
  {
    num_segments_ = 3;
    sustain_point_ = 0;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = sustain;
    level_[3] = 0;

    time_[0] = attack;
    time_[1] = decay;
    time_[2] = release;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;
    shape_[2] = ENV_SHAPE_LINEAR;

    loop_start_ = loop_end_ = 0;
  }

  inline void set_ar(uint16_t attack, uint16_t decay)
  {
    num_segments_ = 2;
    sustain_point_ = 1;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = 0;

    time_[0] = attack;
    time_[1] = decay;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;

    loop_start_ = loop_end_ = 0;
  }

  inline void set_adsar(
      uint16_t attack,
      uint16_t decay,
      uint16_t sustain,
      uint16_t release)
  {
    num_segments_ = 4;
    sustain_point_ = 2;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = sustain;
    level_[3] = 32767;
    level_[4] = 0;

    time_[0] = attack;
    time_[1] = decay;
    time_[2] = attack;
    time_[3] = release;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;
    shape_[2] = ENV_SHAPE_LINEAR;
    shape_[3] = ENV_SHAPE_LINEAR;

    loop_start_ = loop_end_ = 0;
  }

  inline void set_adar(
      uint16_t attack,
      uint16_t decay,
      uint16_t sustain,
      uint16_t release)
  {
    num_segments_ = 4;
    sustain_point_ = 0;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = sustain;
    level_[3] = 32767;
    level_[4] = 0;

    time_[0] = attack;
    time_[1] = decay;
    time_[2] = attack;
    time_[3] = release;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;
    shape_[2] = ENV_SHAPE_LINEAR;
    shape_[3] = ENV_SHAPE_LINEAR;

    loop_start_ = loop_end_ = 0;
  }

  inline void set_ad_loop(uint16_t attack, uint16_t decay)
  {
    num_segments_ = 2;
    sustain_point_ = 0;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = 0;

    time_[0] = attack;
    time_[1] = decay;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;

    loop_start_ = 0;
    loop_end_ = 2;
  }

  inline void set_ad_f_loop(uint16_t attack, uint16_t decay, uint16_t sustain, uint16_t silence)
  {
    num_segments_ = 4;
    sustain_point_ = 0;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = 32767;
    level_[3] = 0;
    level_[4] = 0;

    time_[0] = attack;
    time_[1] = sustain;
    time_[2] = decay;
    time_[3] = silence;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;
    shape_[2] = ENV_SHAPE_LINEAR;
    shape_[3] = ENV_SHAPE_LINEAR;

    loop_start_ = 0;
    loop_end_ = 4;
  }

  inline void set_adr_loop(
      uint16_t attack,
      uint16_t decay,
      uint16_t sustain,
      uint16_t release)
  {
    num_segments_ = 3;
    sustain_point_ = 0;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = sustain;
    level_[3] = 0;

    time_[0] = attack;
    time_[1] = decay;
    time_[2] = release;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;
    shape_[2] = ENV_SHAPE_LINEAR;

    loop_start_ = 0;
    loop_end_ = 3;
  }

  inline void set_adar_loop(
      uint16_t attack,
      uint16_t decay,
      uint16_t sustain,
      uint16_t release)
  {
    num_segments_ = 4;
    sustain_point_ = 0;

    level_[0] = 0;
    level_[1] = 32767;
    level_[2] = sustain;
    level_[3] = 32767;
    level_[4] = 0;

    time_[0] = attack;
    time_[1] = decay;
    time_[2] = attack;
    time_[3] = release;

    shape_[0] = ENV_SHAPE_LINEAR;
    shape_[1] = ENV_SHAPE_LINEAR;
    shape_[2] = ENV_SHAPE_LINEAR;
    shape_[3] = ENV_SHAPE_LINEAR;

    loop_start_ = 0;
    loop_end_ = 4;
  }

  inline void set_hard_reset(bool hard_reset)
  {
    hard_reset_ = hard_reset;
  }

  private:
  int16_t level_[kMaxNumSegments];
  uint16_t time_[kMaxNumSegments];
  EnvelopeShape shape_[kMaxNumSegments];

  int16_t segment_;
  int16_t start_value_;
  int16_t value_;

  uint32_t phase_;
  uint32_t phase_increment_;

  uint16_t num_segments_;
  uint16_t sustain_point_;
  uint16_t loop_start_;
  uint16_t loop_end_;
  uint16_t smoothness_;
  bool hard_reset_;
  HysteresisQuantizer quant;
  DISALLOW_COPY_AND_ASSIGN(Tides);
};

} // namespace peaks

#endif // PEAKS_MODULATIONS_MULTISTAGE_ENVELOPE_H_
