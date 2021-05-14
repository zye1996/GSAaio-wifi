#include <Arduino.h>
#include <AIOapp.h>


AIOapp aiOapp;


void setup() {
  // put your setup code here, to run once:
  //   mySerial.begin(115200);
  // mySerial.println("Hello, world?");
  mySerial.begin(115200);
  aiOapp.begin();

}

void loop() {

// mySerial.print(a);
  aiOapp.update();

}