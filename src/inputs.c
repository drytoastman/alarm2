#include "hardware/gpio.h"
#include "pico/time.h"
#include "local.h"

typedef struct {
    uint gpio;
    bool reported;
    bool changed;
} InputState;

InputState state[INPUTPINLAST+1];
alarm_pool_t *debouncePool;

/**
 * Handle timeout to recheck input for bounce
 */
int64_t debounce(alarm_id_t id, void *user) {
    InputState *state = (InputState*)user;
    bool current = gpio_get(state->gpio);

    if (current != state->reported) {
        state->reported = current;
        state->changed  = true;
    } // otherwise, we assume it never stayed changed, catch next edge

    // renable irq
    gpio_set_irq_enabled(state->gpio, EDGES, true);
    return 0;
}

/**
 * handle edge interupt for a input pin that we are not currently debouncing
 */
void edge_callback(uint gpio, uint32_t events) {
    if (events & EDGES) {
        gpio_set_irq_enabled(gpio, EDGES, false);
        alarm_pool_add_alarm_in_us(debouncePool, DEBOUNCE_US, debounce, &state[gpio], true);
    }
}

/**
 * startup tasks for inputs
 */
void inputs_init() {
    debouncePool = alarm_pool_create(PICO_TIME_DEFAULT_ALARM_POOL_HARDWARE_ALARM_NUM - 1, 32);
    busy_wait_ms(10);  // wait to make sure our inputs are settled after powering everything on

    for (int gpio = 0; gpio <= INPUTPINLAST; gpio++) {
        InputState s = { .gpio = gpio, .reported = true, .changed = false };
        state[gpio] = s;

        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_IN);
        gpio_pull_up(gpio);
        gpio_set_irq_enabled_with_callback(gpio, EDGES, true, edge_callback);
        gpio_set_input_enabled(gpio, true);
    }
}

/**
 * user task to report any changed inputs
 */
void inputs_task() {
    for (int gpio = 0; gpio <= INPUTPINLAST; gpio++) {
        if (state[gpio].changed) {
            usb_printf("I%d=%d\n", gpio, state[gpio].reported);
            state[gpio].changed = false;
        }
    }
}

void inputs_send_all() {
    for (int gpio = 0; gpio <= INPUTPINLAST; gpio++) {
        usb_printf("I%d=%d\n", gpio, state[gpio].reported);
    }
}
