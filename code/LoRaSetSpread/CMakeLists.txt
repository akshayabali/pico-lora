cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)

if (TARGET tinyusb_device)
    project(LoRaSetSpread)

    add_executable(LoRaSetSpread
        LoRaSetSpread.cpp
    )

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 17)

    target_include_directories(LoRaSetSpread PUBLIC ../../src)

    target_link_directories(LoRaSetSpread PUBLIC ../../src)

    target_link_libraries(LoRaSetSpread pico_stdlib LoRa_pico_lib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(LoRaSetSpread 1)
    pico_enable_stdio_uart(LoRaSetSpread 0)

    # create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(LoRaSetSpread)

    # example_auto_set_url(LoRaSetSpread)

    elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()