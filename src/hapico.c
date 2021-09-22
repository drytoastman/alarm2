#include <stdarg.h>
#include "hardware/gpio.h"
#include "tusb.h"

#include "local.h"

enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

int  blink_interval_ms = BLINK_NOT_MOUNTED;
char inputbuffer[256];
int  bufsize = 0;

char outputbuffer[256];
void usb_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int cnt = vsprintf(outputbuffer, fmt, ap);
    va_end(ap);

    tud_cdc_write(outputbuffer, cnt);
    tud_cdc_write_flush();
    tud_task();  // let it write now as usb buffer is only 64 bytes
}


int64_t led_blink(alarm_id_t id, void *user_data) {
    gpio_xor_mask(1ul << BOARDLED);
    return blink_interval_ms*1000;  // return is in uS
}

void tud_cdc_rx_cb(uint8_t _) { /* just wake and handle in main loop */ }
void tud_mount_cb(void)       { blink_interval_ms = BLINK_MOUNTED; }
void tud_umount_cb(void)      { blink_interval_ms = BLINK_NOT_MOUNTED; }
void tud_suspend_cb(bool _)   { blink_interval_ms = BLINK_SUSPENDED; }
void tud_resume_cb(void)      { blink_interval_ms = BLINK_MOUNTED; }

void process_command(char *command) {
    int gpio, val;
    switch (command[0]) {
        case 'I': inputs_send_all(); break;
        case 'O': outputs_send_all(); break;
        default:
            if (sscanf(command, "%d=%d", &gpio, &val) == 2) {
                output_set(gpio, val);
            }
        break;
    }
}

void cdc_task(void) {
    if (tud_cdc_connected() && tud_cdc_available()) {
        int number;
        uint32_t cnt = tud_cdc_read(&inputbuffer[bufsize], sizeof(inputbuffer) - bufsize);
        if (cnt > 0) {
            int start = 0;
            int cut = -1;
            bufsize += cnt;

            for (int ii = 0; ii < bufsize; ii++) {
                if (inputbuffer[ii] == '\r') {
                    inputbuffer[ii] = 0;
                    cut = ii+1;
                    process_command(&inputbuffer[start]);
                    start = cut;
                }
            }

            if (cut > 0) {
                memmove(inputbuffer, &inputbuffer[cut], bufsize - cut);
                bufsize -= cut;
            }
        }
    }
}


int main() {
    alarm_pool_init_default();
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
