// MAIN
#define USB_TIMEOUT_US 500000
void usb_printf(const char *fmt, ...);

// INPUTS
// #define HWSWITCH 20
#define INPUTPINLAST 21
#define EDGES (GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL)
#define DEBOUNCE_US 20000
void inputs_init();
void inputs_task();
void inputs_send_all();

// OUTPUTS
#define HWLED    28
#define BUZZER   27
#define ALARM    26
#define BOARDLED 25
#define HOTWATER 22
#define BUZZER_TOGGLE_US 500000
void outputs_init();
void output_set(int gpio, int val);
void buzzer_set(int val);
void outputs_send_all();