// Copyright 2020 Jan-Henrik Bruhn
//
// Author: Jan-Henrik Bruhn (hi@jhbruhn.de)
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
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef STEREO_MIX_RESOURCES_H_
#define STEREO_MIX_RESOURCES_H_


#include "stmlib/stmlib.h"



namespace stereo_mix {

typedef uint8_t ResourceId;

extern const uint16_t* lookup_table_u16_table[];

extern const uint8_t* lookup_table_u8_table[];

extern const uint16_t lut_linear_to_exp[];
extern const uint16_t lut_left_sin_pan[];
extern const uint16_t lut_right_cos_pan[];
extern const uint16_t lut_led_red_gamma[];
extern const uint16_t lut_led_green_gamma[];
#define LUT_LINEAR_TO_EXP 0
#define LUT_LINEAR_TO_EXP_SIZE 4096
#define LUT_LEFT_SIN_PAN 1
#define LUT_LEFT_SIN_PAN_SIZE 4096
#define LUT_RIGHT_COS_PAN 2
#define LUT_RIGHT_COS_PAN_SIZE 4096
#define LUT_LED_RED_GAMMA 3
#define LUT_LED_RED_GAMMA_SIZE 4096
#define LUT_LED_GREEN_GAMMA 4
#define LUT_LED_GREEN_GAMMA_SIZE 4096

}  // namespace stereo_mix

#endif  // STEREO_MIX_RESOURCES_H_
