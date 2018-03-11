
/*
 * distance.c
 *
 *  Created on: Jan 31, 2018
 *  Author: David R. Flores
 */

#include <stdio.h>
#include <tinyara/gpio.h>
#include <tinyara/config.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "navigate.h"
#include <sys/time.h>

#undef CONFIG_USEC_PER_TICK
#define CONFIG_USEC_PER_TICK 9979

/*
 * Get distance in mm using HC-SR04.
 * Return -1 if there are critical error.
 * Return -2 if echo pulse is too long(measured value is incorrect).
 * Otherwise return measured distance in mm.
 * min measure distance: 20mm
 * max measure distance: ~5000mm(5V) / ~4200mm(3.3V)
 * unit measure distance: 5mm
 */
long getDistance(int trig_pin, int echo_pin)
{
	static char devtrig[16] = "";
	char devecho[16] = "";
	char buf[4];
	int fd, cntPulseDuration;

	// check trig and echo is same.
	if(trig_pin == echo_pin) {
		fprintf(stderr, "Trig pin and echo pin is same.\n");
		return -1;
	}

	// make gpio path string.
	snprintf(devtrig, 16, "/dev/gpio%d", trig_pin);
	snprintf(devecho, 16, "/dev/gpio%d", echo_pin);

	// pin open test
	fd = open(devtrig, O_RDWR);
	if(fd == -1) {
		fprintf(stderr, "Wrong Trig pin.\n");
		close(fd); return -1;
	}
	close(fd);

	fd = open(devecho, O_RDONLY);
	if(fd == -1) {
		fprintf(stderr, "Wrong Echo pin. \n");
		close(fd); return -1;
	}
	close(fd);

	// Trig pulse duration require at least 10us.
	// But write operation's time is enough to exceed 10us.
	// So just write 1 and 0 in sequence on trig pin.
	fd = open(devtrig, O_RDWR);
	ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_OUT);
	if (write(fd, "1", 2) < 0) {
		fprintf(stderr, "Trig pin write error.\n");
		// delay 60ms each measurement (as datasheet recommend)
		close(fd); up_mdelay(60); return -1;
	}
	close(fd);
	fd = open(devtrig, O_RDWR);
	ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_OUT);
	if (write(fd, "0", 2) < 0) {
		fprintf(stderr, "Trig pin write error.\n");
		// delay 60ms each measurement (as datasheet recommend)
		close(fd); up_mdelay(60); return -1;
	}
	close(fd);

	// wait echo pulse rise(PGT)
	cntPulseDuration = 0;
	do {
	fd = open(devecho, O_RDONLY);
	ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_IN);
	read(fd, buf, sizeof(buf));
	close(fd);
	cntPulseDuration++;
	// If stuck here too long, timeout error.
	//if(1000 < cntPulseDuration) {
	//	fprintf(stderr, "Echo pulse rise timeout.\n");
	//	// delay 60ms each measurement (as datasheet recommend)
	//	up_mdelay(60); return -1;
	//}
	} while(!(buf[0] & 0x1));

	// If above do-while run only 1 time, echo pin is stuck at high.
	// This might an error of wrong echo pin is selected.
	if(1 == cntPulseDuration) {
		fprintf(stderr, "Echo pin stuck at high.\n");
		// delay 60ms each measurement (as datasheet recommend)
		up_mdelay(60); return -1;
	}

	// wait echo pulse fall(NGT)
	cntPulseDuration = 0;
	do {
	fd = open(devecho, O_RDONLY);
	ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_IN);
	read(fd, buf, sizeof(buf));
	close(fd);
	// While echo read as high,
	// add 1 to cntPulseDuration every read cycle
	// and compare cntPulseDuration and real distance measured by ruler.
	cntPulseDuration++;
	// 0.5cm/cntPulseDuration is calculated.
	// 1000 cntPulseDuration is 500cm.
	// and 500cm is max measure length of HC-SR04.
	if(1000 < cntPulseDuration) {
		fprintf(stderr, "Echo pulse is too long.\n");
		// delay 60ms each measurement (as datasheet recommend)
		up_mdelay(60); return -2;
	}
	} while(buf[0] & 0x1);

	// correction measured value. and convert to mm.
	if(2 > cntPulseDuration) cntPulseDuration = 0;
	else cntPulseDuration = (cntPulseDuration - 2) * 5;
	// delay 60ms each measurement (as datasheet recommend)
	up_mdelay(60);

	// return distance in mm.
	return cntPulseDuration;
}

// attempt to return microsecond difference




/**
 * Returns the current time in microseconds.
 */
long getMicrotime(void){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void time_difference(void){
	printf("Time...\n");
	struct timeval tv_var1 = {0};
	struct timeval tv_var2 = {0};
	gettimeofday(&tv_var1, NULL);
	usleep(10);
	gettimeofday(&tv_var2, NULL);
	long millisecond1 = (tv_var1.tv_sec * 1000) + (tv_var1.tv_usec/1000);
	long millisecond2 = (tv_var2.tv_sec * 1000) + (tv_var2.tv_usec/1000);
	long millisecond = millisecond2 - millisecond1;
	printf("time 1 = %lu %lu \n", tv_var1.tv_sec, tv_var1.tv_usec);
	printf("time 2 = %lu %lu diff (milliseconds) %lu \n", tv_var2.tv_sec, tv_var2.tv_usec, millisecond);
	gettimeofday(&tv_var1, NULL);
	gettimeofday(&tv_var2, NULL);
	millisecond1 = (tv_var1.tv_sec * 1000) + (tv_var1.tv_usec/1000);
	millisecond2 = (tv_var2.tv_sec * 1000) + (tv_var2.tv_usec/1000);
	millisecond = millisecond2 - millisecond1;
	printf("time 1 = %lu %lu \n", tv_var1.tv_sec, tv_var1.tv_usec);
	printf("time 2 = %lu %lu diff (milliseconds) %lu \n", tv_var2.tv_sec, tv_var2.tv_usec, millisecond);
	gettimeofday(&tv_var1, NULL);
	usleep(100000);
	gettimeofday(&tv_var2, NULL);
	millisecond1 = (tv_var1.tv_sec * 1000) + (tv_var1.tv_usec/1000);
	millisecond2 = (tv_var2.tv_sec * 1000) + (tv_var2.tv_usec/1000);
	millisecond = millisecond2 - millisecond1;
	printf("time 1 = %lu %lu \n", tv_var1.tv_sec, tv_var1.tv_usec);
	printf("time 2 = %lu %lu diff (milliseconds) %lu \n", tv_var2.tv_sec, tv_var2.tv_usec, millisecond);
}

//#include "wiring_private.h"
//#include "pins_arduino.h"

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * This function performs better with short pulses in noInterrupt() context
 */

/*
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution.  calling
	// digitalRead() instead yields much coarser resolution.
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t stateMask = (state ? bit : 0);

	// convert the timeout from microseconds to a number of times through
	// the initial loop; it takes approximately 16 clock cycles per iteration
	unsigned long maxloops = microsecondsToClockCycles(timeout)/16;

	unsigned long width = countPulseASM(portInputRegister(port), bit, stateMask, maxloops);

	// prevent clockCyclesToMicroseconds to return bogus values if countPulseASM timed out
	if (width)
		return clockCyclesToMicroseconds(width * 16 + 16);
	else
		return 0;
}
*/

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse.
 *
 * ATTENTION:
 * this function relies on micros() so cannot be used in noInterrupt() context
 */
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution.  calling
	// digitalRead() instead yields much coarser resolution.
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t stateMask = (state ? bit : 0);

	unsigned long startMicros = micros();

	// wait for any previous pulse to end
	while ((portInputRegister(port) & bit) == stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	// wait for the pulse to start
	while ((portInputRegister(port) & bit) != stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}

	unsigned long start = micros();
	// wait for the pulse to stop
	while ((portInputRegister(port) & bit) == stateMask) {
		if (micros() - startMicros > timeout)
			return 0;
	}
	return micros() - start;
}
