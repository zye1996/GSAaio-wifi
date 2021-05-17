#include <define.h>
#include <Arduino.h>
#include <AIOapp.h>
#include <protoc.h>
#include <SoftwareSerial.h>

AIOapp aiOapp;


void setup() {
  // put your setup code here, to run once:
  //   mySerial.begin(115200);
  // mySerial.println("Hello, world?");
  // DEBUG_SERIAL.begin(115200);
  setNewMsgCallback(parseCommand);
  mySerial.begin(115200);
  aiOapp.begin();

}

void loop() {

// mySerial.print(a);
  aiOapp.update();
  parseSerial();
}