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

#include "pure_adsr/tides.h"

#include "pure_adsr/resources.h"

namespace pure_adsr {

void Tides::Init()
{
  set_adsr(0, 8192, 16384, 32767);
  segment_ = num_segments_;
  phase_ = 0;
  phase_increment_ = 0;
  start_value_ = 0;
  value_ = 0;
  hard_reset_ = false;
  quant.Init();
}

void Tides::Process(
    const GateFlags* gate_flags, int16_t* out, size_t size)
{
  while (size--) {
    GateFlags gate_flag = *gate_flags++;
    if (gate_flag & GATE_FLAG_RISING) {
      start_value_ = (segment_ == num_segments_ || hard_reset_)
          ? level_[0]
          : value_;
      segment_ = 0;
      phase_ = 0;
    } else if (gate_flag & GATE_FLAG_FALLING && sustain_point_) {
      start_value_ = value_;
      segment_ = sustain_point_;
      phase_ = 0;
    } else if (phase_ < phase_increment_) {
      start_value_ = level_[segment_ + 1];
      ++segment_;
      phase_ = 0;
      if (segment_ == loop_end_) {
        segment_ = loop_start_;
      }
    }

    bool done = segment_ == num_segments_;
    bool sustained = sustain_point_ && segment_ == sustain_point_ && gate_flag & GATE_FLAG_HIGH;

    phase_increment_ = sustained || done ? 0 : pgm_read_dword(lut_res_env_increments_slow + (time_[segment_] >> 8));

    int32_t a = start_value_;
    int32_t b = level_[segment_ + 1];

    uint32_t x = pgm_read_word(lookup_table_table[LUT_RES_ENV_LINEAR + shape_[segment_]] + (phase_ >> 24));
    uint32_t y = pgm_read_word(lookup_table_table[LUT_RES_ENV_LINEAR + shape_[segment_]] + (phase_ >> 24) + 1);
    uint16_t t = x + ((y - x) * static_cast<uint32_t>((phase_ >> 8) & 0xffff) >> 16);

    value_ = a + ((b - a) * (t >> 1) >> 15);

    phase_ += phase_increment_;
    *out++ = value_;
  }
}

} // namespace peaks
