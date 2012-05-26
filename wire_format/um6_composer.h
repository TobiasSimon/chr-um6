
/* 
 * File: um6_composer.h
 * Purpose: CHR-UM6 Serial Protocol Composer
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


#ifndef UM6_COMPOSER_H
#define UM6_COMPOSER_H


#include "um6_packet_bits.h"

#include <stdint.h>


typedef struct
{
   uint8_t data[UM6_PACKET_SIZE_MAX];
   uint8_t size;
} um6_composer_t;


/*
 * initializes the composer
 */
void um6_composer_init(um6_composer_t *composer);


/*
 * composes a message from the given input
 */ 
void um6_composer_run(um6_composer_t *composer, const uint8_t *data, const uint8_t data_len,
                      const uint8_t is_batch, const uint8_t ca);


#endif /* UM6_COMPOSER_H */

