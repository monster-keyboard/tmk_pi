#include <stdint.h>
#include "host.h"
#include "host_driver.h"
#include "matrix.h"


static uint8_t  keyboard_led_stats = 0;
static report_keyboard_t keyboard_report;


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

int main(){
    printf("hello world\n");
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
