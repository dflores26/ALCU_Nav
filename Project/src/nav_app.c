/*
 * nav_app.c
 *
 *  Created on: Feb 20, 2018
 *      Author: kiaxa
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "sensor_read.h"
#include "gps.h"

static void print_all(void){

	uint8_t *data;
	uint8_t online;
	online = 0;

	printf("GPS online status: ");
	online = gps_check_online();
	if(online==1){
		printf("ONLINE\n");
	}else{
		printf("OFFLINE\n");
	}
	data = gps_get_utc_date_time();
	printf("%d-%d-%d,%d:%d:%d\n", data[0], data[1], data[2], data[3], data[4], data[5]);
	printf("Status: %c\n", gps_get_status());
	printf("Latitude: %c:%f\n",gps_get_ns(),gps_get_latitude());
	printf("Longitude: %c:%f\n",gps_get_ew(),gps_get_longitude());
	printf("Speed: %f\n", gps_get_speed());
	printf("Course: %f\n", gps_get_course());
	printf("Fix: %d\n", gps_get_position_fix());
	printf("Satellites in view: %d\n", gps_get_sate_in_veiw());
	printf("Sat used: %d\n", gps_get_sate_used());
	printf("Altitude: %f\n", gps_get_altitude());
	printf("Mode: %c\n", gps_get_mode());
	printf("Mode 2: %c\n", gps_get_mode2());
}

static void show_usage(FAR const char *program)
{
	printf("USAGE:\n");
	printf(" %s run        : runs navigation program\n", program);
	printf(" %s check      : check if GPS is online\n", program);
	printf(" %s utc        : show GPS UTC date time\n", program);
	printf(" %s status     : get GPS status\n", program);
	printf(" %s lat        : get latitude\n", program);
	printf(" %s lon        : get longitude\n", program);
	printf(" %s speed      : get current speed\n", program);
	printf(" %s course     : get course\n", program);
	printf(" %s fix   	   : get position fix\n", program);
	printf(" %s view       : get satellite in view\n", program);
	printf(" %s sat_used   : get satellite used\n", program);
	printf(" %s alt        : get altitude\n", program);
	printf(" %s mode       : get mode\n", program);
	printf(" %s mode2      : get mode 2\n", program);
	printf(" %s location   : get location\n", program);
	printf(" %s all        : show all info\n", program);
	printf(" %s help       : show this help\n", program);
}

void nav_main(int argc, FAR char *argv[]){

	int port = 1;

	gps_init(port);

	uint8_t *data;
	uint8_t online;
	online = 0;

	switch(argc){
	case 2:
		if(strcmp(argv[1], "run")==0){
			printf("Attempt to run navigation code\n");
			u_sensor_loop();
		}else if(strcmp(argv[1], "check")==0){
			printf("GPS online status: ");
			online = gps_check_online();
			if(online==1){
				printf("ONLINE\n");
			}else{
				printf("OFFLINE\n");
			}
		} else if(strcmp(argv[1], "utc")==0){
			data = gps_get_utc_date_time();
			printf("%d-%d-%d,%d:%d:%d\n", data[0], data[1], data[2], data[3], data[4], data[5]);
		} else if(strcmp(argv[1], "status")==0){
			printf("Status: %c\n", gps_get_status());
		} else if(strcmp(argv[1], "lat")==0){
			printf("Latitude: %c:%f\n",gps_get_ns(),gps_get_latitude());
		} else if(strcmp(argv[1], "lon")==0){
			printf("Longitude: %c:%f\n",gps_get_ew(),gps_get_longitude());
		} else if(strcmp(argv[1], "speed")==0){
			printf("Speed: %f\n", gps_get_speed());
		} else if(strcmp(argv[1], "course")==0){
			printf("Course: %f\n", gps_get_course());
		} else if(strcmp(argv[1], "fix")==0){
			printf("Fix: %d\n", gps_get_position_fix());
		} else if(strcmp(argv[1], "view")==0){
			printf("Satellites in view: %d\n", gps_get_sate_in_veiw());
		} else if(strcmp(argv[1], "sat_used")==0){
			printf("Sat used: %d\n", gps_get_sate_used());
		} else if(strcmp(argv[1], "alt")==0){
			printf("Altitude: %f\n", gps_get_altitude());
		} else if(strcmp(argv[1], "mode")==0){
			printf("Mode: %c\n", gps_get_mode());
		} else if(strcmp(argv[1], "mode2")==0){
			printf("Mode 2: %c\n", gps_get_mode2());
		} else if(strcmp(argv[1], "location")==0){
			print_location();
		} else if(strcmp(argv[1], "all")==0){
			print_all();
		} else if(strcmp(argv[1], "help")==0){
			show_usage(argv[0]);
		} else {
			show_usage(argv[0]);
		}
		break;
	default:
		show_usage(argv[0]);
		break;
	}
}

