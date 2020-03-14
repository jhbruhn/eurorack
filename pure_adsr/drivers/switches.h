// Copyright 2016 Emilie Gillet.
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
// Driver for the 2 switches.

#ifndef PLAITS_DRIVERS_SWITCHES_H_
#define PLAITS_DRIVERS_SWITCHES_H_

#include "avrlib/gpio.h"

namespace pure_adsr {

template <typename DigitalInput>
class Switch {
  public:
  Switch() {}
  ~Switch() {}

  void Init() { DigitalInput::Init(); }
  void Debounce()
  {
    switch_state_ = (switch_state_ << 1) | Switch::pressed_immediate();
  }

  inline bool released()
  {
    return switch_state_ == 0x7f;
  }

  inline bool just_pressed()
  {
    return switch_state_ == 0x80;
  }

  inline bool pressed()
  {
    return switch_state_ == 0x00;
  }

  inline bool pressed_immediate()
  {
    return DigitalInput::Read();
  }

  private:
  uint8_t switch_state_;

  DISALLOW_COPY_AND_ASSIGN(Switch);
};

} // namespace plaits

#endif // PLAITS_DRIVERS_SWITCHES_H_
