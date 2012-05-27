
/* 
 * File: um6_parser.h
 * Purpose: CHR-UM6 Serial Protocol Parser
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


#ifndef __UM6_PARSER_H__
#define __UM6_PARSER_H__


#include "um6_packet_bits.h"

#include <stdint.h>


typedef enum
{
   UM6_S,
   UM6_N,
   UM6_P,
   UM6_PT,
   UM6_CA,
   UM6_DATA,
   UM6_CS1,
   UM6_CS2
}
um6_parser_state_t;


/*
 * parser context:
 */
typedef struct
{
   um6_parser_state_t state; /* indicates what to read next */
   um6_parser_state_t state_after_ca; /* indicates what to read after ca state */

   uint8_t pt;
   uint8_t ca;
   uint8_t data[UM6_DATA_MAX];
   uint8_t data_len;
   uint8_t tmp;
   uint16_t crc;
} um6_parser_t;


/*
 * initializes the parser; must be called once before um6_parser_run
 */ 
void um6_parser_init(um6_parser_t *parser);


/*
 * runs the parser for a given character coming from the CHR-6DM AHRS
 * returns: 0 (successful intermediate parser step)
 *          1 (complete frame with valid CRC)
 *         -1 (parser state error)
 *         -2 (CRC invalid)
 */
int um6_parser_run(um6_parser_t *parser, uint8_t c);


#endif /* __UM6_PARSER_H__ */

