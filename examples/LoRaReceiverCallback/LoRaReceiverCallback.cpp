#include "stdlib.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "stdio.h"
#include "string.h"
#include "string"
//Inlude Library
#include "LoRa-RP2040.h"

using std::string;


void onReceive(int packetSize) {
  // received a packet
  printf("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    printf("%s",(char)LoRa.read());
  }

  // print RSSI of packet
  printf("' with RSSI ");
  printf("%d\n",LoRa.packetRssi());
}

int main(){

  stdio_init_all();

  printf("LoRa Receiver Callback");

  if (!LoRa.begin(915E6)) {
    printf("Starting LoRa failed!\n");
    while (1);
  }

  // Uncomment the next line to disable the default AGC and set LNA gain, values between 1 - 6 are supported
  // LoRa.setGain(6);
  
  // register the receive callback
  LoRa.onReceive(onReceive);

  // put the radio into receive mode
  LoRa.receive();
  return 0;
}