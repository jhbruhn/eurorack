// Copyright 2015 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//         modified for ints by Jan-Henrik Bruhn (hi@jhbruhn.de)
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
// Handles the "hold button to tweak a hidden parameter" behaviour of pots.
// A pot can be in 4 states:
// - POT_STATE_TRACKING: the main parameter tracks the position of the pot.
// - POT_STATE_LOCKING: the main parameter no longer tracks the position of
//   the pot. We wait for the pot to move further from its original position
//   to start modifying the hidden parameter.
// - POT_STATE_HIDDEN_PARAMETER: the hidden parameter tracks the position of
//   the pot.
// - POT_STATE_CATCHING_UP: the pot adjusts the main parameter in a relative
//   way, until the position of the pot and the value of the parameter match
//   again.

#pragma once

#include "stmlib/stmlib.h"
#include "stmlib/dsp/dsp.h"


enum PotState {
  POT_STATE_TRACKING,
  POT_STATE_LOCKING,
  POT_STATE_HIDDEN_PARAMETER,
  POT_STATE_CATCHING_UP
};

class PotController {
 public:
  PotController() { }
  ~PotController() { }

  inline void Init(
      uint16_t* main_parameter,
      uint16_t* hidden_parameter // this pot controller always works on values between 0 and 65535
      ) {
    state_ = POT_STATE_TRACKING;
    was_catching_up_ = false;

    main_parameter_ = main_parameter;
    hidden_parameter_ = hidden_parameter;

    value_ = 0;
    stored_value_ = 0;
    previous_value_ = 0;
  }

  inline void Lock() {
    if (state_ == POT_STATE_LOCKING || state_ == POT_STATE_HIDDEN_PARAMETER) {
      return;
    }
    if (hidden_parameter_) {
      was_catching_up_ = state_ == POT_STATE_CATCHING_UP;
      state_ = POT_STATE_LOCKING;
    }
  }


  inline bool editing_hidden_parameter() const {
    return state_ == POT_STATE_HIDDEN_PARAMETER;
  }

  inline void Unlock() {
    if (state_ == POT_STATE_HIDDEN_PARAMETER || was_catching_up_) {
      state_ = POT_STATE_CATCHING_UP;
    } else {
      state_ = POT_STATE_TRACKING;
    }
  }

  inline void Realign() {
    state_ = POT_STATE_TRACKING;
  }

  inline void ProcessControlRate(uint16_t adc_value) {
    value_ += (adc_value - value_) >> 6;
    CONSTRAIN(value_, 0, 65535);
    // approximately this:
    // ONE_POLE(value_, adc_value, 0.01f);

    if (state_ == POT_STATE_TRACKING) {
      *main_parameter_ = value_;
    }
  }

  inline void ProcessUIRate() {
    switch (state_) {
      case POT_STATE_TRACKING:
        previous_value_ = value_;
        break;

      case POT_STATE_LOCKING:
        if (abs(value_ - previous_value_) > 1966) {
          stored_value_ = previous_value_;
          CONSTRAIN(value_, 0, 65535);
          *hidden_parameter_ = value_;
          state_ = POT_STATE_HIDDEN_PARAMETER;
          previous_value_ = value_;
        }
        break;

      case POT_STATE_HIDDEN_PARAMETER:
        CONSTRAIN(value_, 0, 65535);
        *hidden_parameter_ = value_;
        previous_value_ = value_;
        break;

      case POT_STATE_CATCHING_UP:
        {
          if (abs(value_ - previous_value_) > 327) {
            int32_t delta = value_ - previous_value_;

            int32_t skew_ratio = delta > 0
              ? (65600 - stored_value_) / (65535 - previous_value_)
              : (66 + stored_value_) / (66 + previous_value_);
            CONSTRAIN(skew_ratio, 6553, 655350);

            stored_value_ += (skew_ratio * delta) >> 11;
            CONSTRAIN(stored_value_, 0, 65535);

            if (abs(stored_value_ - value_) < 327) {
              state_ = POT_STATE_TRACKING;
            }
            previous_value_ = value_;
            *main_parameter_ = stored_value_;
          }
        }
        break;
    }
  }

 private:
  PotState state_;
  bool was_catching_up_;

  uint16_t* main_parameter_;
  uint16_t* hidden_parameter_;
  int32_t value_;
  int32_t stored_value_;
  int32_t previous_value_;

  DISALLOW_COPY_AND_ASSIGN(PotController);
};


