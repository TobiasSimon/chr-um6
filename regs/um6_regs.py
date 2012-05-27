
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
   ('GYRO_RAW2', 0x57, 32, # this one is not sent individually - data follows GYRO_PROC1.
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
   ('GYRO_PROC2', 0x5D, 32, # this one is not sent individually - data follows GYRO_PROC1.
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
   ('ACC_PROC2', 0x5F, 32, # this one is not sent individually - data follows ACC_PROC1.
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
   ('MAG_PROC2', 0x61, 32, # this one is not sent individually - data follows MAG_PROC1.
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
   ('EULER2', 0x63, 32, # this one is not sent individually - data follows EULER1.
      [
         ('PSI', 16),
         (None, 16)
      ]
   ),
   ('TEMPERATURE', 0x76, 32)

]

