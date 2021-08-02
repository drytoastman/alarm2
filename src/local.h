// MAIN
void usb_printf(const char *fmt, ...);

// INPUTS
// #define HWSWITCH 20
#define INPUTPINLAST 21
#define EDGES (GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL)
#define DEBOUNCE_US 10000
void inputs_init();
void inputs_task();

// OUTPUTS
#define HWLED    28
#define BUZZER   27
#define ALARM    26
#define BOARDLED 25
#define HOTWATER 22
void outputs_init();