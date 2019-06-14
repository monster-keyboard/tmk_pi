/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include "led.h"
#include <wiringPi.h>


#define USB_LED_NUM_LOCK_PIN                0
#define USB_LED_CAPS_LOCK_PIN               1
#define USB_LED_SCROLL_LOCK_PIN             2
#define USB_LED_COMPOSE_PIN                 3

void led_init(){
    pinMode (USB_LED_NUM_LOCK_PIN    ,OUTPUT) ;  
    pinMode (USB_LED_CAPS_LOCK_PIN   ,OUTPUT) ;  
    pinMode (USB_LED_SCROLL_LOCK_PIN ,OUTPUT) ;  
    pinMode (USB_LED_COMPOSE_PIN     ,OUTPUT) ;  
}

void led_set(uint8_t usb_led)
{
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) 
        digitalWrite (USB_LED_NUM_LOCK_PIN, HIGH) ; 
    else
        digitalWrite (USB_LED_NUM_LOCK_PIN, LOW) ; 

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) 
        digitalWrite (USB_LED_CAPS_LOCK_PIN, HIGH) ; 
    else
        digitalWrite (USB_LED_CAPS_LOCK_PIN, LOW) ; 

    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) 
        digitalWrite (USB_LED_SCROLL_LOCK_PIN, HIGH) ; 
    else
        digitalWrite (USB_LED_SCROLL_LOCK_PIN, LOW) ; 

    if (usb_led & (1<<USB_LED_COMPOSE)) 
        digitalWrite (USB_LED_COMPOSE_PIN, HIGH) ; 
    else
        digitalWrite (USB_LED_COMPOSE_PIN, LOW) ; 

}
