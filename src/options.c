/***
 * Base pulled from micropython port
 */
#include <string.h>
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "local.h"

#define STORAGE_BASE (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)
static_assert(sizeof(Options) < FLASH_SECTOR_SIZE, "Options is too big");

#define MAGIC_VERSION 0x0a0b0c01
#define DEFAULT_LED_BRIGHTNESS 15
#define DEFAULT_BUZZER_FREQ 1300
#define DEFAULT_DEBOUNCE_US 20000

Options options;

bool options_read() {
    bool ret = true;
    memcpy(&options, (void *)(XIP_BASE + STORAGE_BASE), sizeof(Options));
    if (options.magic_version != MAGIC_VERSION) {
        // need to intialize
        ret = false;
        options.magic_version = MAGIC_VERSION;
        options.led_brightness = DEFAULT_LED_BRIGHTNESS;
        options.buzzer_freq = DEFAULT_BUZZER_FREQ;
        for (int ii = 0; ii < DEBOUNCE_MAX_COUNT; ii++) {
            options.debounce[ii] = DEFAULT_DEBOUNCE_US;
        }
        options_write();
    }

    return ret;
}

void options_write() {
    // Flash erase/program must run in an atomic section because the XIP bit gets disabled.
    int atomic_state = save_and_disable_interrupts();
    flash_range_erase(STORAGE_BASE, FLASH_SECTOR_SIZE); // works in sectors 4096
    flash_range_program(STORAGE_BASE, (void*)&options, sizeof(Options)); // works in pages 256
    restore_interrupts(atomic_state);
}
