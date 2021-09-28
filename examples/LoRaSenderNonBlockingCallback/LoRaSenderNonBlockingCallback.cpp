#include "pico/stdlib.h"
#include "pico/binary_info.h"
//Inlude Library
#include "LoRa-RP2040.h"

int counter = 0;

void onTxDone() {
  printf("TxDone\n");
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

int main() {

  stdio_init_all();

  printf("LoRa Sender non-blocking Callback\n");

  if (!LoRa.begin(915E6)) {
    printf("Starting LoRa failed!\n");
    while (1);
  }

  LoRa.onTxDone(onTxDone);

  while (1) {
    if (runEvery(5000)) { // repeat every 5000 millis

      printf("Sending packet non-blocking: ");
      printf("%d\n", counter);

      // send in async / non-blocking mode
      LoRa.beginPacket();
      LoRa.print("hello ");
      LoRa.print(counter);
      LoRa.endPacket(true); // true = async / non-blocking mode

      counter++;
    }
  }

  return 0;
}
