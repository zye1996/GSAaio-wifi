
//#include "Pages.h"
#include <Arduino.h>
#include <Pages.h>


void resetCb(void) {
  // Serial.println("EL-Client (re-)starting!");
  bool ok = false;
  do {
    ok = esp.Sync();      // sync up with esp-link, blocks for up to 2 seconds
    // if (!ok) Serial.println("EL-Client sync failed!");
  } while(!ok);
  // Serial.println("EL-Client synced!");
  
  webServer.setup();
}

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  // Serial.begin(115200);
  esp.resetCb = resetCb;

  //init
  
//  resetCb();
//  webServer.registerHandler(F("/test.html.json"));
  // URLHandler *ledHandler = webServer.createURLHandler(F("/TEST.json"));
  PIDInit();

  resetCb();
}

void loop() {
  // put your main code here, to run repeatedly:
  esp.Process();
  
  delay(5);
  printloop();
}