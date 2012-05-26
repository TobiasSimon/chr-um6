
/* 
 * File: um6_packet_bits.h
 * Purpose: CHR-UM6 Serial Protocol Packet Type Bit Definitions
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


#ifndef UM6_PACKET_BITS_H
#define UM6_PACKET_BITS_H

/*
 * general packet information:
 */
#define UM6_SYNC_1 ('s')
#define UM6_SYNC_2 ('n')
#define UM6_SYNC_3 ('p')
#define UM6_SYNC_SIZE (3)
#define UM6_SYNC_CRC (UM6_SYNC_1 + UM6_SYNC_2 + UM6_SYNC_3)

#define UM6_DATA_ITEM_SIZE (4)
#define UM6_DATA_MAX (16 * UM6_DATA_ITEM_SIZE)

#define UM6_PT_SIZE (1)
#define UM6_CA_SIZE (1)
#define UM6_CRC_SIZE (2)
#define UM6_CRC_GET_LOW(crc) (crc & 0xFF)
#define UM6_CRC_GET_HIGH(crc) (crc >> 8)
#define UM6_CRC_BUILD(low, high) ((high) << 8 | (low))

#define UM6_PACKET_SIZE_MIN (UM6_SYNC_SIZE + UM6_PT_SIZE + UM6_CA_SIZE + UM6_CRC_SIZE)
#define UM6_PACKET_SIZE_MAX (UM6_PACKET_SIZE_MIN + UM6_DATA_MAX)

#define UM6_PT_OFFSET (UM6_SYNC_SIZE)
#define UM6_CA_OFFSET (UM6_PT_OFFSET + UM6_PT_SIZE)
#define UM6_DATA_OFFSET (UM6_CA_OFFSET + UM6_CA_SIZE)
#define UM6_CRC_OFFSET(data_size) (UM6_DATA_OFFSET + (data_size))
#define UM6_PACKET_SIZE(data_size) (UM6_CRC_OFFSET(data_size) + UM6_CRC_SIZE)

/* 
 * bit definitions for PT command:
 */
#define UM6_PT_BIT_DATA     (1 << 7)
#define UM6_PT_BIT_BATCH    (1 << 6)
#define UM6_PT_SHIFT_BATCH  (2)
#define UM6_PT_BITS_BATCH   (0x0F << UM6_PT_SHIFT_BATCH)
#define UM6_PT_BIT_CF       (1 << 0)


/*
 * access macros for PT command:
 */
#define UM6_PT_GET_DATA(pt)       ((pt) & UM6_PT_BIT_DATA)
#define UM6_PT_GET_BATCH(pt)      ((pt) & UM6_PT_BIT_BATCH)
#define UM6_PT_GET_BATCH_SIZE(pt) (((pt) & UM6_PT_BITS_BATCH) >> UM6_PT_SHIFT_BATCH)
#define UM6_PT_GET_CF(pt)         ((pt) & UM6_PT_BIT_CF)

#define UM6_PT_SET_DATA(pt)          pt |= UM6_PT_BIT_DATA
#define UM6_PT_SET_BATCH(pt)         pt |= UM6_PT_BIT_BATCH
#define UM6_PT_SET_BATCH_SIZE(pt, s) pt |= (s) << UM6_PT_SHIFT_BATCH
#define UM6_PT_SET_CF(pt)            pt |= UM6_PT_BIT_CF


/*
 * command/addess validity check:
 */
#define UM6_CA_VALID(ca) (((ca) >= 0 && (ca) <= 0x40) || ((ca) >= 0x55 && (ca) <= 0x84) || ((ca) >= 0xAA && (ca) <= 0xFF))


#endif /* UM6_PACKET_BITS_H */

