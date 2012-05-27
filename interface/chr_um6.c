
/* 
 * File: chr_um6.c
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


#include "chr_um6.h"
#include "../wire_format/um6_parser.h"
#include "../regs/um6_convert.h"
#include "../regs/um6_regs.h"

#include <pthread.h>
#include <endian.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


int um6_lock(um6_dev_t *dev)
{
   return dev->lock->lock(dev->lock->context);
}


int um6_unlock(um6_dev_t *dev)
{
   return dev->lock->unlock(dev->lock->context);
}


static void handle_data(um6_data_t *data_out, uint8_t ca, uint8_t *data)
{
   uint32_t data32_1 = le32toh(*(uint32_t *)data);
   uint32_t data32_2 = le32toh(*(uint32_t *)(data + UM6_DATA_ITEM_SIZE));
   switch (ca)
   {
      case UM6_STATUS:
         //TODO UM6_STATUS_DEBUG(data32_1);
         break;
      
      case UM6_TEMPERATURE:
         data_out->temperature.val = float_from_uint32(*(uint32_t *)data);
         data_out->temperature.valid = 1;
         break;
      
      case UM6_COMM:
         //TODO UM6_COMM_DEBUG(data32_1);
         break;
      
      case UM6_GYRO_RAW1:
      {
         float grx = gyro_from_uint16(UM6_GYRO_RAW1_GET_X(data32_1));
         float gry = gyro_from_uint16(UM6_GYRO_RAW1_GET_Y(data32_1));
         float grz = gyro_from_uint16(UM6_GYRO_RAW2_GET_Z(data32_2));
         //TOTO printf("gyro raw x = %f y = %f z = %f\n", grx, gry, grz);
         break;
      }

      case UM6_GYRO_PROC1:
      {
         float gx = gyro_from_uint16(UM6_GYRO_PROC1_GET_X(data32_1));
         float gy = gyro_from_uint16(UM6_GYRO_PROC1_GET_Y(data32_1));
         float gz = gyro_from_uint16(UM6_GYRO_PROC2_GET_Z(data32_2));
         //TODO printf("gyro x = %f y = %f z = %f\n", gx, gy, gz);
         break;
      }

      case UM6_ACC_PROC1:
      {
         float ax = acc_from_uint16(UM6_ACC_PROC1_GET_X(data32_1));
         float ay = acc_from_uint16(UM6_ACC_PROC1_GET_Y(data32_1));
         float az = acc_from_uint16(UM6_ACC_PROC2_GET_Z(data32_2));
         //TODO printf("acc x = %f y = %f z = %f\n", ax, ay, az);
         break;
      }

      case UM6_MAG_PROC1:
      {
         float mx = mag_from_uint16(UM6_MAG_PROC1_GET_X(data32_1));
         float my = mag_from_uint16(UM6_MAG_PROC1_GET_Y(data32_1));
         float mz = mag_from_uint16(UM6_MAG_PROC2_GET_Z(data32_2));
         //TODO printf("mag x = %f y = %f z = %f\n", mx, my, mz);
         break;
      }

      case UM6_EULER1:
      {
         float phi = euler_from_uint16(UM6_EULER1_GET_PHI(data32_1));
         float theta = euler_from_uint16(UM6_EULER1_GET_THETA(data32_1));
         float psi = euler_from_uint16(UM6_EULER2_GET_PSI(data32_2));
         //TODO printf("euler roll = %f pitch = %f yaw = %f\n", phi, theta, psi);
         break;
      }
   }
}


void *um6_reader(void *arg)
{
   um6_dev_t *dev = (um6_dev_t *)arg;
   um6_io_t *io = dev->io;
   um6_parser_t parser;
   um6_parser_init(&parser);
   int start = 0;
   while (1)
   {
      int c = io->read(io->context);
      if (c >= 0)
      {
         int ret = um6_parser_run(&parser, c);
         if (ret == 1)
         {
            um6_lock(dev);
            handle_data(&dev->data, parser.ca, parser.data);
            um6_unlock(dev);
         }
         else if (ret < 0 && start++ > UM6_DATA_MAX)
         {
            start = UM6_DATA_MAX;
            printf("error: %d\n", ret);
         }
      }
   }
   pthread_exit(NULL);
}


void um6_dev_init(um6_dev_t *dev, um6_lock_t *lock, um6_io_t *io)
{
   dev->io = io;
   dev->lock = lock;
   memset(&dev->data, 0, sizeof(um6_data_t));
   um6_composer_init(&dev->composer);
}


int um6_compose_and_send(um6_dev_t *dev, const uint8_t *data, const uint8_t data_len,
                         const uint8_t is_batch, const uint8_t ca)
{
   int ret;
   um6_lock(dev);
   um6_composer_run(&dev->composer, data, data_len, is_batch, ca);
   int i;
   for (i = 0; i < dev->composer.size; i++)
   {
      ret = dev->io->write(dev->io->context, dev->composer.data[i]);
      if (ret != 0)
      {
         goto out;
      }
   }
out:
   um6_unlock(dev);
   return ret;
}



