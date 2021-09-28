/*
  LoRa Duplex communication with Spreading Factor

  Sends a message every half second, and polls continually
  for new incoming messages. Sets the LoRa radio's spreading factor.

  Spreading factor affects how far apart the radio's transmissions
  are, across the available bandwidth. Radios with different spreading
  factors will not receive each other's transmissions. This is one way you
  can filter out radios you want to ignore, without making an addressing scheme.

  Spreading factor affects reliability of transmission at high rates, however,
  so avoid a hugh spreading factor when you're sending continually.

  See the Semtech datasheet, http://www.semtech.com/images/datasheet/sx1276.pdf
  for more on Spreading Factor.

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

const int csPin = 7;          // LoRa radio chip select
const int resetPin = 6;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin

uint8_t msgCount = 0;            // count of outgoing messages
int interval = 2000;          // interval between sends
long lastSendTime = 0;        // time of last packet send

void sendMessage(string outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.print(outgoing.c_str());                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  string incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  printf("Message: %d\n", incoming);
  printf("RSSI: %s\n",LoRa.packetRssi());
  printf("Snr: %s\n", LoRa.packetSnr());
  printf("\n");
}

int main() {
  
  stdio_init_all();

  printf("LoRa Duplex - Set spreading factor\n");

  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin); // set CS, reset, IRQ pin

  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    printf("LoRa init failed. Check your connections.\n");
    while (true);                       // if failed, do nothing
  }

  LoRa.setSpreadingFactor(8);           // ranges from 6-12,default 7 see API docs
  printf("LoRa init succeeded.\n");

  while (1)
  {
    if (to_ms_since_boot(get_absolute_time()) - lastSendTime > interval) {
      string message = "HeLoRa World! ";   // send a message
      message += msgCount;
      sendMessage(message);
      printf("Sending ", message.c_str());
      lastSendTime = to_ms_since_boot(get_absolute_time());            // timestamp the message
      interval = rand()%2000 + 1000;    // 2-3 seconds
      msgCount++;
    }

    // parse for a packet, and call onReceive with the result:
    onReceive(LoRa.parsePacket());
  }

  return 0;
}