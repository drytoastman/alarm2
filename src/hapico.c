#include <stdarg.h>
#include "hardware/gpio.h"
#include "pico/time.h"
#include "tusb.h"

#include "local.h"

enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

int  blink_interval_ms = BLINK_NOT_MOUNTED;
int  bufsize = 0;

void usb_printf(const char *fmt, ...) {
    char outputbuffer[512];

    va_list ap;
    va_start(ap, fmt);
    int length = vsnprintf(outputbuffer, sizeof(outputbuffer), fmt, ap);
    va_end(ap);

    static uint64_t last_avail_time;
    if (tud_cdc_connected()) {
        for (int i = 0; i < length;) {
            int n = length - i;
            int avail = tud_cdc_write_available();
            if (n > avail) n = avail;
            if (n) {
                int n2 = tud_cdc_write(&outputbuffer[i], n);
                tud_task();
                tud_cdc_write_flush();
                i += n2;
                last_avail_time = time_us_64();
            } else {
                tud_task();
                tud_cdc_write_flush();
                if (!tud_cdc_connected() || (!tud_cdc_write_available() && time_us_64() > last_avail_time + USB_TIMEOUT_US)) {
                    break;
                }
            }
        }
    } else {
        // reset our timeout
        last_avail_time = 0;
    }
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
        case 'I':
            inputs_send_all();
            return;
        case 'O':
            outputs_send_all();
            return;

        // Output switches
        case 'H':
            hw_toggle();
            return;
        case 'A':
            if (sscanf(command, "A=%d", &val) == 1) {
                alarm_set(val);
                return;
            }
        case 'T':
            if (sscanf(command, "T=%d", &val) == 1) {
                buzzer_set(val);
                return;
            }

        // Numerical Settings
        case 'B':
            if (sscanf(command, "B=%d", &val) == 1) {
                buzzer_set_freq(val);
                return;
            }
        case 'L':
            if (sscanf(command, "L=%d", &val) == 1) {
                hwled_set_brightness(val);
                return;
            }
        case 'D':
            if (sscanf(command, "D%d=%d", &gpio, &val) == 2) {
                debounce_set(gpio, val);
                return;
            }

        // Button
        case 'S':
            options_write();
            return;
    }

    usb_printf("invalid request '%s'\n", command);
}

void cdc_task(void) {
    static char inputbuffer[512];
    if (tud_cdc_connected() && tud_cdc_available()) {
        uint32_t cnt = tud_cdc_read(&inputbuffer[bufsize], sizeof(inputbuffer) - bufsize);
        if (cnt > 0) {
            int start = 0;
            int cut = -1;
            bufsize += cnt;

            for (int ii = 0; ii < bufsize; ii++) {
                if ((inputbuffer[ii] == '\r') || (inputbuffer[ii] == '\n')) {
                    inputbuffer[ii] = 0;
                    cut = ii+1;
                    if (start != ii) {
                        process_command(&inputbuffer[start]);
                    }
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
    bool ofound = options_read();
    alarm_pool_init_default();
    inputs_init();
    outputs_init();

    add_alarm_in_ms(blink_interval_ms, led_blink, NULL, true);
    tusb_init();

    if (!ofound) {
        usb_printf("options intitialized\n");
    }

    while (true) {
        tud_task();
        cdc_task();
        inputs_task();
        __wfi();
    }

    return 0;
}
