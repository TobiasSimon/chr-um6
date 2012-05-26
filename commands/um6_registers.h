
/* 
 * AUTOGENERATED FILE - DO NOT EDIT!
 * file generated using creghead: https://github.com/TobiasSimon/creghead
 */


#ifndef __UM6_REGS_H__
#define __UM6_REGS_H__



/* communication settings */
#define UM6_COMM (0x0)
/* packet broadcast frequency; freq = (280 / 255) * broadcast_rate + 20 */
#define UM6_COMM_GET_BC_RATE(x) \
   (((x) >> 0) & 0xff)
#define UM6_COMM_SET_BC_RATE(x, v) \
   do {x &= ~(0xff << 0); x |= (v & 0xff) << 0;} while(0)

/* serial port baudrate; 000: 9600, 001: 14400, 010: 19200, 011 -> 38400, 100 -> 57600, 101 -> 115200 */
#define UM6_COMM_GET_BAUD_RATE(x) \
   (((x) >> 8) & 0x7)
#define UM6_COMM_SET_BAUD_RATE(x, v) \
   do {x &= ~(0x7 << 8); x |= (v & 0x7) << 8;} while(0)

/* GPS baudrate see BAUD_RATE for details */
#define UM6_COMM_GET_GPS_BAUD(x) \
   (((x) >> 11) & 0x7)
#define UM6_COMM_SET_GPS_BAUD(x, v) \
   do {x &= ~(0x7 << 11); x |= (v & 0x7) << 11;} while(0)

/* bit 14 ignored */

/* detailed satellite status transmission */
#define UM6_COMM_GET_SAT(x) \
   (((x) >> 15) & 1)
#define UM6_COMM_SET_SAT(x) \
   do {x |= 1 << 15;} while (0)
#define UM6_COMM_CLEAR_SAT(x) \
   do {x &= ~(1 << 15);} while (0)

/* satellite summary transmission */
#define UM6_COMM_GET_SUM(x) \
   (((x) >> 16) & 1)
#define UM6_COMM_SET_SUM(x) \
   do {x |= 1 << 16;} while (0)
#define UM6_COMM_CLEAR_SUM(x) \
   do {x &= ~(1 << 16);} while (0)

/* GPS course and velocity transmission */
#define UM6_COMM_GET_VEL(x) \
   (((x) >> 17) & 1)
#define UM6_COMM_SET_VEL(x) \
   do {x |= 1 << 17;} while (0)
#define UM6_COMM_CLEAR_VEL(x) \
   do {x &= ~(1 << 17);} while (0)

/* GPS relative position transmission */
#define UM6_COMM_GET_REL(x) \
   (((x) >> 18) & 1)
#define UM6_COMM_SET_REL(x) \
   do {x |= 1 << 18;} while (0)
#define UM6_COMM_CLEAR_REL(x) \
   do {x &= ~(1 << 18);} while (0)

/* GPS position transmission */
#define UM6_COMM_GET_POS(x) \
   (((x) >> 19) & 1)
#define UM6_COMM_SET_POS(x) \
   do {x |= 1 << 19;} while (0)
#define UM6_COMM_CLEAR_POS(x) \
   do {x &= ~(1 << 19);} while (0)

/* temperature transmission */
#define UM6_COMM_GET_TEMP(x) \
   (((x) >> 20) & 1)
#define UM6_COMM_SET_TEMP(x) \
   do {x |= 1 << 20;} while (0)
#define UM6_COMM_CLEAR_TEMP(x) \
   do {x &= ~(1 << 20);} while (0)

/* covariance matrix transmission */
#define UM6_COMM_GET_COV(x) \
   (((x) >> 21) & 1)
#define UM6_COMM_SET_COV(x) \
   do {x |= 1 << 21;} while (0)
#define UM6_COMM_CLEAR_COV(x) \
   do {x &= ~(1 << 21);} while (0)

/* euler angles transmission */
#define UM6_COMM_GET_EU(x) \
   (((x) >> 22) & 1)
#define UM6_COMM_SET_EU(x) \
   do {x |= 1 << 22;} while (0)
#define UM6_COMM_CLEAR_EU(x) \
   do {x &= ~(1 << 22);} while (0)

/* quaternion transmission */
#define UM6_COMM_GET_QT(x) \
   (((x) >> 23) & 1)
#define UM6_COMM_SET_QT(x) \
   do {x |= 1 << 23;} while (0)
#define UM6_COMM_CLEAR_QT(x) \
   do {x &= ~(1 << 23);} while (0)

/* processed magnetometer transmission */
#define UM6_COMM_GET_MP(x) \
   (((x) >> 24) & 1)
#define UM6_COMM_SET_MP(x) \
   do {x |= 1 << 24;} while (0)
#define UM6_COMM_CLEAR_MP(x) \
   do {x &= ~(1 << 24);} while (0)

/* processed accelerometer transmission */
#define UM6_COMM_GET_AP(x) \
   (((x) >> 25) & 1)
#define UM6_COMM_SET_AP(x) \
   do {x |= 1 << 25;} while (0)
#define UM6_COMM_CLEAR_AP(x) \
   do {x &= ~(1 << 25);} while (0)

/* processed gyroscope transmission */
#define UM6_COMM_GET_GP(x) \
   (((x) >> 26) & 1)
#define UM6_COMM_SET_GP(x) \
   do {x |= 1 << 26;} while (0)
#define UM6_COMM_CLEAR_GP(x) \
   do {x &= ~(1 << 26);} while (0)

/* raw magnetometer transmission */
#define UM6_COMM_GET_MR(x) \
   (((x) >> 27) & 1)
#define UM6_COMM_SET_MR(x) \
   do {x |= 1 << 27;} while (0)
#define UM6_COMM_CLEAR_MR(x) \
   do {x &= ~(1 << 27);} while (0)

/* raw accelerometer transmission */
#define UM6_COMM_GET_AR(x) \
   (((x) >> 28) & 1)
#define UM6_COMM_SET_AR(x) \
   do {x |= 1 << 28;} while (0)
#define UM6_COMM_CLEAR_AR(x) \
   do {x &= ~(1 << 28);} while (0)

/* raw gyroscope transmission */
#define UM6_COMM_GET_GR(x) \
   (((x) >> 29) & 1)
#define UM6_COMM_SET_GR(x) \
   do {x |= 1 << 29;} while (0)
#define UM6_COMM_CLEAR_GR(x) \
   do {x &= ~(1 << 29);} while (0)

/* broadcast mode */
#define UM6_COMM_GET_BEN(x) \
   (((x) >> 30) & 1)
#define UM6_COMM_SET_BEN(x) \
   do {x |= 1 << 30;} while (0)
#define UM6_COMM_CLEAR_BEN(x) \
   do {x &= ~(1 << 30);} while (0)

/* bit 31 ignored */

#define UM6_COMM_DEBUG(x) \
   do { printf("COMM: BC_RATE = %X, "\
      "BAUD_RATE = %X, "\
      "GPS_BAUD = %X, "\
      "SAT = %X, "\
      "SUM = %X, "\
      "VEL = %X, "\
      "REL = %X, "\
      "POS = %X, "\
      "TEMP = %X, "\
      "COV = %X, "\
      "EU = %X, "\
      "QT = %X, "\
      "MP = %X, "\
      "AP = %X, "\
      "GP = %X, "\
      "MR = %X, "\
      "AR = %X, "\
      "GR = %X, "\
      "BEN = %X\n", UM6_COMM_GET_BC_RATE(x), \
      UM6_COMM_GET_BAUD_RATE(x), \
      UM6_COMM_GET_GPS_BAUD(x), \
      UM6_COMM_GET_SAT(x), \
      UM6_COMM_GET_SUM(x), \
      UM6_COMM_GET_VEL(x), \
      UM6_COMM_GET_REL(x), \
      UM6_COMM_GET_POS(x), \
      UM6_COMM_GET_TEMP(x), \
      UM6_COMM_GET_COV(x), \
      UM6_COMM_GET_EU(x), \
      UM6_COMM_GET_QT(x), \
      UM6_COMM_GET_MP(x), \
      UM6_COMM_GET_AP(x), \
      UM6_COMM_GET_GP(x), \
      UM6_COMM_GET_MR(x), \
      UM6_COMM_GET_AR(x), \
      UM6_COMM_GET_GR(x), \
      UM6_COMM_GET_BEN(x)); } while(0)



/* status */
#define UM6_STATUS (0x55)
/* self-test complete */
#define UM6_STATUS_GET_ST(x) \
   (((x) >> 0) & 1)
#define UM6_STATUS_SET_ST(x) \
   do {x |= 1 << 0;} while (0)
#define UM6_STATUS_CLEAR_ST(x) \
   do {x &= ~(1 << 0);} while (0)

/* bit 1 ignored */

/* magnetometer data delay */
#define UM6_STATUS_GET_MAG_DEL(x) \
   (((x) >> 13) & 1)
#define UM6_STATUS_SET_MAG_DEL(x) \
   do {x |= 1 << 13;} while (0)
#define UM6_STATUS_CLEAR_MAG_DEL(x) \
   do {x &= ~(1 << 13);} while (0)

/* accelerometer date delay */
#define UM6_STATUS_GET_ACC_DEL(x) \
   (((x) >> 14) & 1)
#define UM6_STATUS_SET_ACC_DEL(x) \
   do {x |= 1 << 14;} while (0)
#define UM6_STATUS_CLEAR_ACC_DEL(x) \
   do {x &= ~(1 << 14);} while (0)

/* gyroscope data delay */
#define UM6_STATUS_GET_GYR_DEL(x) \
   (((x) >> 15) & 1)
#define UM6_STATUS_SET_GYR_DEL(x) \
   do {x |= 1 << 15;} while (0)
#define UM6_STATUS_CLEAR_GYR_DEL(x) \
   do {x &= ~(1 << 15);} while (0)

/* extended kalman filter diverged */
#define UM6_STATUS_GET_EKF_DIV(x) \
   (((x) >> 16) & 1)
#define UM6_STATUS_SET_EKF_DIV(x) \
   do {x |= 1 << 16;} while (0)
#define UM6_STATUS_CLEAR_EKF_DIV(x) \
   do {x &= ~(1 << 16);} while (0)

/* magnetometer bus error */
#define UM6_STATUS_GET_BUS_MAG(x) \
   (((x) >> 17) & 1)
#define UM6_STATUS_SET_BUS_MAG(x) \
   do {x |= 1 << 17;} while (0)
#define UM6_STATUS_CLEAR_BUS_MAG(x) \
   do {x &= ~(1 << 17);} while (0)

/* accelerometer bus error */
#define UM6_STATUS_GET_BUS_ACC(x) \
   (((x) >> 18) & 1)
#define UM6_STATUS_SET_BUS_ACC(x) \
   do {x |= 1 << 18;} while (0)
#define UM6_STATUS_CLEAR_BUS_ACC(x) \
   do {x &= ~(1 << 18);} while (0)

/* gyroscope bus error */
#define UM6_STATUS_GET_BUS_GYR(x) \
   (((x) >> 19) & 1)
#define UM6_STATUS_SET_BUS_GYR(x) \
   do {x |= 1 << 19;} while (0)
#define UM6_STATUS_CLEAR_BUS_GYR(x) \
   do {x &= ~(1 << 19);} while (0)

/* self-test failed for magnetometer z axis */
#define UM6_STATUS_GET_ST_MZ(x) \
   (((x) >> 20) & 1)
#define UM6_STATUS_SET_ST_MZ(x) \
   do {x |= 1 << 20;} while (0)
#define UM6_STATUS_CLEAR_ST_MZ(x) \
   do {x &= ~(1 << 20);} while (0)

/* self-test failed for magnetometer y axis */
#define UM6_STATUS_GET_ST_MY(x) \
   (((x) >> 21) & 1)
#define UM6_STATUS_SET_ST_MY(x) \
   do {x |= 1 << 21;} while (0)
#define UM6_STATUS_CLEAR_ST_MY(x) \
   do {x &= ~(1 << 21);} while (0)

/* self-test failed for magnetometer x axis */
#define UM6_STATUS_GET_ST_MX(x) \
   (((x) >> 22) & 1)
#define UM6_STATUS_SET_ST_MX(x) \
   do {x |= 1 << 22;} while (0)
#define UM6_STATUS_CLEAR_ST_MX(x) \
   do {x &= ~(1 << 22);} while (0)

/* self-test failed for accelerometer z axis */
#define UM6_STATUS_GET_ST_AZ(x) \
   (((x) >> 23) & 1)
#define UM6_STATUS_SET_ST_AZ(x) \
   do {x |= 1 << 23;} while (0)
#define UM6_STATUS_CLEAR_ST_AZ(x) \
   do {x &= ~(1 << 23);} while (0)

/* self-test failed for accelerometer y axis */
#define UM6_STATUS_GET_ST_AY(x) \
   (((x) >> 24) & 1)
#define UM6_STATUS_SET_ST_AY(x) \
   do {x |= 1 << 24;} while (0)
#define UM6_STATUS_CLEAR_ST_AY(x) \
   do {x &= ~(1 << 24);} while (0)

/* self-test failed for accelerometer x axis */
#define UM6_STATUS_GET_ST_AX(x) \
   (((x) >> 25) & 1)
#define UM6_STATUS_SET_ST_AX(x) \
   do {x |= 1 << 25;} while (0)
#define UM6_STATUS_CLEAR_ST_AX(x) \
   do {x &= ~(1 << 25);} while (0)

/* self-test failed for gyroscope z axis */
#define UM6_STATUS_GET_ST_GZ(x) \
   (((x) >> 26) & 1)
#define UM6_STATUS_SET_ST_GZ(x) \
   do {x |= 1 << 26;} while (0)
#define UM6_STATUS_CLEAR_ST_GZ(x) \
   do {x &= ~(1 << 26);} while (0)

/* self-test failed for gyroscope y axis */
#define UM6_STATUS_GET_ST_GY(x) \
   (((x) >> 27) & 1)
#define UM6_STATUS_SET_ST_GY(x) \
   do {x |= 1 << 27;} while (0)
#define UM6_STATUS_CLEAR_ST_GY(x) \
   do {x &= ~(1 << 27);} while (0)

/* self-test failed for gyroscope x axis */
#define UM6_STATUS_GET_ST_GX(x) \
   (((x) >> 28) & 1)
#define UM6_STATUS_SET_ST_GX(x) \
   do {x |= 1 << 28;} while (0)
#define UM6_STATUS_CLEAR_ST_GX(x) \
   do {x &= ~(1 << 28);} while (0)

/* gyroscope init failed */
#define UM6_STATUS_GET_GYR_INI(x) \
   (((x) >> 29) & 1)
#define UM6_STATUS_SET_GYR_INI(x) \
   do {x |= 1 << 29;} while (0)
#define UM6_STATUS_CLEAR_GYR_INI(x) \
   do {x &= ~(1 << 29);} while (0)

/* accelerometer init failed */
#define UM6_STATUS_GET_ACC_INI(x) \
   (((x) >> 30) & 1)
#define UM6_STATUS_SET_ACC_INI(x) \
   do {x |= 1 << 30;} while (0)
#define UM6_STATUS_CLEAR_ACC_INI(x) \
   do {x &= ~(1 << 30);} while (0)

/* magnetometer init failed */
#define UM6_STATUS_GET_MAG_INI(x) \
   (((x) >> 31) & 1)
#define UM6_STATUS_SET_MAG_INI(x) \
   do {x |= 1 << 31;} while (0)
#define UM6_STATUS_CLEAR_MAG_INI(x) \
   do {x &= ~(1 << 31);} while (0)

#define UM6_STATUS_DEBUG(x) \
   do { printf("STATUS: ST = %X, "\
      "MAG_DEL = %X, "\
      "ACC_DEL = %X, "\
      "GYR_DEL = %X, "\
      "EKF_DIV = %X, "\
      "BUS_MAG = %X, "\
      "BUS_ACC = %X, "\
      "BUS_GYR = %X, "\
      "ST_MZ = %X, "\
      "ST_MY = %X, "\
      "ST_MX = %X, "\
      "ST_AZ = %X, "\
      "ST_AY = %X, "\
      "ST_AX = %X, "\
      "ST_GZ = %X, "\
      "ST_GY = %X, "\
      "ST_GX = %X, "\
      "GYR_INI = %X, "\
      "ACC_INI = %X, "\
      "MAG_INI = %X\n", UM6_STATUS_GET_ST(x), \
      UM6_STATUS_GET_MAG_DEL(x), \
      UM6_STATUS_GET_ACC_DEL(x), \
      UM6_STATUS_GET_GYR_DEL(x), \
      UM6_STATUS_GET_EKF_DIV(x), \
      UM6_STATUS_GET_BUS_MAG(x), \
      UM6_STATUS_GET_BUS_ACC(x), \
      UM6_STATUS_GET_BUS_GYR(x), \
      UM6_STATUS_GET_ST_MZ(x), \
      UM6_STATUS_GET_ST_MY(x), \
      UM6_STATUS_GET_ST_MX(x), \
      UM6_STATUS_GET_ST_AZ(x), \
      UM6_STATUS_GET_ST_AY(x), \
      UM6_STATUS_GET_ST_AX(x), \
      UM6_STATUS_GET_ST_GZ(x), \
      UM6_STATUS_GET_ST_GY(x), \
      UM6_STATUS_GET_ST_GX(x), \
      UM6_STATUS_GET_GYR_INI(x), \
      UM6_STATUS_GET_ACC_INI(x), \
      UM6_STATUS_GET_MAG_INI(x)); } while(0)

#endif /* __UM6_REGS_H__ */

