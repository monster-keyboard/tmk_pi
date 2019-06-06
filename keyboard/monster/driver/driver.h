/* Author:Rainboy
 * 2019-06-06 18:42
 * */
#ifndef _PI_ZERO_DRIVER_H
#define _PI_ZERO_DRIVER_H
#include <stdint.h>
#include "host.h"

extern host_driver_t pi_driver;

void _delay_us(uint32_t us); 
void _delay_ms(uint32_t ms);

#endif
