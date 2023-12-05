#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

int x;
int temp;
RF24 radio(7, 8);
const byte address[10] = "00001";
Servo servo[5];
const byte servoPins[5] = {2, 3, 4, 5, 6};
int pos[5] = {1, 1, 1, 1, 1};

void setup() {
  Serial.begin(115200);
  for (x = 0; x < 5; x++) {
    servo[x].attach(servoPins[x]);
  }
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    for (x = 0; x < 5; x++) {
      radio.read(&temp, sizeof(temp));
      if (temp != 0) {
        pos[x] = temp;
        //   radio.read(&pos[x], sizeof(pos[x]));
        Serial.println (temp);
        servo[x].write(pos[x]);
      }
    }
  }
  delay(100);
}
