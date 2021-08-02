#include <stdarg.h>
#include "hardware/gpio.h"
#include "tusb.h"

#include "local.h"

enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

int blink_interval_ms = BLINK_NOT_MOUNTED;
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


int64_t led_blink(alarm_id_t id, void *user_data) {
    gpio_xor_mask(1ul << BOARDLED);
    return blink_interval_ms;
}

void tud_cdc_rx_cb(uint8_t _) { /* just wake and handle in main loop */ }
void tud_mount_cb(void)       { blink_interval_ms = BLINK_MOUNTED;   usb_printf("hello world!\n"); }
void tud_umount_cb(void)      { blink_interval_ms = BLINK_NOT_MOUNTED; }
void tud_suspend_cb(bool _)   { blink_interval_ms = BLINK_SUSPENDED; }
void tud_resume_cb(void)      { blink_interval_ms = BLINK_MOUNTED; }

void cdc_task(void) {
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
    inputs_init();
    outputs_init();

    add_alarm_in_ms(blink_interval_ms, led_blink, NULL, true);
    tusb_init();

    while (true) {
        tud_task();
        cdc_task();
        inputs_task();
        __wfi();
    }

    return 0;
}
