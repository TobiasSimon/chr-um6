
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
   return lock_acquire(dev->lock);
}


int um6_unlock(um6_dev_t *dev)
{
   return lock_release(dev->lock);
}


static void handle_data(um6_data_t *out, uint8_t ca, uint8_t *data)
{
   uint32_t data32_1 = le32toh(*(uint32_t *)data);
   uint32_t data32_2 = le32toh(*(uint32_t *)(data + UM6_DATA_ITEM_SIZE));
   switch (ca)
   {
      case UM6_STATUS:
         out->status.data = data32_1;
         out->status.valid = 1;
         event_signal(&out->status.event);
         break;

      case UM6_EKF_MAG_VAR:
         out->ekf_mag_var.data = float_from_uint32(*(uint32_t *)data);
         out->ekf_mag_var.valid = 1;
         event_signal(&out->ekf_mag_var.event);
         break;

      case UM6_EKF_ACC_VAR:
         out->ekf_acc_var.data = float_from_uint32(*(uint32_t *)data);
         out->ekf_acc_var.valid = 1;
         event_signal(&out->ekf_acc_var.event);
         break;

      case UM6_EKF_PROC_VAR:
         out->ekf_proc_var.data = float_from_uint32(*(uint32_t *)data);
         out->ekf_proc_var.valid = 1;
         event_signal(&out->ekf_proc_var.event);
         break;

      case UM6_TEMPERATURE:
         out->temperature.data = float_from_uint32(*(uint32_t *)data);
         out->temperature.valid = 1;
         event_signal(&out->temperature.event);
         break;
      
      case UM6_COMM:
         out->comm.data = data32_1;
         out->comm.valid = 1;
         event_signal(&out->comm.event);
         break;
      
      case UM6_GYRO_BIAS1:
         out->gyro_bias.x = be16toi16(UM6_GYRO_BIAS1_GET_X(data32_1));
         out->gyro_bias.y = be16toi16(UM6_GYRO_BIAS1_GET_Y(data32_1));
         out->gyro_bias.z = be16toi16(UM6_GYRO_BIAS2_GET_Z(data32_2));
         out->gyro_bias.valid = 1;
         printf("gyro biases: %d %d %d\n", out->gyro_bias.x, out->gyro_bias.y, out->gyro_bias.z);
         event_signal(&out->gyro_bias.event);
         break;


      case UM6_GET_FW_VERSION:
         out->fw_version.data = data32_1;
         out->fw_version.valid = 1;
         event_signal(&out->fw_version.event);
         break;
      
      case UM6_GYRO_RAW1:
         out->gyro_raw.x = gyro_from_uint16(UM6_GYRO_RAW1_GET_X(data32_1));
         out->gyro_raw.y = gyro_from_uint16(UM6_GYRO_RAW1_GET_Y(data32_1));
         out->gyro_raw.z = gyro_from_uint16(UM6_GYRO_RAW2_GET_Z(data32_2));
         out->gyro_raw.valid = 1;
         event_signal(&out->gyro_raw.event);
         break;

      case UM6_GYRO_PROC1:
         out->gyro_proc.x = gyro_from_uint16(UM6_GYRO_PROC1_GET_X(data32_1));
         out->gyro_proc.y = gyro_from_uint16(UM6_GYRO_PROC1_GET_Y(data32_1));
         out->gyro_proc.z = gyro_from_uint16(UM6_GYRO_PROC2_GET_Z(data32_2));
         out->gyro_proc.valid = 1;
         event_signal(&out->gyro_proc.event);
         break;

      case UM6_ACC_PROC1:
         out->acc_proc.x = acc_from_uint16(UM6_ACC_PROC1_GET_X(data32_1));
         out->acc_proc.y = acc_from_uint16(UM6_ACC_PROC1_GET_Y(data32_1));
         out->acc_proc.z = acc_from_uint16(UM6_ACC_PROC2_GET_Z(data32_2));
         out->acc_proc.valid = 1;
         event_signal(&out->acc_proc.event);
         break;

      case UM6_MAG_PROC1:
         out->mag_proc.x = mag_from_uint16(UM6_MAG_PROC1_GET_X(data32_1));
         out->mag_proc.y = mag_from_uint16(UM6_MAG_PROC1_GET_Y(data32_1));
         out->mag_proc.z = mag_from_uint16(UM6_MAG_PROC2_GET_Z(data32_2));
         out->mag_proc.valid = 1;
         event_signal(&out->mag_proc.event);
         break;

      case UM6_EULER1:
         out->euler.phi = euler_from_uint16(UM6_EULER1_GET_PHI(data32_1));
         out->euler.theta = euler_from_uint16(UM6_EULER1_GET_THETA(data32_1));
         out->euler.psi = euler_from_uint16(UM6_EULER2_GET_PSI(data32_2));
         out->euler.valid = 1;
         //printf("%f %f %f\n", out->euler.phi, out->euler.theta, out->euler.psi);
         event_signal(&out->euler.event);
         break;

      case UM6_ZERO_GYROS:
         event_signal(&out->zero_gyros_event);
         break;

      case UM6_RESET_EKF:
         event_signal(&out->ekf_reset_event);
         break;

      case UM6_SET_ACC_REF:
         event_signal(&out->acc_ref_event);
         break;

     case UM6_SET_MAG_REF:
         event_signal(&out->mag_ref_event);
         break;

     case UM6_RESET_TO_FACTORY:
         event_signal(&out->factory_reset_event);
         break;


      default:
         printf("unhandled command: %X\n", ca);
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
            handle_data(&dev->data, parser.ca, parser.data);
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


void um6_dev_init(um6_dev_t *dev, lock_t *lock, um6_io_t *io, event_interface_t *event_interface)
{
   dev->io = io;
   dev->lock = lock;
   memset(&dev->data, 0, sizeof(um6_data_t));
   um6_composer_init(&dev->composer);
   event_init(&dev->data.status.event, event_interface);
   event_init(&dev->data.ekf_mag_var.event, event_interface);
   event_init(&dev->data.ekf_acc_var.event, event_interface);
   event_init(&dev->data.ekf_proc_var.event, event_interface);
   event_init(&dev->data.gyro_bias.event, event_interface);
   event_init(&dev->data.temperature.event, event_interface);
   event_init(&dev->data.comm.event, event_interface);
   event_init(&dev->data.fw_version.event, event_interface);
   event_init(&dev->data.gyro_raw.event, event_interface);
   event_init(&dev->data.gyro_proc.event, event_interface);
   event_init(&dev->data.acc_proc.event, event_interface);
   event_init(&dev->data.mag_proc.event, event_interface);
   event_init(&dev->data.euler.event, event_interface);
   event_init(&dev->data.ekf_reset_event, event_interface);
   event_init(&dev->data.zero_gyros_event, event_interface);
   event_init(&dev->data.acc_ref_event, event_interface);
   event_init(&dev->data.mag_ref_event, event_interface);
   event_init(&dev->data.factory_reset_event, event_interface);
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
      if (ret != 1)
      {
         goto out;
      }
   }
out:
   um6_unlock(dev);
   return ret;
}


uint32_t um6_get_status(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_STATUS);
   event_wait(&dev->data.status.event);
   return dev->data.status.data;
}


uint32_t um6_get_comm(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_COMM);
   event_wait(&dev->data.comm.event);
   return dev->data.comm.data;
}


uint32_t um6_get_fw_version(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_GET_FW_VERSION);
   event_wait(&dev->data.fw_version.event);
   return dev->data.fw_version.data;
}

int um6_zero_gyros(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_ZERO_GYROS);
   event_wait(&dev->data.zero_gyros_event);
   return 0;
}

int um6_reset_ekf(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_RESET_EKF);
   event_wait(&dev->data.ekf_reset_event);
   return 0;
}


int um6_acc_ref(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_SET_ACC_REF);
   event_wait(&dev->data.acc_ref_event);
   return 0;
}


int um6_mag_ref(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_SET_MAG_REF);
   event_wait(&dev->data.mag_ref_event);
   return 0;
}


int um6_reset_to_factory(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_RESET_TO_FACTORY);
   event_wait(&dev->data.factory_reset_event);
   return 0;
}


float um6_get_mag_var(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_EKF_MAG_VAR);
   event_wait(&dev->data.ekf_mag_var.event);
   return dev->data.ekf_mag_var.data;
}


float um6_get_acc_var(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_EKF_ACC_VAR);
   event_wait(&dev->data.ekf_acc_var.event);
   return dev->data.ekf_acc_var.data;
}


float um6_get_proc_var(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_EKF_PROC_VAR);
   event_wait(&dev->data.ekf_proc_var.event);
   return dev->data.ekf_proc_var.data;
}


float um6_set_mag_var(um6_dev_t *dev, float var)
{
   uint32_t u_var = float_to_uint32(var);
   um6_compose_and_send(dev, (uint8_t *)&u_var, 4, 0, UM6_EKF_MAG_VAR);
   //event_wait(&dev->data.ekf_mag_var.event);
   return dev->data.ekf_mag_var.data;
}


float um6_set_acc_var(um6_dev_t *dev, float var)
{
   uint32_t u_var = float_to_uint32(var);
   um6_compose_and_send(dev, (uint8_t *)&u_var, 4, 0, UM6_EKF_ACC_VAR);
   event_wait(&dev->data.ekf_acc_var.event);
   return dev->data.ekf_acc_var.data;
}


float um6_set_proc_var(um6_dev_t *dev, float var)
{
   uint32_t u_var = float_to_uint32(var);
   um6_compose_and_send(dev, (uint8_t *)&u_var, 4, 0, UM6_EKF_PROC_VAR);
   event_wait(&dev->data.ekf_proc_var.event);
   return dev->data.ekf_proc_var.data;
}


