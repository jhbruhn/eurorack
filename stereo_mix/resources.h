// Copyright 2019 Jan-Henrik Bruhn.
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef STEREO_MIX_RESOURCES_H_
#define STEREO_MIX_RESOURCES_H_


#include "avrlib/avrlib.h"
#include <avr/pgmspace.h>



namespace stereo_mix {

typedef uint8_t ResourceId;

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint32_t* const lookup_table_32_table[];

extern const prog_uint16_t lut_res_linear_to_exp[] PROGMEM;
extern const prog_uint16_t lut_res_left_sin_pan[] PROGMEM;
extern const prog_uint16_t lut_res_right_cos_pan[] PROGMEM;
#define STR_RES_DUMMY 0  // dummy
#define LUT_RES_LINEAR_TO_EXP 0
#define LUT_RES_LINEAR_TO_EXP_SIZE 512
#define LUT_RES_LEFT_SIN_PAN 1
#define LUT_RES_LEFT_SIN_PAN_SIZE 512
#define LUT_RES_RIGHT_COS_PAN 2
#define LUT_RES_RIGHT_COS_PAN_SIZE 512

}  // namespace stereo_mix

#endif  // STEREO_MIX_RESOURCES_H_
