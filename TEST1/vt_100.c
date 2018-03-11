/*
 * vt100.c
 *
 * Created: 11/11/2017 05:07:42 PM
 *  Author: David
 */
#define F_CPU           320000000UL       //System-Clock 8Mhz

#include <stdio.h>
#define ASCII_ESC 27

void vt_clear_screen(void){
	printf( "%c[2J", ASCII_ESC );
}

void vt_cursor_pos(int line, int col){
	printf("%c[%d;%dH", ASCII_ESC,line,col);
}

void fore_ground(void){
	printf("%c[3 1 m", ASCII_ESC);
	_delay_ms(10);
	printf("%c[3 0 m", ASCII_ESC);
	_delay_ms(10);
}

void vt_red_text(void){
	printf("%c[5m", ASCII_ESC);
}

void vt_clear_cursor(void){
	printf("%c[?25l", ASCII_ESC);
}

void vt_unclear_cursor(void){
	printf("%c[?25h", ASCII_ESC);
}

void screen_setup(void){
	vt_clear_screen();
	vt_clear_cursor();
	vt_red_text();
	vt_cursor_pos(25, 75);
	printf(" WELCOME TO THE INITAL TESTING OF THE\n");
	vt_cursor_pos(27, 79);
	printf(" ALCU TEAM 2 NAVIGATION SYSTEM\n");

	vt_cursor_pos(30,85);
	printf("Left Sensor: ");//40+13
	vt_cursor_pos(32,85);
	printf("Middle Sensor: ");//60+15
	vt_cursor_pos(34,85);
	printf("Right Sensor: ");//80+14

}

void pwm_position_print(void){
	vt_cursor_pos(4,0);
	printf("PWM 2: ");
}

void counter_position_print(void){
  vt_cursor_pos(6,0);
  printf("Counter 3: ");
}

void adc_position_print(void){
  vt_cursor_pos(2,0);
  printf("ADC7: ");

}


void pwm_screen_setup(void){
	/*cli();*/
// 	vt_clear_screen();
// 	vt_clear_cursor();
/*	vt_red_text();*/
	/*name_assignment();*/
/*	pwm_position_print();*/
// 	adc_position_print();
// 	counter_position_print();
	/*sei();*/
}

void terminal_setup(void){
	screen_setup();
	name_assignment();
}
