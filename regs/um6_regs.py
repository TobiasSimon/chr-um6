
# File: um6_registers.py
# Purpose: CHR-UM6 register/bit definitions for "creghead" header generator
# Author: Tobias Simon, Ilmenau University of Technology
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


prefix = 'UM6'
regs = [
   # UM6 CONFIGURATION REGISTERS:
   ('COMM', 0x00, 32, 'communication settings',
      [
         ('BC_RATE',   8, 'packet broadcast frequency; freq = (280 / 255) * broadcast_rate + 20'),
         ('BAUD_RATE', 3, 'serial port baudrate; 000: 9600, 001: 14400, 010: 19200, 011 -> 38400, 100 -> 57600, 101 -> 115200'),
         ('GPS_BAUD',  3, 'GPS baudrate see BAUD_RATE for details'),
         None,
         ('SAT',  'detailed satellite status transmission'),
         ('SUM',  'satellite summary transmission'),
         ('VEL',  'GPS course and velocity transmission'),
         ('REL',  'GPS relative position transmission'),
         ('POS',  'GPS position transmission'),
         ('TEMP', 'temperature transmission'),
         ('COV',  'covariance matrix transmission'),
         ('EU',   'euler angles transmission'),
         ('QT',   'quaternion transmission'),
         ('MP',   'processed magnetometer transmission'),
         ('AP',   'processed accelerometer transmission'),
         ('GP',   'processed gyroscope transmission'),
         ('MR',   'raw magnetometer transmission'),
         ('AR',   'raw accelerometer transmission'),
         ('GR',   'raw gyroscope transmission'),
         ('BEN',  'broadcast mode'),
         None
      ]
   ),
   ('MISC_CONFIG', 0x01, 32, 'miscellaneous configuration options',
      [
         (None,   27),
         ('PPS',  'PPS timing enabled'),
         ('QUAT', 'quaterion estimation enabled'),
         ('CAL',  'start-up gyroscope calibration enabled'),
         ('AUE',  'EKF accelerometer updated enabled'),
         ('MUE',  'EKF magnetometer updates enabled')
      ]
   ),
   ('MAG_REF_X', 0x02, 32),
   ('MAG_REF_Y', 0x03, 32),
   ('MAG_REF_Z', 0x04, 32),
   ('ACC_REF_X', 0x05, 32),
   ('ACC_REF_Y', 0x06, 32),
   ('ACC_REF_Z', 0x07, 32),
   ('EKF_MAG_VAR', 0x08, 32),
   ('EKF_ACC_VAR', 0x09, 32),
   ('EKF_PROC_VAR', 0x0A, 32),
   ('GYRO_BIAS_XY', 0x0B, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('GYRO_BIAS_Z', 0x0C, 32,
      [
         ('X', 16),
         (None, 16)
      ]
   ),
   ('ACC_BIAS_XY', 0x0D, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('ACC_BIAS_Z', 0x0E, 32,
      [
         ('X', 16),
         (None, 16)
      ]
   ),
   ('MAG_BIAS_XY', 0x0F, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('MAG_BIAS_Z', 0x10, 32,
      [
         ('X', 16),
         (None, 16)
      ]
   ),
   ('ACC_CAL_00', 0x11, 32),
   ('ACC_CAL_01', 0x12, 32),
   ('ACC_CAL_02', 0x13, 32),
   ('ACC_CAL_11', 0x14, 32),
   ('ACC_CAL_12', 0x15, 32),
   ('ACC_CAL_13', 0x16, 32),
   ('ACC_CAL_21', 0x16, 32),
   ('ACC_CAL_22', 0x18, 32),
   ('ACC_CAL_23', 0x19, 32),
   ('GYRO_CAL_00', 0x1A, 32),
   ('GYRO_CAL_01', 0x1B, 32),
   ('GYRO_CAL_02', 0x1C, 32),
   ('GYRO_CAL_11', 0x1D, 32),
   ('GYRO_CAL_12', 0x1E, 32),
   ('GYRO_CAL_13', 0x1F, 32),
   ('GYRO_CAL_21', 0x20, 32),
   ('GYRO_CAL_22', 0x21, 32),
   ('GYRO_CAL_23', 0x22, 32),
   ('MAG_CAL_00', 0x23, 32),
   ('MAG_CAL_01', 0x24, 32),
   ('MAG_CAL_02', 0x25, 32),
   ('MAG_CAL_11', 0x26, 32),
   ('MAG_CAL_12', 0x27, 32),
   ('MAG_CAL_13', 0x28, 32),
   ('MAG_CAL_21', 0x29, 32),
   ('MAG_CAL_22', 0x2A, 32),
   ('MAG_CAL_23', 0x2B, 32),
   ('GYROX_BIAS_C0', 0x2C, 32),
   ('GYROX_BIAS_C1', 0x2D, 32),
   ('GYROX_BIAS_C2', 0x2E, 32),
   ('GYROX_BIAS_C3', 0x2F, 32),
   ('GYROY_BIAS_C0', 0x30, 32),
   ('GYROY_BIAS_C1', 0x31, 32),
   ('GYROY_BIAS_C2', 0x32, 32),
   ('GYROY_BIAS_C3', 0x33, 32),
   ('GYROZ_BIAS_C0', 0x34, 32),
   ('GYROZ_BIAS_C1', 0x35, 32),
   ('GYROZ_BIAS_C2', 0x36, 32),
   ('GYROZ_BIAS_C3', 0x37, 32),
   # UM6 DATA REGISTERS:
   ('STATUS', 0x55, 32, 'status',
      [
         ('ST', 'self-test complete'),
         (None, 12),
         ('MAG_DEL', 'magnetometer data delay'),
         ('ACC_DEL', 'accelerometer date delay'),
         ('GYR_DEL', 'gyroscope data delay'),
         ('EKF_DIV', 'extended kalman filter diverged'),
         ('BUS_MAG', 'magnetometer bus error'),
         ('BUS_ACC', 'accelerometer bus error'),
         ('BUS_GYR', 'gyroscope bus error'),
         ('ST_MZ',   'self-test failed for magnetometer z axis'),
         ('ST_MY',   'self-test failed for magnetometer y axis'),
         ('ST_MX',   'self-test failed for magnetometer x axis'),
         ('ST_AZ',   'self-test failed for accelerometer z axis'),
         ('ST_AY',   'self-test failed for accelerometer y axis'),
         ('ST_AX',   'self-test failed for accelerometer x axis'),
         ('ST_GZ',   'self-test failed for gyroscope z axis'),
         ('ST_GY',   'self-test failed for gyroscope y axis'),
         ('ST_GX',   'self-test failed for gyroscope x axis'),
         ('GYR_INI', 'gyroscope init failed'),
         ('ACC_INI', 'accelerometer init failed'),
         ('MAG_INI', 'magnetometer init failed')
      ]
   ),
   ('GYRO_RAW1', 0x56, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('GYRO_RAW2', 0x57, 32,
      [
         ('Z', 16),
         (None, 16)
      ]
   ),
   ('ACC_RAW1', 0x58, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('ACC_RAW2', 0x59, 32,
      [
         ('Z', 16),
         (None, 16)
      ]
   ),
   ('MAG_RAW1', 0x5A, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('MAG_RAW2', 0x5B, 32,
      [
         ('Z', 16),
         (None, 16)
      ]
   ),
   ('GYRO_PROC1', 0x5C, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('GYRO_PROC2', 0x5D, 32,
      [
         ('Z', 16),
         (None, 16)
      ]
   ),
   ('ACC_PROC1', 0x5E, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('ACC_PROC2', 0x5F, 32,
      [
         ('Z', 16),
         (None, 16)
      ]
   ),
   ('MAG_PROC1', 0x60, 32,
      [
         ('X', 16),
         ('Y', 16)
      ]
   ),
   ('MAG_PROC2', 0x61, 32,
      [
         ('Z', 16),
         (None, 16)
      ]
   ),
   ('EULER1', 0x62, 32,
      [
         ('PHI', 16),
         ('THETA', 16)
      ]
   ),
   ('EULER2', 0x63, 32,
      [
         ('PSI', 16),
         (None, 16)
      ]
   ),
   ('QUAT1', 0x64, 32,
      [
         ('A', 16),
         ('B', 16)
      ]
   ),
   ('QUAT2', 0x65, 32,
      [
         ('C', 16),
         ('D', 16)
      ]
   ),
   ('ERROR_COV_00', 0x66, 32),
   ('ERROR_COV_01', 0x67, 32),
   ('ERROR_COV_02', 0x68, 32),
   ('ERROR_COV_03', 0x69, 32),
   ('ERROR_COV_10', 0x6A, 32),
   ('ERROR_COV_11', 0x6B, 32),
   ('ERROR_COV_12', 0x6C, 32),
   ('ERROR_COV_13', 0x6D, 32),
   ('ERROR_COV_20', 0x6E, 32),
   ('ERROR_COV_21', 0x6F, 32),
   ('ERROR_COV_22', 0x70, 32),
   ('ERROR_COV_23', 0x71, 32),
   ('ERROR_COV_30', 0x72, 32),
   ('ERROR_COV_31', 0x73, 32),
   ('ERROR_COV_32', 0x74, 32),
   ('ERROR_COV_33', 0x75, 32),
   ('TEMPERATURE', 0x76, 32),
   ('GPS_LONGITUDE', 0x77, 32),
   ('GPS_LATITUDE', 0x78, 32),
   ('GPS_ALTITUDE', 0x79, 32),
   ('GPS_POS_NORTH', 0x7A, 32),
   ('GPS_POS_EAST', 0x7B, 32),
   ('GPS_POS_HEIGHT', 0x7C, 32),
   ('GPS_COURSE_SPEED', 0x7D, 32,
      [
         ('COURCE', 16),
         ('SPEED', 16)
      ]
   ),
   ('GPS_SAT_SUMMARY', 0x7E, 32, 'status',
      [
         ('MODE',      2, 'fix mode'),
         ('SAT_COUNT', 4, 'satellite count'),
         ('HDOP',      10, 'horizontal dillusion of precision'),
         ('VDOP',      10, 'vertical dillusion of precision'),
         (None,        6)
      ]
   ),
   ('GPS_SAT_XY_0', 0x7F, 32,
      [
         ('X_ID', 8),
         ('X_SNR', 8),
         ('Y_ID', 8),
         ('Y_SNR', 8)
      ]
   ),
   ('GPS_SAT_XY_1', 0x80, 32,
      [
         ('X_ID', 8),
         ('X_SNR', 8),
         ('Y_ID', 8),
         ('Y_SNR', 8)
      ]
   ),
   ('GPS_SAT_XY_2', 0x81, 32,
      [
         ('X_ID', 8),
         ('X_SNR', 8),
         ('Y_ID', 8),
         ('Y_SNR', 8)
      ]
   ),
   ('GPS_SAT_XY_3', 0x82, 32,
      [
         ('X_ID', 8),
         ('X_SNR', 8),
         ('Y_ID', 8),
         ('Y_SNR', 8)
      ]
   ),
   ('GPS_SAT_XY_4', 0x83, 32,
      [
         ('X_ID', 8),
         ('X_SNR', 8),
         ('Y_ID', 8),
         ('Y_SNR', 8)
      ]
   ),
   ('GPS_SAT_XY_5', 0x84, 32,
      [
         ('X_ID', 8),
         ('X_SNR', 8),
         ('Y_ID', 8),
         ('Y_SNR', 8)
      ]
   ),
   ('GET_FW_VERSION', 0xAA, 0),
   ('FLASH_COMMIT', 0xAB, 0),
   ('ZERO_GYROS', 0xAC, 0),
   ('RESET_EKF', 0xAD, 0),
   ('GET_DATA', 0xAE, 0),
   ('SET_ACC_REF', 0xAF, 0),
   ('SET_MAG_REF', 0xB0, 0),
   ('RESET_TO_FACTORY', 0xB1, 0),
   ('SET_HOME_POS', 0xB3, 0),
   ('BAD_CHECKSUM', 0xFD, 0),
   ('UNKNOWN_ADDRESS', 0xFE, 0),
   ('INVALID_BATCH_SIZE', 0xFF, 0),
]

