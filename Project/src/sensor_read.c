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
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <iotbus/iotbus_gpio.h>
#include <iotbus/iotbus_error.h>
#include <sys/mount.h>
#include <tinyara/arch.h>
//#include <tinyara/gpio.h>
#include "vt_100.h"

//Definitions for trigger pins
#define Left_Trig_Pin 30
#define Left_Echo_Pin 32
#define Mid_Trig_Pin 39
#define Mid_Echo_Pin 38
#define Right_Trig_Pin 59
#define Right_Echo_Pin 58

int run = 1;
unsigned long duration_L, duration_R;
long distance_left_sensor, distance_mid_sensor, distance_right_sensor;
iotbus_gpio_context_h g_gpio;
iotbus_gpio_context_h g_gpio2;

volatile int ledstate = 0;

void gpio_event_callback(void *user_data){
	iotbus_gpio_context_h hnd = (iotbus_gpio_context_h) user_data;
	int value = iotbus_gpio_read(hnd);
	printf("inside callback, value %d\r\n",value);
	if(ledstate==1){
		run = 0;
		vt_clear_screen();
		vt_cursor_pos(50,50);
		printf("INTERRUPT DETECTED!!!\n");
		iotbus_gpio_write(g_gpio,1);
		ledstate = 0;
	} else {
		iotbus_gpio_write(g_gpio,0);
		ledstate = 1;
		run = 1;
	}
	return;
}

void gpio_setup(void){
	int ret=0;
	g_gpio = iotbus_gpio_open(51); //LED is 49
	g_gpio2 = iotbus_gpio_open(57); //Button

	ret = iotbus_gpio_set_direction(g_gpio, IOTBUS_GPIO_DIRECTION_OUT);
	ret = iotbus_gpio_set_direction(g_gpio2, IOTBUS_GPIO_DIRECTION_IN);
	if(ret != 0){
		printf("set direction fail\n");
	}
	//iotbus_gpio_write(g_gpio,1);

	//Register callback
	ret=iotbus_gpio_register_cb(g_gpio2,IOTBUS_GPIO_EDGE_BOTH,gpio_event_callback,(void *)g_gpio2);
	if(ret != 0){
		printf("callback register failed\n");
	}
	iotbus_gpio_write(g_gpio,1);
}
// time = distance / speed
// t = 10 cm / 0.034 cm/us
// distance = duration*0.034 / 2

void u_sensor_loop(void)
{
	int i;
	screen_setup();
	iotapi_initialize(); //basically the interrupt system
	gpio_setup();
	ledstate = 0;
	while(run == 1){

//		gpio_write(Left_Trig_Pin, LOW);
//		gpio_write(Right_Trig_Pin, LOW);
//		gpio_write(Mid_Trig_Pin, LOW);
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



//	distance_left_sensor = getDistance(Left_Trig_Pin, Left_Echo_Pin);
//	distance_mid_sensor = getDistance(Mid_Trig_Pin, Mid_Echo_Pin);
//	distance_right_sensor = getDistance(Right_Trig_Pin, Right_Echo_Pin);

	// initial navigation method
//	navigate(distance_left_sensor, distance_mid_sensor, distance_right_sensor);
	}
}



