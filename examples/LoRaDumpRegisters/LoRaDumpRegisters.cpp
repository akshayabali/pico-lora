#include "pico/stdlib.h"
#include "pico/binary_info.h"

//Inlude Library
#include "LoRa-RP2040.h"

int main(){

  stdio_init_all();
  
  printf("LoRa Dump Registers\n");

  // override the default CS, reset, and IRQ pins (optional)
  // LoRa.setPins(7, 6, 1); // set CS, reset, IRQ pin

  if (!LoRa.begin(915E6)) {         // initialize ratio at 915 MHz
    printf("LoRa init failed. Check your connections.");
    while (true);                   // if failed, do nothing
  }

  LoRa.dumpRegisters();

  return 0;
}

