/*
 *  navigate.c
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

//Definitions for LEDs
#define Left_LED 31
#define Right_LED 41
#define BLUE_LED 49
#define RED_LED 45
#define MID_LED 40

//External Interrupt Pin
#define EXINT0 57

//Definition for beeper
#define BACK_UP 37


void navigate(long distance_L, long distance_M, long distance_R){

//	if(run == 1){
	//	vt_clear_screen();
		//vt_cursor_pos(10,10);
	//	printf("\n\n\n\n\n!!!!!!!!INTERRUPT!!!!!!!!\n\n\n\n\n");
	//}
//===============================================
	// FORWARD STATE
	/*
	if(distance_M <= 30){
		gpio_write(MID_LED, LOW);
		gpio_write(RED_LED, LOW);
		gpio_write(BLUE_LED, HIGH);
		gpio_write(Right_LED, LOW);
		gpio_write(Left_LED, LOW);

		vt_cursor_pos(10, 75);
		printf("%ld   ", distance_L);//40+13
		vt_cursor_pos(12, 75);
		printf("%ld   ", distance_M);//60+15
		vt_cursor_pos(14, 75);
		printf("%ld   ", distance_R);//80+14
		vt_cursor_pos(20, 75);
		printf("STOP!!!         \n");

		return;
	}
	//checking middle and then left and right
	else if(distance_M > 30){
		gpio_write(MID_LED, HIGH);
		gpio_write(RED_LED, LOW);
		gpio_write(BLUE_LED, LOW);
		gpio_write(Right_LED, HIGH);
		gpio_write(Left_LED, LOW);
		vt_cursor_pos(10, 75);
		printf("%ld   ", distance_L);//40+13
		vt_cursor_pos(12, 75);
		printf("%ld   ", distance_M);//60+15
		vt_cursor_pos(14, 75);
		printf("%ld   ", distance_R);//80+14
		vt_cursor_pos(20, 75);
		printf("FORWARD!!!          \n");

		return;
	}
	*/
	//===========================================================
	// FORWARD STATE
	if(distance_L > 55 && distance_M > 45 && distance_R > 50 ){
		gpio_write(MID_LED, LOW);
		gpio_write(RED_LED, LOW);
		gpio_write(BLUE_LED, HIGH);
		gpio_write(Right_LED, LOW);
		gpio_write(Left_LED, LOW);
		gpio_write(BACK_UP, LOW);
		vt_cursor_pos(30, 98);
		printf("%ld   ", distance_L);//40+13
		vt_cursor_pos(32, 100);
		printf("%ld   ", distance_M);//60+15
		vt_cursor_pos(34, 99);
		printf("%ld   ", distance_R);//80+14
		vt_cursor_pos(36, 87);
		printf("FORWARD!!!            ");

		return;
	}
	//checking middle and then left and right
	else if((distance_M >= 30 && distance_M <= 45) && distance_L >= 35 && distance_R >= 30){
		gpio_write(MID_LED, HIGH);
		gpio_write(RED_LED, LOW);
		gpio_write(BLUE_LED, LOW);
		gpio_write(Right_LED, HIGH);
		gpio_write(Left_LED, LOW);
		gpio_write(BACK_UP, LOW);
		vt_cursor_pos(30, 98);
		printf("%ld   ", distance_L);//40+13
		vt_cursor_pos(32, 100);
		printf("%ld   ", distance_M);//60+15
		vt_cursor_pos(34, 99);
		printf("%ld   ", distance_R);//80+14
		vt_cursor_pos(36, 87);
		printf("TURN LEFT: MID            ");

		return;
	}
	// checking left sensor
	else if((distance_L >= 35 && distance_L <= 55) && distance_M >= 30 && distance_R >= 30){
		gpio_write(MID_LED, LOW);
		gpio_write(RED_LED, LOW);
		gpio_write(BLUE_LED, LOW);
		gpio_write(Right_LED, LOW);
		gpio_write(Left_LED, HIGH);
		gpio_write(BACK_UP, LOW);
		vt_cursor_pos(30, 98);
		printf("%ld   ", distance_L);//40+13
		vt_cursor_pos(32, 100);
		printf("%ld   ", distance_M);//60+15
		vt_cursor_pos(34, 99);
		printf("%ld   ", distance_R);//80+14
		vt_cursor_pos(36, 87);
		printf("TURN RIGHT            ");
		return;
	}
	// checking right sensor
	else if((distance_R >= 30 && distance_R <= 55) && distance_L >= 35 && distance_M >= 30){
		gpio_write(MID_LED, LOW);
		gpio_write(RED_LED, LOW);
		gpio_write(BLUE_LED, LOW);
		gpio_write(Right_LED, HIGH);
		gpio_write(Left_LED, LOW);
		gpio_write(BACK_UP, LOW);
		vt_cursor_pos(30, 98);
		printf("%ld   ", distance_L);//40+13
		vt_cursor_pos(32, 100);
		printf("%ld   ", distance_M);//60+15
		vt_cursor_pos(34, 99);
		printf("%ld   ", distance_R);//80+14
		vt_cursor_pos(36, 87);
		printf("TURN LEFT            ");
		return;
	}
	else if((distance_L < 36) || (distance_R < 31) || distance_M < 31){
		gpio_write(RED_LED, HIGH);
		up_mdelay(100);
		gpio_write(RED_LED, LOW);
		up_mdelay(100);
		gpio_write(Right_LED, LOW);
		gpio_write(MID_LED, LOW);
		gpio_write(Left_LED, LOW);
		gpio_write(BLUE_LED, LOW);
		gpio_write(BACK_UP, HIGH);
		vt_cursor_pos(30, 98);
		printf("%ld   ", distance_L);//40+13
		vt_cursor_pos(32, 100);
		printf("%ld   ", distance_M);//60+15
		vt_cursor_pos(34, 99);
		printf("%ld   ", distance_R);//80+14
		vt_cursor_pos(36, 87);
		printf("STOP: TOO CLOSE!!!            ");
		return;
	}
	return;
}

