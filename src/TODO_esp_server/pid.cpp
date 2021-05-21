#include <Pages.h>
#include <EEPROM.h>

#define MAGIC 0xABEF
#define MAX_STR_LEN  32

// EEPROM content 
#define EEPROM_POS_MAGIC          0
#define EEPROM_POS_KP     (EEPROM_POS_MAGIC + 2)
#define EEPROM_POS_KI      (EEPROM_POS_KP + MAX_STR_LEN)
#define EEPROM_POS_KD            (EEPROM_POS_KI + MAX_STR_LEN)
#define EEPROM_POS_VALVE_STATUS         (EEPROM_POS_KD+MAX_STR_LEN)
#define EEPROM_POS_NOTIFICATIONS  (EEPROM_POS_VALVE_STATUS+MAX_STR_LEN)

float kp=0;
float ki=0;
float kd=0;
bool v_status=0; //0 on 1 off


void userSetFieldCb(char * field)
{
    // mySerial.print("4343420");
    // mySerial.println();
      String fld = field;
  if( fld == F("KP")){
    kp = (float)webServer.getArgFloat();}
  else if( fld == F("KI")){
    ki = (float)webServer.getArgFloat();}
  else if( fld == F("KD")){
    kd = (float)webServer.getArgFloat();}
  else if( fld == F("Valve Status"))
  {
    String valve_status = webServer.getArgString();
    v_status = ((valve_status == F("on")) ? 0 : 1);
  }

    // mySerial.print("4343420"); 
    // mySerial.println();
}

void userLoadCb(char * url)
{
    // mySerial.print("024420");
    // mySerial.println();
    char buf[MAX_STR_LEN];
    webServer.setArgFloat(F("KP"), kp);
    webServer.setArgFloat(F("KI"), ki);
    webServer.setArgFloat(F("KD"), kd);
    webServer.setArgString(F("Valve Status"), (v_status == 0) ?  F("on") : F("off"));
    // mySerial.print("4343420"); 
    mySerial.println();
}

void PIDInit()
{


  URLHandler *pidPageHandler = webServer.createURLHandler(F("/Test7.html.json"));
  pidPageHandler->setFieldCb.attach(userSetFieldCb);
  pidPageHandler->loadCb.attach(userLoadCb);
}

void printloop(){
    // webServer.setArgInt(F("KP"), (float)EEPROM[EEPROM_POS_KP]);
    // mySerial.print((float)EEPROM[EEPROM_POS_KP]); 
    // webServer.setArgInt(F("KI"), (float)EEPROM[EEPROM_POS_KI]);
    // mySerial.print((float)EEPROM[EEPROM_POS_KI]); 
    // webServer.setArgInt(F("KD"), (float)EEPROM[EEPROM_POS_KD]);
    // mySerial.print((float)EEPROM[EEPROM_POS_KD]); 
    // mySerial.print("4343420"); 
    mySerial.print(ki);
    mySerial.print(",");
    mySerial.print(kp);
    mySerial.print(",");
    mySerial.print(kd);
    mySerial.print(",");
    mySerial.println();
    delay(50);
}