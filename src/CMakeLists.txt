# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(hapico hapico.c inputs.c outputs.c usb_descriptors.c)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hapico pico_stdlib pico_unique_id hardware_pwm tinyusb_device)
target_include_directories(hapico PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

pico_enable_stdio_usb(hapico 0)
pico_enable_stdio_uart(hapico 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hapico)
