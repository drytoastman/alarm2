cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/pico-sdk)
set(PICO_BOARD pico)

include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
project(HAPico)
add_subdirectory(src)
