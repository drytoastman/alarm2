#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/time.h"

#include "local.h"

const int outputs[] = {
    HWLED, ALARM, BOARDLED, HOTWATER
};
const int buzzer_slice = (BUZZER >> 1u) & 7u;
const int buzzer_chan  = BUZZER & 1u;
const float clkdiv = 8.0;
int buzzer_freq = 0;
alarm_id_t buzzer_alarm;


/*
    Buzzer is a PWM output
    clk = 125MHz
    clkdiv  hifreq(0)  lowfreq(65535)
        1      125M     1907
        2     62.5M      953
        4     31.2M      477     18750=2000Hz
        8     15.6M      238      9375=2000Hz
       16     7812K      120      4687=2000Hz
       32     3906K       60
       64     1953K       30
      128      976K       15
      256      488K        7
*/
#define FREQ_TO_SCALE(cd, f) clock_get_hz(clk_sys) / (cd * f)

void outputs_init() {

    for (int ii = 0; ii < sizeof(outputs)/sizeof(int); ii++) {
        gpio_init(outputs[ii]);
        gpio_put(outputs[ii], 0);
        gpio_set_dir(outputs[ii], GPIO_OUT);
        gpio_set_drive_strength(outputs[ii], GPIO_DRIVE_STRENGTH_2MA);
    }

    // Buzzer PWM
    {
        pwm_config c = pwm_get_default_config();
        pwm_config_set_clkdiv(&c, clkdiv);
        pwm_init(buzzer_slice, &c, false);
        gpio_set_function(BUZZER, GPIO_FUNC_PWM);
        gpio_set_drive_strength(BUZZER, GPIO_DRIVE_STRENGTH_2MA);
    }
}

int64_t buzzer_toggle(alarm_id_t id, void *data) {
    bool *buzzer_on = data;
    *buzzer_on = !*buzzer_on;
    pwm_set_enabled(buzzer_slice, *buzzer_on);
    return BUZZER_TOGGLE_US;
}

void buzzer_set(int freq) {
    static bool buzzer_on = false;

    if (freq == 0) {
        pwm_set_enabled(buzzer_slice, false);
        cancel_alarm(buzzer_alarm);
        buzzer_freq = 0;
    } else {
        uint16_t scale = FREQ_TO_SCALE(clkdiv, freq);
        pwm_set_wrap(buzzer_slice, scale);
        pwm_set_chan_level(buzzer_slice, buzzer_chan, scale/2);
        pwm_set_enabled(buzzer_slice, true);

        buzzer_freq = freq;
        buzzer_on = true;
        buzzer_alarm = add_alarm_in_us(BUZZER_TOGGLE_US, buzzer_toggle, &buzzer_on, true);
    }
}

void outputs_send_all() {
    for (int ii = 0; ii < sizeof(outputs)/sizeof(int); ii++) {
        if (outputs[ii] != BOARDLED)
            usb_printf("O%d=%d\n", outputs[ii], gpio_get(outputs[ii]));
    }
    usb_printf("B=%d\n", buzzer_freq);
}

void output_set(int gpio, int val) {
    switch (gpio) {
        case HWLED:
        case ALARM:
        case HOTWATER:
            gpio_put(gpio, val);
            break;
        default:
            usb_printf("invalid output: %d\n", gpio);
            break;
    }
}
