/*
 * sensor_read.c
 *
 *  Created on: Jan 31, 2018
 *  Author: David R. Flores
 */

#include <stdio.h>
#include <tinyara/config.h>
#include <artik_gpio.h>
#include "gpio.h"
#include <stdio.h>
#include "distance.h"
#include "vt_100.h"

//Definitions for trigger pins
#define Left_Trig_Pin 30
#define Left_Echo_Pin 32
#define Mid_Trig_Pin 39
#define Mid_Echo_Pin 38
#define Right_Trig_Pin 59
#define Right_Echo_Pin 58


unsigned long duration_L, duration_R;
long distance_left_sensor, distance_mid_sensor, distance_right_sensor;



// time = distance / speed
// t = 10 cm / 0.034 cm/us
// distance = duration*0.034 / 2



void u_sensor_loop(void)
{
	int i;

	screen_setup();

	while(1){

		gpio_write(Left_Trig_Pin, LOW);
		gpio_write(Right_Trig_Pin, LOW);
		gpio_write(Mid_Trig_Pin, LOW);
		// delay here for 2 micro seconds
	//	usleep(2);
	//	gpio_write(Left_Trig_Pin, HIGH);
	//	gpio_write(Right_Trig_Pin, HIGH);

		// delay here for 10 micro seconds
		//delayMicroseconds(10);
	//	usleep(10);
	//	for(i = 10000; i>0; i++){

	//	}

		//gpio_write(Left_Trig_Pin, LOW);
	//	gpio_write(Right_Trig_Pin, LOW);

		//duration_L = pulseIn(Left_Echo_Pin, HIGH);
		//duration_R = pulseIn(Right_Echo_Pin, HIGH);

		//distance_left_sensor = duration_L * 0.034 / 2;
		//distance_right_sensor = duration_R* 0.034 / 2;



	distance_left_sensor = getDistance(Left_Trig_Pin, Left_Echo_Pin);
	distance_mid_sensor = getDistance(Mid_Trig_Pin, Mid_Echo_Pin);
	distance_right_sensor = getDistance(Right_Trig_Pin, Right_Echo_Pin);

	// initial navigation method
	navigate(distance_left_sensor, distance_mid_sensor, distance_right_sensor);
	}
}



