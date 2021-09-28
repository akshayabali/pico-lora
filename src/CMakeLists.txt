cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)

# project(LoRa_pico_lib)

add_library(LoRa_pico_lib LoRa-RP2040.cpp LoRa-RP2040.h)
add_library(LoRa_print Print.h Print.cpp)

target_link_libraries(LoRa_pico_lib pico_stdlib hardware_spi hardware_interp LoRa_print)

 # enable usb output, disable uart output
 pico_enable_stdio_usb(LoRa_pico_lib 1)
 pico_enable_stdio_uart(LoRa_pico_lib 0)