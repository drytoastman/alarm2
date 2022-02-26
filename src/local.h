// MAIN
#define USB_TIMEOUT_US 500000
void usb_printf(const char *fmt, ...);

// INPUTS
// #define HWSWITCH 20
#define INPUTPINLAST 21
#define EDGES (GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL)
void inputs_init();
void inputs_task();
void inputs_send_all();
void debounce_set(int gpio, int val);

// OUTPUTS
#define HWLED    28
#define BUZZER   27
#define ALARM    26
#define BOARDLED 25
#define HOTWATER 22
#define BUZZER_CLKDIV    8
#define BUZZER_DUTY      50
#define BUZZER_PULSE_US  500000
#define HWLED_CLKDIV     16
#define HWLED_PWM_FREQ   1000
#define HWLED_PULSE_US   7000
void outputs_init();
void alarm_set(int val);
void buzzer_set_freq(int freq);
void buzzer_set(int val);
void hwled_set_brightness(int brightness);
void hw_toggle();
void outputs_send_all();

// Flash
#define DEBOUNCE_MAX_COUNT 28
typedef struct Options {
    int magic_version;
    // outputs
    int led_brightness;
    int buzzer_freq;
    // inputs
    uint64_t debounce[DEBOUNCE_MAX_COUNT];
} Options;
extern Options options;
bool options_read();
void options_write();