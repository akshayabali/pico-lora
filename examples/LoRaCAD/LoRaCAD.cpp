/*
  LoRa Duplex communication

  Sends a message every half second, and polls continually
  for new incoming messages. Implements a one-byte addressing scheme,
  with 0xFF as the broadcast address.

  Uses readString() from Stream class to read payload. The Stream class'
  timeout may affect other functuons, like the radio's callback. For an

  created 28 April 2017
  by Tom Igoe

  translated by Akshaya Bali
*/

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
  printf("Received packet\n '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    printf("%s",(char)LoRa.read());
  }

  // print RSSI of packet
  printf("' with RSSI \n");
  printf("%d\n",LoRa.packetRssi());
  LoRa.channelActivityDetection();

}

void onCadDone(bool signalDetected) {
  // detect preamble
  if (signalDetected) {
    printf("Signal detected\n");
    LoRa.receive();


  } else {
    LoRa.channelActivityDetection();
  }
}

int main(){

  stdio_init_all();
  sleep_ms(3000);

  printf("\nLoRa CAD\n");

  if (!LoRa.begin(433.425E6)) {             // initialize ratio at 915 MHz
    printf("LoRa init failed. Check your connections.\n");
    while (true);                       // if failed, do nothing
  }

  printf("LoRa init succeeded.\n");
    // register the channel activity dectection callback
  
  LoRa.onReceive(onReceive);
  LoRa.onCadDone(onCadDone);
  // put the radio into CAD mode
  LoRa.channelActivityDetection();
  while (1)
  {
    sleep_ms(1);
    tight_loop_contents();
  }
  
  return 0;
}
