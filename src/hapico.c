#include <stdarg.h>
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "bsp/board.h"
#include "tusb.h"

// INPUTS
#define HWSWITCH 20
const int regularinputs[] = {
    0,   1,  2,  3,  4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21
};


// OUTPUTS
#define HWLED    28
#define BUZZER   27
#define ALARM    26
#define BOARDLED 25
#define HOTWATER 22
const int regularoutputs[] = {
    HWLED, ALARM, BOARDLED, HOTWATER
};
const int buzzer_slice = (BUZZER >> 1u) & 7u;
const int buzzer_chan  = BUZZER & 1u;

char inputbuffer[256];
int bufend = 0;

char outputbuffer[256];
void usb_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int cnt = vsprintf(outputbuffer, fmt, ap);
    va_end(ap);

    tud_cdc_write(outputbuffer, cnt-1);  // don't send \0
    tud_cdc_write_flush();
}

// CALLBACKS
void sensor_callback(uint gpio, uint32_t events) {
    usb_printf("Sensor %d %d\n", gpio, events);
}

void switch_callback(uint gpio, uint32_t events) {
    usb_printf("Switch %d %d\n", gpio, events);
}

void cdc_task(void)
{
    if (tud_cdc_connected() && tud_cdc_available()) {
        int number;
        uint32_t cnt = tud_cdc_read(&inputbuffer[bufend], sizeof(inputbuffer) - bufend);

        if (cnt > 0) {
            for (int ii = bufend; ii < bufend+cnt; ii++) {
                if (inputbuffer[bufend-1] == '\n') {
                    sscanf(inputbuffer, "%d\n", &number);
                }
            }
            bufend += cnt;
        }
    }
}

int main() {
    int ii;

    for (ii = 0; ii < sizeof(regularinputs)/sizeof(int); ii++) {
        gpio_init(ii);
        gpio_set_dir(ii, GPIO_IN);
        gpio_pull_up(regularinputs[ii]);
        gpio_set_input_enabled(ii, true);
        gpio_set_irq_enabled_with_callback(regularinputs[ii], GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, (ii == HWSWITCH) ? &switch_callback : &sensor_callback);
    }

    for (ii = 0; ii < sizeof(regularoutputs)/sizeof(int); ii++) {
        gpio_init(ii);
        gpio_put(ii, 0);
        gpio_set_dir(ii, GPIO_OUT);
        gpio_set_drive_strength(ii, GPIO_DRIVE_STRENGTH_2MA);
    }

    // Buzzer is a PWM output
    {
        gpio_init(BUZZER);
        gpio_set_function(BUZZER, GPIO_FUNC_PWM);
        pwm_set_wrap(buzzer_slice, 99);
        pwm_set_chan_level(buzzer_slice, buzzer_chan, 50);
        // pwm_set_enabled(buzzer_slice, true);
    }

    tusb_init();

    while (true) {
        tud_task();
        cdc_task();
        __wfi();
    }

    return 0;
}


void tud_cdc_rx_cb(uint8_t itf)
{
    // just wake and handle in main loop
}

enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};
int blink_interval_ms = BLINK_NOT_MOUNTED;

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
  usb_printf("hello world!\n");
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}