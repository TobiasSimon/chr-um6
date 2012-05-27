
/* 
 * File: chr_um6.h
 * Purpose: CHR-UM6 Interface
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


#ifndef __CHR_UM6_H__
#define __CHR_UM6_H__


#include <stdint.h>

#include "../wire_format/um6_composer.h"


/*
 * generic um6 3d vector:
 */
typedef struct
{
   union
   {
      struct
      {
         float x;
         float y;
         float z;
      };
      float a[3];
   };
   int valid;
}
um6_vec3d_t;


typedef struct
{
   float val;
   int valid;
}
um6_float_t;


typedef struct
{
   void *context;
   int (*lock)(void *context); /* returns 0 on success or a negative error code */
   int (*unlock)(void *context); /* returns 0 on success or a negative error code */
}
um6_lock_t;


typedef struct
{
   void *context;
   int (*read)(void *context); /* returns character (0-255) or a negative error code */
   int (*write)(void *context, uint8_t c); /* returns 0 on success or a negative error code */
}
um6_io_t;


typedef struct
{
   um6_vec3d_t gyro_raw;
   um6_vec3d_t acc_raw;
   um6_vec3d_t mag_raw;
   um6_vec3d_t gyro_proc;
   um6_vec3d_t acc_proc;
   um6_vec3d_t mag_proc;
   um6_float_t temperature;
}
um6_data_t;


typedef struct
{
   um6_io_t *io; /* abstract io interface */
   um6_lock_t *lock; /* abstract lock for data protection */
   um6_data_t data; /* date written by reader thread */
   um6_composer_t composer; /* composer for sending data */
}
um6_dev_t;


int um6_lock(um6_dev_t *lock);

int um6_unlock(um6_dev_t *lock);

void um6_dev_init(um6_dev_t *dev, um6_lock_t *lock, um6_io_t *io);

void *um6_reader(void *arg);


int um6_compose_and_send(um6_dev_t *dev, const uint8_t *data, const uint8_t data_len,
                         const uint8_t is_batch, const uint8_t ca);


#endif /* __CHR_UM6_H__ */

