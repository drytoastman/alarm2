cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/../pico-sdk)
set(PICO_SDK_INIT_CMAKE_FILE ${PICO_SDK_PATH}/pico_sdk_init.cmake)
set(PICO_STDIO_USB_TASK_INTERVAL_US 100000)
include(${PICO_SDK_INIT_CMAKE_FILE})

project(HAPico)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(hapico hapico.c usb_descriptors.c)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hapico pico_stdlib hardware_pwm tinyusb_device pico_unique_id)
target_include_directories(hapico PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

pico_enable_stdio_usb(hapico 0)
pico_enable_stdio_uart(hapico 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hapico)
