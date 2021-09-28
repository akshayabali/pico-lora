cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)

if (TARGET tinyusb_device)
    project(LoRaDumpRegisters)

    add_executable(LoRaDumpRegisters
        LoRaDumpRegisters.cpp
    )

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 17)

    target_include_directories(LoRaDumpRegisters PUBLIC ../../src)

    target_link_directories(LoRaDumpRegisters PUBLIC ../../src)

    target_link_libraries(LoRaDumpRegisters pico_stdlib LoRa_pico_lib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(LoRaDumpRegisters 1)
    pico_enable_stdio_uart(LoRaDumpRegisters 0)

    # create map/bin/hex/uf2 file in addition to ELF.
    pico_add_extra_outputs(LoRaDumpRegisters)

    elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()