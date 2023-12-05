#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
int x;
int pos[5] = {1, 1, 1, 1, 1};
RF24 radio(7, 8);
const byte address[10] = "00001";
int pot = A0;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  for (x = 0; x < 5; x++) {
    pos[x] = analogRead(x);
 //   pos[x] = map(pos[x], 540, 770, 0, 180);
 //   if (pos[x] < 30) pos[x] = 1;
    Serial.println (pos[x]);
    radio.write(pos[x], sizeof(pos[x]));
  }
  delay(100);
}
