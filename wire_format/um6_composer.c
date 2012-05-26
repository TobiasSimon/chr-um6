
/* 
 * File: um6_composer.c
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


#include <assert.h>

#include "um6_composer.h"
#include "um6_packet_bits.h"


/*
 * initializes the composer
 */
void um6_composer_init(um6_composer_t *composer)
{
   /* header is always fixed and is thus NOT 
      updated in every um6_composer_run call: */
   composer->data[0] = UM6_SYNC_1;
   composer->data[1] = UM6_SYNC_2;
   composer->data[2] = UM6_SYNC_3;
}


/*
 * composes a message from the given input
 */
void um6_composer_run(um6_composer_t *composer, const uint8_t *data, uint8_t data_len,
                      const uint8_t is_batch, const uint8_t ca)
{
   assert(composer);
   assert(is_batch < 2);
   assert(UM6_CA_VALID(ca));
   
   uint16_t crc = UM6_SYNC_CRC + ca;
   composer->data[UM6_CA_OFFSET] = ca;
   uint8_t pt = 0; /* NOTE: CF is nevers set here */
   if (data)
   {
      UM6_PT_SET_DATA(pt);
      if (!is_batch)
      {
         assert(data_len == UM6_DATA_ITEM_SIZE);
      }
      else
      {
         assert(data_len > 0 && data_len <= UM6_DATA_MAX);
         UM6_PT_SET_BATCH(pt);
         UM6_PT_SET_BATCH_SIZE(pt, data_len / UM6_DATA_ITEM_SIZE);
      }
   }
   else
   {
      assert(data_len == 0);
      assert(!is_batch);
   }
   crc += pt;
   composer->data[UM6_PT_OFFSET] = pt;
   unsigned int pos;
   for (pos = 0; pos < data_len; pos++)
   {
      composer->data[UM6_DATA_OFFSET + pos] = data[pos];
      crc += data[pos];
   }

   composer->data[UM6_CRC_OFFSET(pos)] = UM6_CRC_GET_HIGH(crc);
   composer->data[UM6_CRC_OFFSET(pos + 1)] = UM6_CRC_GET_LOW(crc);
   composer->size = UM6_PACKET_SIZE(pos);
}

