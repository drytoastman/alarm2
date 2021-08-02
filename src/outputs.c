#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "local.h"

const int outputs[] = {
    HWLED, ALARM, BOARDLED, HOTWATER
};
const int buzzer_slice = (BUZZER >> 1u) & 7u;
const int buzzer_chan  = BUZZER & 1u;
const float clkdiv = 8.0;


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
    }
}

void buzzer_set(int freq) {
    if (freq == 0) {
        pwm_set_enabled(buzzer_slice, false);
    } else {
        uint16_t scale = FREQ_TO_SCALE(clkdiv, freq);
        pwm_set_wrap(buzzer_slice, scale);
        pwm_set_chan_level(buzzer_slice, buzzer_chan, scale/2);
        pwm_set_enabled(buzzer_slice, false);
    }
}

void output_set(int gpio, int val) {
    gpio_put(gpio, val);
}