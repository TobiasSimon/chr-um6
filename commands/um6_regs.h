
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
   UM6_COMMUNICATION = 0x00,
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


/*
 * data registers
 */
typedef enum
{
   UM6_STATUS = 0x55,
   UM6_GYRO_RAW_XY,
   UM6_GYRO_RAW_Z,
   UM6_ACCEL_RAW_XY,
   UM6_ACCEL_RAW_Z,
   UM6_MAG_RAW_XY,
   UM6_MAG_RAW_Z,
   UM6_GYRO_PROC_XY,
   UM6_GYRO_PROC_Z,
   UM6_ACCEL_PROC_XY,
   UM6_ACCEL_PROC_Z,
   UM6_MAG_PROC_XY,
   UM6_MAG_PROC_Z,
   UM6_EULER_PHI_THETA,
   UM6_EULER_PSI,
   UM6_QUAT_AB,
   UM6_QUAT_CD,
   UM6_ERROR_COV_00,
   UM6_ERROR_COV_01,
   UM6_ERROR_COV_02,
   UM6_ERROR_COV_03,
   UM6_ERROR_COV_10,
   UM6_ERROR_COV_11,
   UM6_ERROR_COV_12,
   UM6_ERROR_COV_13,
   UM6_ERROR_COV_20,
   UM6_ERROR_COV_21,
   UM6_ERROR_COV_22,
   UM6_ERROR_COV_23,
   UM6_ERROR_COV_30,
   UM6_ERROR_COV_31,
   UM6_ERROR_COV_32,
   UM6_ERROR_COV_33,
   UM6_TEMPERATURE,
   UM6_GPS_LONGITUDE,
   UM6_GPS_LATITUDE,
   UM6_GPS_ALTITUDE,
   UM6_GPS_POSITION_N,
   UM6_GPS_POSITION_E,
   UM6_GPS_POSITION_H,
   UM6_GPS_COURSE_SPEED,
   UM6_GPS_SAT_SUMMARY,
   UM6_GPS_SAT_1_2,
   UM6_GPS_SAT_3_4,
   UM6_GPS_SAT_5_6,
   UM6_GPS_SAT_7_8,
   UM6_GPS_SAT_9_10,
   UM6_GPS_SAT_11_12
}
um6_data_reg_t;


/* status register bits */
#define UM6_STATUS_ST      (1 << 0)
/* bits 1 - 12 reserved */
#define UM6_STATUS_MAG_DEL (1 << 13)
#define UM6_STATUS_ACC_DEL (1 << 14)
#define UM6_STATUS_GYR_DEL (1 << 15)
#define UM6_STATUS_EKF_DIV (1 << 16)
#define UM6_STATUS_BUS_MAG (1 << 17)
#define UM6_STATUS_BUS_ACC (1 << 18)
#define UM6_STATUS_BUS_GYR (1 << 19)
#define UM6_STATUS_ST_MZ   (1 << 20)
#define UM6_STATUS_ST_MY   (1 << 21)
#define UM6_STATUS_ST_MX   (1 << 22)
#define UM6_STATUS_ST_AZ   (1 << 23)
#define UM6_STATUS_ST_AY   (1 << 24)
#define UM6_STATUS_ST_AX   (1 << 25)
#define UM6_STATUS_ST_GZ   (1 << 26)
#define UM6_STATUS_ST_GY   (1 << 27)
#define UM6_STATUS_ST_GX   (1 << 28)
#define UM6_STATUS_GYR_INI (1 << 29)
#define UM6_STATUS_ACC_INI (1 << 30)
#define UM6_STATUS_MAG_INI (1 << 31)


/*
 * command registers
 */
typedef enum
{
   UM6_GET_FW_VERSION = 0xAA,
   UM6_FLASH_COMMIT,
   UM6_ZERO_GYROS,
   UM6_RESET_EKF,
   UM6_GET_DATA,
   UM6_SET_ACCEL_REF,
   UM6_SET_MAG_REF,
   UM6_RESET_TO_FACTORY,
   UM6_CMD_RESERVED,
   UM6_SET_HOME_POSITION,
   UM6_BAD_CHECKSUM,
   UM6_UNKNOWN_ADDRESS,
   UM6_INVALID_BATCH_SIZE
}
um6_cmd_reg_t;


#endif /* UM6_REGS_H */
