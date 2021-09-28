#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "stdio.h"
//Inlude Library
#include "LoRa-RP2040.h"

int counter = 0;

int main(){

  stdio_init_all();

  printf("LoRa Sender non-blocking\n");

  if (!LoRa.begin(915E6)) {
    printf("Starting LoRa failed!\n");
    while (1);
  }

  while(1){
    // wait until the radio is ready to send a packet
    while (LoRa.beginPacket() == 0) {
      printf("waiting for radio ... \n");
      sleep_ms(100);
    }

    printf("Sending packet non-blocking: ");
    printf("%d\n",counter);

    // send in async / non-blocking mode
    LoRa.beginPacket();
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket(true); // true = async / non-blocking mode

    counter++;
  }
}