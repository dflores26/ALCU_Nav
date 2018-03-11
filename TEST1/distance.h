/*
 * distance.h
 *
 *  Created on: Jan 31, 2018
 *  Author: David R. Flores
 */

#ifndef DISTANCE_H_
#define DISTANCE_H_

#define HIGH 1
#define LOW 0

long getDistance(int trig_pin, int echo_pin);
long return_distance(int trig_pin, int echo_pin);
void time_difference(void);
long getMicrotime(void);

#endif /* DISTANCE_H_ */
