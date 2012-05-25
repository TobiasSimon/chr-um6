/* 
 * File: um6_regs.h
 * Purpose: CHR-UM6 Register Definitions
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


#ifndef UM6_REGS_H
#define UM6_REGS_H


/*
 * configuration registers
 */
typedef enum
{
   UM6_COMMUNICATION,
   UM6_MISC_CONFIG,
   UM6_MAG_REF_X,
   UM6_MAG_REF_Y,
   UM6_MAG_REF_Z,
   UM6_ACCEL_REF_X,
   UM6_ACCEL_REF_Y,
   UM6_ACCEL_REF_Z,
   UM6_EKF_MAG_VARIANCE,
   UM6_EKF_ACCEL_VARIANCE,
   UM6_EKF_PROCESS_VARIANCE,
   UM6_GYRO_BIAS_XY,
   UM6_GYRO_BIAS_Z,
   UM6_ACCEL_BIAS_XY,
   UM6_ACCEL_BIAS_Z,
   UM6_MAG_BIAS_XY,
   UM6_MAG_BIAS_Z,
   UM6_ACCEL_CAL_00,
   UM6_ACCEL_CAL_01,
   UM6_ACCEL_CAL_02,
   UM6_ACCEL_CAL_10,
   UM6_ACCEL_CAL_11,
   UM6_ACCEL_CAL_12,
   UM6_ACCEL_CAL_20,
   UM6_ACCEL_CAL_21,
   UM6_ACCEL_CAL_22,
   UM6_GYRO_CAL_00,
   UM6_GYRO_CAL_01,
   UM6_GYRO_CAL_02,
   UM6_GYRO_CAL_10,
   UM6_GYRO_CAL_11,
   UM6_GYRO_CAL_12,
   UM6_GYRO_CAL_20,
   UM6_GYRO_CAL_21,
   UM6_GYRO_CAL_22,
   UM6_MAG_CAL_00,
   UM6_MAG_CAL_01,
   UM6_MAG_CAL_02,
   UM6_MAG_CAL_10,
   UM6_MAG_CAL_11,
   UM6_MAG_CAL_12,
   UM6_MAG_CAL_20,
   UM6_MAG_CAL_21,
   UM6_MAG_CAL_22,
   UM6_GYROX_BIAS_0,
   UM6_GYROX_BIAS_1,
   UM6_GYROX_BIAS_2,
   UM6_GYROX_BIAS_3,
   UM6_GYROY_BIAS_0,
   UM6_GYROY_BIAS_1,
   UM6_GYROY_BIAS_2,
   UM6_GYROY_BIAS_3,
   UM6_GYROZ_BIAS_0,
   UM6_GYROZ_BIAS_1,
   UM6_GYROZ_BIAS_2,
   UM6_GYROZ_BIAS_3,
   UM6_GPS_HOME_LAT,
   UM6_GPS_HOME_LON,
   UM6_GPS_HOME_ALTITUDE,
}
um6_conf_reg_t;


#endif /* UM6_REGS_H */

