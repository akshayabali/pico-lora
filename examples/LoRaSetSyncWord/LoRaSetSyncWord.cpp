/*
  LoRa Duplex communication with Sync Word

  Sends a message every half second, and polls continually
  for new incoming messages. Sets the LoRa radio's Sync Word.

  Spreading factor is basically the radio's network ID. Radios with different
  Sync Words will not receive each other's transmissions. This is one way you
  can filter out radios you want to ignore, without making an addressing scheme.

  See the Semtech datasheet, http://www.semtech.com/images/datasheet/sx1276.pdf
  for more on Sync Word.

  created 28 April 2017
  by Tom Igoe

  translated by Akshaya Bali
*/
#include "stdlib.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "stdio.h"
#include "string.h"

#include <string>
//Inlude Library
#include "LoRa-RP2040.h"


const int csPin = 7;          // LoRa radio chip select
const int resetPin = 6;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin

using std::string;

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
  printf("RSSI: %s\n", LoRa.packetRssi());
  printf("Snr: %s\n", LoRa.packetSnr());
  printf("\n");
}

int main() {

  stdio_init_all();

  printf("LoRa Duplex - Set sync word\n");

  // override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// set CS, reset, IRQ pin

  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    printf("LoRa init failed. Check your connections.\n");
    while (true);                       // if failed, do nothing
  }

  LoRa.setSyncWord(0xF3);           // ranges from 0-0xFF, default 0x34, see API docs
  printf("LoRa init succeeded.\n");

  while (1)
  {
    if (to_ms_since_boot(get_absolute_time()) - lastSendTime > interval) {
      string message = "HeLoRa World! ";   // send a message
      message += msgCount;
      sendMessage(message);
      printf("Sending %s\n", message.c_str());
      lastSendTime = to_ms_since_boot(get_absolute_time());            // timestamp the message
      interval = rand()%2000 + 1000;    // 2-3 seconds
      msgCount++;
    }

    // parse for a packet, and call onReceive with the result:
    onReceive(LoRa.parsePacket());
  }
  
  return 0;
}