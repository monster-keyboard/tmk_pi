/* Author:Rainboy
 * 2019-06-06 18:42
 * */
#ifndef _PI_ZERO_DRIVER_H
#define _PI_ZERO_DRIVER_H
#include <stdint.h>
#include "host.h"
#include <wiringPi.h>

extern host_driver_t pi_driver;

#define _delay_ms delay
#define _delay_us delayMicroseconds

#endif
