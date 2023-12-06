#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(7, 8);
const byte address[10] = "ADDRESS01";
char txt[] = {72, 73, 74, 74, 0 };
int x;

void setup() {

  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
};

void loop() {
  //  const char txt[] = "Hello World";
  for (x = 0; x < 5; x++) {
    int y = analogRead(x);
    txt[x] = map(y, 550, 790, 1, 127);
    if (txt[x] < 30) txt[x] = 1;
    Serial.print (y, DEC);
    Serial.print (';');
    Serial.print(txt[x], DEC);
    Serial.print('\t');
  }
  radio.write(&txt, sizeof(txt));
  Serial.println ();
  delay(100);
};
