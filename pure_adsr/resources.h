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


#ifndef PURE_ADSR_RESOURCES_H_
#define PURE_ADSR_RESOURCES_H_


#include "avrlib/avrlib.h"
#include <avr/pgmspace.h>



namespace pure_adsr {

typedef uint8_t ResourceId;

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint32_t* const lookup_table_32_table[];

extern const prog_uint16_t lut_res_env_linear[] PROGMEM;
extern const prog_uint16_t lut_res_env_expo[] PROGMEM;
extern const prog_uint16_t lut_res_env_quartic[] PROGMEM;
extern const prog_uint16_t lut_res_raised_cosine[] PROGMEM;
extern const prog_uint32_t lut_res_env_increments[] PROGMEM;
extern const prog_uint32_t lut_res_env_increments_slow[] PROGMEM;
#define STR_RES_DUMMY 0  // dummy
#define LUT_RES_ENV_LINEAR 0
#define LUT_RES_ENV_LINEAR_SIZE 257
#define LUT_RES_ENV_EXPO 1
#define LUT_RES_ENV_EXPO_SIZE 257
#define LUT_RES_ENV_QUARTIC 2
#define LUT_RES_ENV_QUARTIC_SIZE 257
#define LUT_RES_RAISED_COSINE 3
#define LUT_RES_RAISED_COSINE_SIZE 257
#define LUT_RES_ENV_INCREMENTS 0
#define LUT_RES_ENV_INCREMENTS_SIZE 257
#define LUT_RES_ENV_INCREMENTS_SLOW 1
#define LUT_RES_ENV_INCREMENTS_SLOW_SIZE 257

}  // namespace pure_adsr

#endif  // PURE_ADSR_RESOURCES_H_
