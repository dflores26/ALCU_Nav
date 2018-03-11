/*
 * gps.c
 *
 *  Created on: Jan 29, 2018
 *      Author: kiaxa
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <tinyara/i2c.h>
#include "gps.h"

/* Uncomment to use original i2c code (Doesn't seem to work) */
//#define I2C_ORIGINAL

static struct i2c_dev_s *i2c_dev;
static struct i2c_config_s configs;

uint8_t gps_utc_date_time[GPS_UTC_DATE_TIME_SIZE]={0};

uint8_t gps_init(int port)
{
	i2c_dev = up_i2cinitialize(port);
	if (i2c_dev == NULL) {
		printf("up_i2cinitialize failed(i2c:%d)\n", port);
		fflush(stdout);
		return 0;
	}

	configs.frequency = 100000;
	configs.address = GPS_DEVICE_ADDR;
	configs.addrlen = 7;
	return 1;
}

uint8_t gps_check_online(void)
{
	uint8_t data[GPS_SCAN_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_SCAN_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_SCAN_SIZE+2));
#else
	for(i=0;i<(GPS_SCAN_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	if(data[5]==GPS_DEVICE_ADDR) return 1;
	else return 0;
}

uint8_t* gps_get_utc_date_time(void)
{
	uint8_t data[GPS_UTC_DATE_TIME_SIZE+2];
	uint8_t i;
	uint8_t dtmp[1];
	uint8_t reg[1];
	reg[0] = GPS_UTC_DATE_TIME_ID;
	int j;

	i2c_write(i2c_dev, &configs, reg, 1);

#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_UTC_DATE_TIME_SIZE+2));
#else
	for(j=0;j<(GPS_UTC_DATE_TIME_SIZE+2);j++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[j] = dtmp[0];
	}
#endif
	for(i=0;i<GPS_UTC_DATE_TIME_SIZE;i++)
		gps_utc_date_time[i] = data[i+2];

	return gps_utc_date_time;
}

uint8_t gps_get_status(void)
{
	uint8_t data[GPS_STATUS_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_STATUS_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_STATUS_SIZE+2));
#else
	for(i=0;i<(GPS_STATUS_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return data[2];
}

float gps_get_latitude(void)
{
	uint8_t data[GPS_LATITUDE_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_LATITUDE_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_LATITUDE_SIZE+2));
#else
	for(i=0;i<(GPS_LATITUDE_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return atof(&data[2]);
}

uint8_t gps_get_ns(void)
{
	uint8_t data[GPS_NS_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_NS_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_NS_SIZE+2));
#else
	for(i=0;i<(GPS_NS_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
    if(data[2] == 'N' || data[2] == 'S')return data[2];
    else return data[2] = '-';

}

float gps_get_longitude(void)
{
	uint8_t data[GPS_LONGITUDE_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_LONGITUDE_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_LONGITUDE_SIZE+2));
#else
	for(i=0;i<(GPS_LONGITUDE_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return atof(&data[2]);
}

uint8_t gps_get_ew(void)
{
	uint8_t data[GPS_EW_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_EW_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_EW_SIZE+2));
#else
	for(i=0;i<(GPS_EW_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	if(data[2] == 'E' || data[2] == 'W')return data[2];
	else return data[2] = '-';
}

float gps_get_speed(void)
{
	uint8_t data[GPS_SPEED_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_SPEED_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_SPEED_SIZE+2));
#else
	for(i=0;i<(GPS_SPEED_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return atof(&data[2]);
}

float gps_get_course(void)
{
	uint8_t data[GPS_COURSE_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_COURSE_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_COURSE_SIZE+2));
#else
	for(i=0;i<(GPS_COURSE_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return atof(&data[2]);
}

uint8_t gps_get_position_fix(void)
{
	uint8_t data[GPS_POSITION_FIX_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_POSITION_FIX_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_POSITION_FIX_SIZE+2));
#else
	for(i=0;i<(GPS_POSITION_FIX_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return data[2];
}

uint8_t gps_get_sate_used(void)
{
	uint8_t data[GPS_SATE_USED_SIZE+2];
	uint8_t value;
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_SATE_USED_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_SATE_USED_SIZE+2));
#else
	for(i=0;i<(GPS_SATE_USED_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	if(data[3] >= '0' && data[3] <= '9')value = (data[3] - '0') * 10;
	else value = 0;
	if(data[2] >= '0' && data[2] <= '9')value += (data[2] - '0');
	else value += 0;

	return value;
}

float gps_get_altitude(void)
{
	uint8_t data[GPS_ALTITUDE_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_ALTITUDE_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_ALTITUDE_SIZE+2));
#else
	for(i=0;i<(GPS_ALTITUDE_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return atof(&data[2]);
}

uint8_t gps_get_mode(void)
{
	uint8_t data[GPS_MODE_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_MODE_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_MODE_SIZE+2));
#else
	for(i=0;i<(GPS_MODE_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return data[2];
}

uint8_t gps_get_mode2(void)
{
	uint8_t data[GPS_MODE2_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_MODE2_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_MODE2_SIZE+2));
#else
	for(i=0;i<(GPS_MODE2_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return data[2];
}

uint8_t gps_get_sate_in_veiw(void)
{
	uint8_t data[GPS_SATE_IN_VIEW_SIZE+2];
	uint8_t reg[1];
	uint8_t dtmp[1];
	reg[0] = GPS_SATE_IN_VIEW_ID;
	int i;

	i2c_write(i2c_dev, &configs, reg, 1);
#ifdef I2C_ORIGINAL
	i2c_read(i2c_dev, &configs, data, (GPS_SATE_IN_VIEW_SIZE+2));
#else
	for(i=0;i<(GPS_SATE_IN_VIEW_SIZE+2);i++)
	{
		i2c_read(i2c_dev, &configs, dtmp, 1);
		data[i] = dtmp[0];
	}
#endif
	return data[2];
}

void degtodms(dms_t *coord, float latlon)
{
	int degrees = (int)latlon;
	coord->deg = degrees;
	float minf = ((float)degrees-latlon)*60;
	int minutes = (int)minf;
	coord->min = minutes;
	float secf = ((float)minutes-minf)*60;
	int seconds = (int)secf;
	coord->sec = seconds;
}

void print_location(void)
{
	float lati, longi;
	dms_t lat_dms, lon_dms;
	char ns_head, ew_head;

	ns_head=gps_get_ns();
	lati=gps_get_latitude();
	ew_head=gps_get_ew();
	longi=gps_get_longitude();

	degtodms(&lat_dms,lati);
	degtodms(&lon_dms,longi);

	printf("Location: %d\00B0%d\'%d\"%c %d\u00B0%d\'%d\"%c\n",
			lat_dms.deg,lat_dms.min,lat_dms.sec,ns_head,lon_dms.deg,
			lon_dms.min,lon_dms.sec,ew_head);
}
