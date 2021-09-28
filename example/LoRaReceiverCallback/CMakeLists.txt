cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)

if (TARGET tinyusb_device)
    project(LoRaReceiverCallback)

    add_executable(LoRaReceiverCallback
        LoRaReceiverCallback.cpp
    )

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 17)

    target_include_directories(LoRaReceiverCallback PUBLIC ../../src)

    target_link_directories(LoRaReceiverCallback PUBLIC ../../src)

    target_link_libraries(LoRaReceiverCallback pico_stdlib LoRa_pico_lib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(LoRaReceiverCallback 1)
    pico_enable_stdio_uart(LoRaReceiverCallback 0)

    # create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(LoRaReceiverCallback)

    # example_auto_set_url(LoRaReceiverCallback)

    elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()