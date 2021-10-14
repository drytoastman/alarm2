#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/time.h"

#include "local.h"

typedef struct pwmstate {
    int pin;
    int slice;
    int chan;
    float clkdiv;
    int freq;
    int duty;
    alarm_id_t alarm;
} PWMState;

PWMState buzzer;
PWMState hwled;

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

void pwm_setup(int pin, float clkdiv, PWMState *newstate) {
    PWMState init = {
        .pin    = pin,
        .slice  = (pin >> 1u) & 7u,
        .chan   = pin & 1u,
        .clkdiv = clkdiv,
        .freq   = 0,
        .duty   = 0,
        .alarm  = 0
    };
    *newstate = init;

    pwm_config c = pwm_get_default_config();
    pwm_config_set_clkdiv(&c, newstate->clkdiv);
    pwm_init(newstate->slice, &c, false);
    gpio_set_function(newstate->pin, GPIO_FUNC_PWM);
}

void pwm_set(PWMState *state) {
    uint16_t scale  = clock_get_hz(clk_sys) / (state->clkdiv * state->freq); \
    uint16_t spoint = scale * state->duty / 100;
    pwm_set_wrap(state->slice, scale);
    pwm_set_chan_level(state->slice, state->chan, spoint);
    pwm_set_enabled(state->slice, true);
}

void pin_setup(int pin) {
    gpio_init(pin);
    gpio_put(pin, 0);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_set_drive_strength(pin, GPIO_DRIVE_STRENGTH_2MA);
}



// Alarm
void alarm_set(int val) {
    gpio_put(ALARM, val);
    usb_printf("A=%d\n", gpio_get(ALARM));
}

// Buzzer
bool buzzer_on = false;
int64_t buzzer_toggle(alarm_id_t id, void *data) {
    buzzer_on = !buzzer_on;
    pwm_set_enabled(buzzer.slice, buzzer_on);
    return BUZZER_TOGGLE_US;
}

void buzzer_set(int freq) {
    buzzer.freq = freq;
    if (freq == 0) {
        pwm_set_enabled(buzzer.slice, false);
        cancel_alarm(buzzer.alarm);
    } else {
        pwm_set(&buzzer);
        buzzer_on    = true;
        buzzer.alarm = add_alarm_in_us(BUZZER_TOGGLE_US, buzzer_toggle, NULL, true);
    }

    usb_printf("B=%d\n", buzzer.freq);
}


// Hotwater LED
int save_brightness = 0;
alarm_id_t pulse_alarm;

void hwled_set(int brightness) {
    hwled.duty = brightness;
    if (hwled.duty == 0) {
        pwm_set_enabled(hwled.slice, false);
    } else {
        pwm_set(&hwled);
    }
    usb_printf("L=%d\n", hwled.duty);
}

int64_t hwled_pulse(alarm_id_t id, void *data) {
    static int direction = -1;
    if (direction < 0) {
        hwled.duty--;
        if (hwled.duty <= 0) direction = 1;
    } else {
        hwled.duty++;
        if (hwled.duty >= 100) direction = -1;
    }
    pwm_set(&hwled);
    return HWLED_PULSE_US;
}

int64_t hwled_pulse_off(alarm_id_t id, void *data) {
    // cancel alarm and then wait to make sure its done
    cancel_alarm(pulse_alarm);
    sleep_ms(HWLED_PULSE_US * 2);
    hwled.duty = save_brightness;
    return 0;
}

void hwled_pulse_on() {
    save_brightness = hwled.duty;
    pulse_alarm = add_alarm_in_us(HWLED_PULSE_US, hwled_pulse, NULL, true);
    add_alarm_in_ms(45000, hwled_pulse_off, NULL, true);
}


// Hotwater request line toggle
int64_t hw_off(alarm_id_t id, void *data) {
    gpio_put(HOTWATER, 0);
    usb_printf("H=0\n");
    return 0;
}

void hw_toggle() {
    gpio_put(HOTWATER, 1);
    usb_printf("H=1\n");
    hwled_pulse_on();
    add_alarm_in_ms(500,   hw_off,    NULL, true);
}


void outputs_send_all() {
    usb_printf("A=%d\n", gpio_get(ALARM));
    usb_printf("B=%d\n", buzzer.freq);
    usb_printf("H=%d\n", gpio_get(HOTWATER));
    usb_printf("L=%d\n", hwled.duty);
}

void outputs_init() {
    pin_setup(ALARM);
    pin_setup(HOTWATER);

    // Buzzer
    pwm_setup(BUZZER,  8, &buzzer);
    buzzer.duty = 50;
    gpio_set_drive_strength(BUZZER, GPIO_DRIVE_STRENGTH_8MA);

    // Hotwater LED
    pwm_setup(HWLED,  16, &hwled);
    hwled.freq = 1000;
    pwm_set_enabled(hwled.slice, true);
    hwled_set(15);
}
