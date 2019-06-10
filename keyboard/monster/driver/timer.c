#include <stdint.h>
#include "timer.h"
#include <wiringPi.h>
#include <stdio.h>


/*-------------------------------------------------
*  timer
*-------------------------------------------------*/

void timer_init(void){

}
void timer_clear(void){
}

uint16_t timer_read(void)
{
    printf("timer_read at pi driver\n");
    return  (uint16_t)millis();
}

uint32_t timer_read32(void)
{
    return  millis();
}

uint16_t timer_elapsed(uint16_t last){
}
uint32_t timer_elapsed32(uint32_t last){
}
