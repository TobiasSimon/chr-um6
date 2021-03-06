
/* 
 * File: um6_convert.c
 * Purpose: CHR-UM6 Serial Protocol Data Conversion Functions
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



#include "um6_convert.h"

#include <endian.h>
#include <math.h>


uint32_t float_to_uint32(float val)
{
  return htobe32(*(uint32_t *)&val);
}


float int32_to_float(uint32_t val)
{
  uint32_t host_val = be32toh(val);
  return *((float *)&host_val);
}


int16_t biguint16_to_int16(uint16_t val)
{
   uint16_t tmp = be16toh(val);
   return *(int16_t *)&tmp;
}


float uint16_to_euler(uint16_t val)
{
   int16_t tmp = val; //be16toh(val);
   return ((float)tmp) * 0.0109863 / 180.0 * M_PI;
}


float uint16_to_gyro(uint16_t val)
{
   int16_t tmp = be16toh(val);
   return ((float)tmp) * 0.0610352 / 180.0 * M_PI;
}


float uint16_to_acc(uint16_t val)
{
   int16_t tmp = be16toh(val);
   return ((float)tmp) * 0.000183105 * 9.81;
}


float uint16_to_mag(uint16_t val)
{
   int16_t tmp = be16toh(val);
   return ((float)tmp) * 0.000305176;
}

