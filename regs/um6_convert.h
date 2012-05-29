
/* 
 * File: um6_convert.h
 * Purpose: CHR-UM6 Serial Protocol Data Conversion Functions
 *
 * Copyright (C) 2012 Tobias Simon, Ilmenau University of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#ifndef __UM6_CONVERT_H__
#define __UM6_CONVERT_H__


#include <stdint.h>


int16_t biguint16_to_int16(uint16_t val);

uint32_t float_to_uint32(float val);

float int32_to_float(uint32_t val);

float uint16_to_euler(uint16_t val);

float uint16_to_gyro(uint16_t val);

float uint16_to_acc(uint16_t val);

float uint16_to_mag(uint16_t val);


#endif /* __UM6_CONVERT_H__ */

