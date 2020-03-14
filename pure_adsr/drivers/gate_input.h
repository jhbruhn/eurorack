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
// Driver for the 2 gate inputs.

#ifndef PEAKS_DRIVERS_GATE_INPUT_H_
#define PEAKS_DRIVERS_GATE_INPUT_H_

#include "avrlib/gpio.h"

namespace pure_adsr {

enum GateInputState {
  INPUT_1_GATE = 0x01,
  INPUT_1_RAISING = 0x02,
  INPUT_1_FALLING = 0x04
};

template<typename DigitalInput>
class GateInput {
 public:
  GateInput() { }
  ~GateInput() { }

  void Init() {
    DigitalInput::Init();
  }

  uint32_t Read() {
    uint32_t result = 0;
    result |= !DigitalInput::Read();
    return result;
  }

  inline bool ReadInput1() {
    return !DigitalInput::Read();
  }

 private:
  uint8_t ReadBits();

  DISALLOW_COPY_AND_ASSIGN(GateInput);
};

}  // namespace peaks

#endif  // PEAKS_DRIVERS_GATE_INPUT_H_

