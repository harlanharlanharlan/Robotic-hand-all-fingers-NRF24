#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(7, 8);
const byte address[10] = "ADDRESS01";
Servo servo[5];
const byte servoPins[5] = {2, 3, 4, 5, 6};
int num[5] = {1, 1, 1, 1, 1};
int x;

void setup() {
  for (x = 0; x < 5; x++) {
    servo[x].attach(servoPins[x]);
  }
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
};

void loop() {
  if (radio.available()) {
    char txt[32] =  "";
    radio.read(&txt, sizeof(txt));
    Serial.println(txt);
    for (int x = 0; x < 5; x++) {
      num[x] = (int)txt[x];
      Serial.print(num[x]);
      Serial.print(':');
      servo[x].write(num[x]);
    }
    Serial.println();
  };
};
