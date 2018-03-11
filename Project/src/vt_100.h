/*
 * vt100.h
 *
 * Created: 11/11/2017 05:07:50 PM
 *  Author: David
 */


#ifndef VT100_H_
#define VT100_H_

void vt_clear_screen(void);
void vt_red_text(void);
void vt_cursor_pos(int line, int col);
void vt_clear_cursor(void);
void vt_unclear_cursor(void);
void screen_setup(void);
void terminal_setup(void);
void pwm_screen_setup(void);
void pwm_terminal_setup(void);
void fore_ground(void);


#endif /* VT100_H_ */
