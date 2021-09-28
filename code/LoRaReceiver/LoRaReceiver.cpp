#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

//Inlude Library
#include "LoRa-pico.h"

int main() {

   stdio_init_all();

   if (!LoRa.begin(500E6)) {
      printf("Starting LoRa failed!\n");
      while (1);
   }

   printf("LoRa Started\n");
   
   int counter = 0;
   
   while (1) {
      int packetSize = LoRa.parsePacket();
      if (packetSize) {
         // received a packet
         printf("Received packet \n'");

         // read packet
         while (LoRa.available()) {
            printf((char*)LoRa.read());
         }

         // print RSSI of packet
         printf("' with RSSI \n");
         printf((char*)LoRa.packetRssi(),"\n");
      }
  }

  return 1;
}