/*
 * gps.h
 *
 *  Created on: Jan 29, 2018
 *      Author: kiaxa
 */

#ifndef SRC_GPS_H_
#define SRC_GPS_H_

#include <stdint.h>

#define GPS_DEVICE_ADDR (0x05)

#define GPS_SCAN_ID (0)   // 4 bytes
#define GPS_SCAN_SIZE (4) // 0,0,0,Device address

#define GPS_UTC_DATE_TIME_ID (1)   // YMDHMS
#define GPS_UTC_DATE_TIME_SIZE (6) // 6 bytes

#define GPS_STATUS_ID (2)   // A/V
#define GPS_STATUS_SIZE (1) // 1 byte

#define GPS_LATITUDE_ID (3)   // dd.dddddd
#define GPS_LATITUDE_SIZE (9) // 9 bytes

#define GPS_NS_ID (4)   // N/S
#define GPS_NS_SIZE (1) // 1 byte

#define GPS_LONGITUDE_ID (5)	// ddd.dddddd
#define GPS_LONGITUDE_SIZE (10) // 10 bytes

#define GPS_EW_ID (6)   // E/W
#define GPS_EW_SIZE (1) // 1 byte

#define GPS_SPEED_ID (7)   // 000.0~999.9 Knots
#define GPS_SPEED_SIZE (5) // 5 bytes

#define GPS_COURSE_ID (8)   // 000.0~359.9
#define GPS_COURSE_SIZE (5) // 5 bytes

#define GPS_POSITION_FIX_ID (9)   // 0,1,2,6
#define GPS_POSITION_FIX_SIZE (1) // 1 byte

#define GPS_SATE_USED_ID (10)  // 00~12
#define GPS_SATE_USED_SIZE (2) // 2 bytes

#define GPS_ALTITUDE_ID (11)  // -9999.9~99999.9
#define GPS_ALTITUDE_SIZE (7) // 7 bytes

#define GPS_MODE_ID (12)  // A/M
#define GPS_MODE_SIZE (1) // 1 byte

#define GPS_MODE2_ID (13)  // 1,2,3
#define GPS_MODE2_SIZE (1) // 1 byte

#define GPS_SATE_IN_VIEW_ID (14)  // 0~12
#define GPS_SATE_IN_VIEW_SIZE (1) // 1 byte

/*Degrees-minutes-seconds coordinate format struct
	dd° mm' ss" */
typedef struct coord_dms
{
	int deg;
	int min;
	int sec;
} dms_t;

/****************************************************************************
 * Name: gps_init
 *
 * Description:
 * 		Initializes the I2C bus for the GPS module and sets the I2C slave 
 * 		address for the I2C port to the address of the GPS module
 * 
 * Inputs:
 * 		-port:	I2C port number 0 or 1
 * 
 * Returned Value:
 * 		State of initialization: 0 (success) or 1 (failure)
 *
 ****************************************************************************/
uint8_t gps_init(int port);

/****************************************************************************
 * Name: gps_check_online
 *
 * Description:
 * 		Checks if the GPS is available on the I2C bus. GPS module will 
 * 		return its I2C address as in the form of the packet 
 * 		{0,0,0,GPS_DEVICE_ADDRESS}
 * 
 * Returned Value:
 * 		GPS presence: Online (1) or Offline(0)
 *
 ****************************************************************************/
uint8_t gps_check_online(void);

/****************************************************************************
 * Name: gps_get_utc_date_time
 *
 * Description:
 * 		Gets UTC date and time from GPS module
 * 
 * Returned Value:
 * 		Pointer to array containing UTC date and time. Format: {Y,M,D,H,M,S}
 *
 ****************************************************************************/
uint8_t *gps_get_utc_date_time(void);

/****************************************************************************
 * Name: gps_get_status
 *
 * Description:
 * 		Gets the status information of the GPS.
 * 
 * Returned Value:
 * 		GPS status
 *
 ****************************************************************************/
uint8_t gps_get_status(void);

/****************************************************************************
 * Name: gps_get_latitude
 *
 * Description:
 * 		Gets latitude information from GPS
 * 
 * Returned Value:
 * 		Latitude in decimal degree format
 *
 ****************************************************************************/
float gps_get_latitude(void);

/****************************************************************************
 * Name: gps_get_ns
 *
 * Description:
 * 		Gets North/South information from GPS
 * 
 * Returned Value:
 * 		Ascii character: 'N','S', or '-'
 *
 ****************************************************************************/
uint8_t gps_get_ns(void);

/****************************************************************************
 * Name: gps_get_longitude
 *
 * Description:
 *		Gets longitude information from GPS
 * 
 * Returned Value:
 *		Longitude in decimal degree format
 *
 ****************************************************************************/
float gps_get_longitude(void);

/****************************************************************************
 * Name: gps_get_ew
 *
 * Description:
 * 		Gets East/West information from GPS
 * 
 * Returned Value:
 * 		Ascii character: 'E','W', or '-'
 *
 ****************************************************************************/
uint8_t gps_get_ew(void);

/****************************************************************************
 * Name: gps_get_speed
 *
 * Description:
 *		Gets current travel speed from GPS
 * 
 * Returned Value:
 *
 ****************************************************************************/
float gps_get_speed(void);

/****************************************************************************
 * Name: gps_get_course
 *
 * Description:
 *		Get course information from GPS
 * 
 * Returned Value:
 *		Course in decimal degree format
 *
 ****************************************************************************/
float gps_get_course(void);

/****************************************************************************
 * Name: gps_get_position_fix
 *
 * Description:
 *		Get position fix status from GPS
 * 
 * Returned Value:
 *		1,2,4, or 6
 *
 ****************************************************************************/
uint8_t gps_get_position_fix(void);

/****************************************************************************
 * Name: gps_get_sate_used
 *
 * Description:
 *		Get number of satelites used
 * 
 * Returned Value:
 *		id of sate used, format 00~12
 *
 ****************************************************************************/
uint8_t gps_get_sate_used(void);

/****************************************************************************
 * Name: gps_get_altitude
 *
 * Description:
 *		Get current altitude
 * 
 * Returned Value:
 *		Altitude 
 *
 ****************************************************************************/
float gps_get_altitude(void);

/****************************************************************************
 * Name: gps_get_mode
 *
 * Description:
 * 		Get current locate mode
 * 
 * Returned Value:
 *		Mode A/M
 *
 ****************************************************************************/
uint8_t gps_get_mode(void);

/****************************************************************************
 * Name: gps_get_mode2
 *
 * Description:
 * 		Get current status
 * 
 * Returned Value:
 *		format 1,2,3
 *
 ****************************************************************************/
uint8_t gps_get_mode2(void);

/****************************************************************************
 * Name: gps_get_sate_in_view
 *
 * Description: 
 * 		Get id of sate in view
 * 
 * Returned Value:
 *		sate in view
 *
 ****************************************************************************/
uint8_t gps_get_sate_in_view(void);

/****************************************************************************
 * Name:
 *
 * Description:
 * 
 * Inputs:
 *		-coord 	Degrees-minutes-seconds struct pointer for DMS value
 *		-latlon	Latitude/Longitude in decimal degree format
 *
 ****************************************************************************/
void degtodms(dms_t *coord, float latlon);

/****************************************************************************
 * Name: print_location
 *
 * Description:
 * 		Prints current location coordinates in DMS format
 *
 ****************************************************************************/
void print_location(void);

#endif /* SRC_GPS_H_ */
