#include <define.h>
#include <SPI.h>
#include <Arduino.h>
#include "AIOapp.h"
#include "protoc.h"
#include <SoftwareSerial.h>

extern SoftwareSerial mySerial;
AIOapp aiOapp(&mySerial,&Serial);

void setup() {
  setNewMsgCallback(parseCommand);
  mySerial.begin(115200);
  Serial.begin(115200);
  aiOapp.begin();
}

void loop() {

// mySerial.print(a);
  aiOapp.update();
  delay(50);
  parseSerial();
}