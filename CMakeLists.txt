cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(LoRa-RP2040 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_LORA_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
pico_sdk_init()

include(example_auto_set_url.cmake)



add_subdirectory(src)

# Hardware-specific examples in subdirectories:
add_subdirectory(examples)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

