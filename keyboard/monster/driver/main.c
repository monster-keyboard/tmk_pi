#include <stdint.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <wiringPi.h>

#include "keyboard.h"
#include "debug.h"
#include "host.h"
#include "host_driver.h"
#include "matrix.h"
#include "config.h"
#include "led.h"

//https://my.oschina.net/floristgao/blog/311612
#include <unistd.h>


fd_set rfds;

int fd;
static uint8_t  keyboard_led_stats = 0;
static report_keyboard_t keyboard_report;

char hidg_path[] = "/dev/hidg0";


/* host driver */ 
static uint8_t keyboard_leds(void);
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

void task_init();


int main(){

    if ((fd = open(hidg_path, O_RDWR, 0666)) == -1) {
        perror(hidg_path);
        return 3;
    }
    /*printf("hello world\n");*/
    setup_mcu();
    task_init();
    led_init();

    FD_SET(fd, &rfds);

    host_set_driver(&pi_driver);
    printf("\n\nTMK: version 0.1 PI_ZERO started !\n");
    keyboard_setup();
    keyboard_init();
    while(1){
        keyboard_task();
        if (FD_ISSET(fd, &rfds)) {
            char buf[8];
            int led_status_len = read(fd,buf,7);
            if( led_status_len){
                keyboard_led_stats = buf[led_status_len-1];
            }
        }
    }
    return 0;
}

void task_init(){
#ifndef NO_DEBUG
    debug_config.enable= 1;
    debug_config.matrix = 1;
    debug_config.keyboard = 1;
#endif
}




/*******************************************************************************
 * Host driver
 ******************************************************************************/
static uint8_t keyboard_leds(void)
{
    return keyboard_led_stats;
}
//https://www.kernel.org/doc/Documentation/usb/gadget_hid.txt
static void send_keyboard(report_keyboard_t *report)
{

/*#ifdef NKRO_ENABLE*/
/*#endif*/
    uint8_t timeout = 128;
    keyboard_report= *report;
    int to_send = sizeof(report_keyboard_t);
    if (write(fd, report, to_send) != to_send) {
        perror(hidg_path);
        return;
    }
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
