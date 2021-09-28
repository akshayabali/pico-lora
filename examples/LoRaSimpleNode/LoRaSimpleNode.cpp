/*
  LoRa Simple Gateway/Node Exemple

  This code uses InvertIQ function to create a simple Gateway/Node logic.

  Gateway - Sends messages with enableInvertIQ()
          - Receives messages with disableInvertIQ()

  Node    - Sends messages with disableInvertIQ()
          - Receives messages with enableInvertIQ()

  With this arrangement a Gateway never receive messages from another Gateway
  and a Node never receive message from another Node.
  Only Gateway to Node and vice versa.

  This code receives messages and sends a message every second.

  InvertIQ function basically invert the LoRa I and Q signals.

  See the Semtech datasheet, http://www.semtech.com/images/datasheet/sx1276.pdf
  for more on InvertIQ register 0x33.

  created 05 August 2018
  by Luiz H. Cassettari

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

using std::string;

const long frequency = 915E6;  // LoRa Frequency

const int csPin = 10;          // LoRa radio chip select
const int resetPin = 9;        // LoRa radio reset
const int irqPin = 2;          // change for your board; must be a hardware interrupt pin

void LoRa_rxMode(){
  LoRa.enableInvertIQ();                // active invert I and Q signals
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode(){
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               // normal mode
}

void LoRa_sendMessage(string message) {
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  LoRa.print(message.c_str());                  // add payload
  LoRa.endPacket(true);                 // finish packet and send it
}

void onReceive(int packetSize) {
  string message = "";

  while (LoRa.available()) {
    message += (char)LoRa.read();
  }

  printf("Node Receive: ");
  printf("%s\n",message.c_str());
}

void onTxDone() {
  printf("TxDone\n");
  LoRa_rxMode();
}

bool runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = to_ms_since_boot(get_absolute_time());
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

int main(){

  stdio_init_all();

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    printf("LoRa init failed. Check your connections.\n");
    while (true);                       // if failed, do nothing
  }

  printf("LoRa init succeeded.\n");
  printf("\n");
  printf("LoRa Simple Node\n");
  printf("Only receive messages from gateways\n");
  printf("Tx: invertIQ disable\n");
  printf("Rx: invertIQ enable\n");
  printf("\n");

  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);
  LoRa_rxMode();

  while (1)  {
    if (runEvery(1000)) { // repeat every 1000 millis

      string message = "HeLoRa World! ";
      message += "I'm a Node! ";
      message += to_ms_since_boot(get_absolute_time());

      LoRa_sendMessage(message); // send a message

      printf("Send Message!");
    }
  }

  return 0;
}