
/* 
 * File: um6_parser.c
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


#include "um6_parser.h"


/*
 * initializes the parser; must be called once before um6_parser_run
 */ 
void um6_parser_init(um6_parser_t *parser)
{
   parser->state = UM6_S;
}


/*
 * runs the parser for a given character coming from the CHR-6DM AHRS
 * returns: 0 (successful intermediate parser step)
 *          1 (complete frame with valid CRC)
 *         -1 (parser state error)
 *         -2 (CRC invalid)
 */
int um6_parser_run(um6_parser_t *parser, const uint8_t c)
{
   int ret = 0;
   if (parser->state == UM6_S && c == 's')
   {
      parser->state = UM6_N;
   }
   else if (parser->state == UM6_N && c == 'n')
   {
      parser->state = UM6_P;
   }
   else if (parser->state == UM6_P && c == 'p')
   {
      parser->crc = 's' + 'n' + 'p';
      parser->state = UM6_PT;
   }
   else if (parser->state == UM6_PT)
   {
      parser->pt = c;
      if (!UM6_PT_GET_DATA(c))
      {
         parser->state = UM6_CS1;
      }
      else
      {
         parser->tmp = 0;
         if (!UM6_PT_GET_BATCH(c))
         {
            parser->data_len = 4;
         }
         else
         {
            parser->data_len = UM6_PT_GET_BATCH_SIZE(c) * 4;
         }
         parser->state = UM6_DATA;
      }
      parser->crc += c;
   }
   else if (parser->state == UM6_DATA)
   {
      if (parser->tmp == parser->data_len)
      {
         parser->state = UM6_CS1;
      }
      parser->data[parser->tmp++] = c;
      parser->crc += c;
   }
   else if (parser->state == UM6_CS1)
   {
      parser->tmp = c;
      parser->state = UM6_CS2;
   }
   else
   {
      if (parser->state == UM6_CS2)
      {
         const uint16_t submitted_crc = (parser->tmp << 8) | c;
         if (submitted_crc == parser->crc)
         {
            ret = 1;
         }
         else
         {
            ret = -2;
         }
      }
      else
      {
         ret = -1;
      }
      parser->state = UM6_S;
   }
   return ret;
}
