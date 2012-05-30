
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
#include "../sys/event.h"
#include "../sys/lock.h"



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
   event_t event;
}
um6_vec3d_t;


/*
 * generic um6 3d bias vector:
 */
typedef struct
{
   union
   {
      struct
      {
         int16_t x;
         int16_t y;
         int16_t z;
      };
      int16_t a[3];
   };
   int valid;
   event_t event;
}
um6_bias3d_t;


typedef struct
{
   union
   {
      struct
      {
         float phi;
         float theta;
         float psi;
      };
      float a[3];
   };
   int valid;
   event_t event;
}
um6_euler_t;


typedef struct
{
   float data;
   int valid;
   event_t event;
}
um6_float_t;


typedef struct
{
   uint32_t data;
   int valid;
   event_t event;
}
um6_uint32_t;


typedef struct
{
   um6_bias3d_t gyro_bias;
   um6_float_t temperature;
   um6_float_t ekf_mag_var;
   um6_float_t ekf_acc_var;
   um6_float_t ekf_proc_var;
   um6_vec3d_t gyro_raw;
   um6_vec3d_t acc_raw;
   um6_vec3d_t mag_raw;
   um6_vec3d_t gyro_proc;
   um6_vec3d_t acc_proc;
   um6_vec3d_t mag_proc;
   um6_euler_t euler;
   um6_uint32_t status;
   um6_uint32_t comm;
   um6_uint32_t fw_version;
   um6_uint32_t misc;
   event_t ekf_reset_event;
   event_t zero_gyros_event;
   event_t acc_ref_event;
   event_t mag_ref_event;
   event_t factory_reset_event;
}
um6_data_t;



typedef struct
{
   void *context;
   int (*read)(void *context); /* returns character (0-255) or a negative error code */
   int (*write)(void *context, uint8_t c); /* returns 0 on success or a negative error code */
}
um6_io_t;


typedef struct
{
   um6_io_t *io; /* abstract io interface */
   lock_t *lock; /* abstract lock for data protection */
   um6_data_t data; /* date written by reader thread */
   um6_composer_t composer; /* composer for sending data */
   unsigned int rx_timeout;
   unsigned int retry_count;
}
um6_dev_t;


void um6_dev_init(um6_dev_t *dev, lock_t *lock, um6_io_t *io,
                  event_interface_t *event_interface, unsigned int rx_timeout);

void *um6_reader(void *arg);


/*
 * get status register
 */
int um6_get_status(um6_dev_t *dev, uint32_t *out);


/*
 * get communication register
 */
int um6_get_comm(um6_dev_t *dev, uint32_t *out);


/*
 * set communication register
 */
int um6_set_comm(um6_dev_t *dev, uint32_t val);


/*
 * get firmware version string
 * len(out) >= 5
 */
int um6_get_fw_version(um6_dev_t *dev, char *out);


/*
 * zero rate gyros
 */
int um6_zero_gyros(um6_dev_t *dev);


/*
 * reset extended kalman filter
 */
int um6_reset_ekf(um6_dev_t *dev);


/*
 * set acc reference vector to current acc readings
 */
int um6_acc_ref(um6_dev_t *dev);


/*
 * set mag regerence vector to current mag readings
 */
int um6_mag_ref(um6_dev_t *dev);


/*
 * reset settings to factory standard
 */
int um6_reset_to_factory(um6_dev_t *dev);


/*
 * read mag variance setting
 */
int um6_get_mag_var(um6_dev_t *dev, float *out);


/*
 * read acc variance setting
 */
float um6_get_acc_var(um6_dev_t *dev, float *out);


/*
 * read process variance setting
 */
float um6_get_proc_var(um6_dev_t *dev, float *out);


/*
 * set mag variance
 */
int um6_set_mag_var(um6_dev_t *dev, float var);


/*
 * set acc variance
 */
int um6_set_acc_var(um6_dev_t *dev, float var);


/*
 * set process variance
 */
int um6_set_proc_var(um6_dev_t *dev, float var);


#endif /* __CHR_UM6_H__ */

