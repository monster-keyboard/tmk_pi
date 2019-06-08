#include <stdint.h>
#include "host.h"
#include "host_driver.h"
#include "matrix.h"
#include <stdio.h>
#include "keyboard.h"
#include <wiringPi.h>



static uint8_t  keyboard_led_stats = 0;
static report_keyboard_t keyboard_report;


/* host driver */ static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);
host_driver_t pi_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};

#define setup_mcu  wiringPiSetup

int main(){
    /*printf("hello world\n");*/
    setup_mcu();

    host_set_driver(&pi_driver);
    printf("\n\nTMK: version 0.1 PI_ZERO started !\n");
    keyboard_setup();
    keyboard_init();
    while(1){
        keyboard_task();
    }
    return 0;
}




/*******************************************************************************
 * Host driver
 ******************************************************************************/
static uint8_t keyboard_leds(void)
{
    return keyboard_led_stats;
}

static void send_keyboard(report_keyboard_t *report)
{
    uint8_t timeout = 128;
    keyboard_report= *report;
}

static void send_mouse(report_mouse_t *report)
{
}

static void send_system(uint16_t data)
{
}

static void send_consumer(uint16_t data)
{
}
