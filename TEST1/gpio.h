/*
 * gpio.h
 *
 *  Created on: Jan 31, 2018
 *  Author: David R. Flores
 */

#ifndef GPIO_H_
#define GPIO_H_

int gpio_read(int port);
void gpio_write(int port, int value);

#endif /* GPIO_H_ */
