#include "tusb.h"
#include "pico/unique_id.h"

#define VID 0xBEEF
#define PID 0x0001

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor           = VID,
    .idProduct          = PID,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};

uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

enum {
    ITF_NUM_CDC = 0,
    ITF_NUM_CDC_DATA,
    ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN  (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN)

#define EPNUM_CDC_NOTIF   0x81
#define EPNUM_CDC_OUT     0x02
#define EPNUM_CDC_IN      0x82

uint8_t const desc_fs_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),
    // Interface number, string index, EP notification address and size, EP data address (out, in) and size.
    TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64),
};

uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
{
    return desc_fs_configuration;
}

char const* string_desc_arr [] =
{
    (const char[]) { 0x09, 0x04 }, // 0: is supported language is English (0x0409)
    "drytoastman",                 // 1: Manufacturer
    "HA Pico",                     // 2: Product
    "this gets pico unique id",    // 3: Serials, should use chip ID
    "HAPico CDC",                  // 4: CDC Interface
};

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
static uint16_t _desc_str[32];
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
    uint8_t chr_count;

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;

    } else if (index == 3) {
        pico_unique_board_id_t board_id;
        pico_get_unique_board_id(&board_id);

        for (int ii = 0; ii < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; ++ii) {
            char interm[3];
            sprintf(interm, "%02x", board_id.id[ii]);
            _desc_str[1+(ii*2)] = interm[0];
            _desc_str[2+(ii*2)] = interm[1];
        }
        chr_count = PICO_UNIQUE_BOARD_ID_SIZE_BYTES*2;

    } else {
        if (index >= 5) return NULL;

        const char *str = string_desc_arr[index];
        chr_count = strlen(str);
        if ( chr_count > 31 ) chr_count = 31;

        // Convert ASCII string into UTF-16
        for (uint8_t i=0; i<chr_count; i++) {
            _desc_str[1+i] = str[i];
        }
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (TUSB_DESC_STRING << 8 ) | (2*chr_count + 2);
    return _desc_str;
}
