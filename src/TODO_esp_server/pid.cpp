#include <Pages.h>
#include <EEPROM.h>

#define MAGIC 0xABEF
#define MAX_STR_LEN  32

// EEPROM content 
#define EEPROM_POS_MAGIC          0
#define EEPROM_POS_FIRST_NAME     (EEPROM_POS_MAGIC + 2)
#define EEPROM_POS_LAST_NAME      (EEPROM_POS_FIRST_NAME + MAX_STR_LEN)
#define EEPROM_POS_AGE            (EEPROM_POS_LAST_NAME + MAX_STR_LEN)
#define EEPROM_POS_GENDER         (EEPROM_POS_AGE+1)
#define EEPROM_POS_NOTIFICATIONS  (EEPROM_POS_GENDER+1)

// write a string to EEPROM
void userWriteStr(char * str, int ndx)
{
  for(uint8_t i=0; i < MAX_STR_LEN-1; i++)
  {
    EEPROM.update(ndx + i, str[i]);
    if( str[i] == 0 )
      break;
  }
  EEPROM.update(ndx + MAX_STR_LEN - 1, 0);
}

// read a string from EEPROM
void userReadStr(char * str, int ndx)
{
  for(uint8_t i=0; i < MAX_STR_LEN; i++)
  {
    str[i] = EEPROM[ndx + i];
  }
}

void userSetFieldCb(char * field)
{
    // mySerial.print("4343420");
    // mySerial.println();
      String fld = field;
  if( fld == F("KP"))
    userWriteStr(webServer.getArgString(), EEPROM_POS_FIRST_NAME);
  else if( fld == F("KI"))
    userWriteStr(webServer.getArgString(), EEPROM_POS_LAST_NAME);
  else if( fld == F("KD"))
    EEPROM.update(EEPROM_POS_AGE, (uint8_t)webServer.getArgInt());
  else if( fld == F("Valve Status"))
  {
    String gender = webServer.getArgString();
    EEPROM.update(EEPROM_POS_GENDER, (gender == F("on")) ? 'o' : 'f');
  }
  else if( fld == F("notifications"))
    EEPROM.update(EEPROM_POS_NOTIFICATIONS, webServer.getArgBoolean());
    // mySerial.print("4343420"); 
    // mySerial.println();
}

void userLoadCb(char * url)
{
    // mySerial.print("024420");
    // mySerial.println();
    char buf[MAX_STR_LEN];
    userReadStr( buf, EEPROM_POS_FIRST_NAME );
    webServer.setArgString(F("KP"), buf);
    mySerial.print(buf); 
    userReadStr( buf, EEPROM_POS_LAST_NAME );
    webServer.setArgString(F("KI"), buf);
    mySerial.print(buf); 
    webServer.setArgInt(F("KD"), (uint8_t)EEPROM[EEPROM_POS_AGE]);
    mySerial.print((uint8_t)EEPROM[EEPROM_POS_AGE]); 
    webServer.setArgString(F("Valve Status"), (EEPROM[EEPROM_POS_GENDER] == 'o') ? F("on") : F("off"));
    webServer.setArgBoolean(F("notifications"), EEPROM[EEPROM_POS_NOTIFICATIONS] != 0);
    // mySerial.print("4343420"); 
    // mySerial.println();
}

void PIDInit()
{
  uint16_t magic;
  EEPROM.get(EEPROM_POS_MAGIC, magic);

  if( magic != MAGIC ) // EEPROM is uninitialized?
  {
    magic = MAGIC;
    // set default values
    EEPROM.put(EEPROM_POS_MAGIC, magic);
    EEPROM.update(EEPROM_POS_FIRST_NAME, 0);
    EEPROM.update(EEPROM_POS_LAST_NAME, 0);
    EEPROM.update(EEPROM_POS_AGE, 0);
    EEPROM.update(EEPROM_POS_GENDER, 'f');
    EEPROM.update(EEPROM_POS_NOTIFICATIONS, 0);
  }

  URLHandler *userPageHandler = webServer.createURLHandler(F("/test1.html.json"));
  userPageHandler->setFieldCb.attach(userSetFieldCb);
  userPageHandler->loadCb.attach(userLoadCb);
}

void printloop(){
    char buf[MAX_STR_LEN];
    userReadStr(buf, EEPROM_POS_FIRST_NAME );
    webServer.setArgString(F("KP"), buf);
    mySerial.print(buf); 
    userReadStr( buf, EEPROM_POS_LAST_NAME );
    webServer.setArgString(F("KI"), buf);
    mySerial.print(buf); 
    webServer.setArgInt(F("KD"), (uint8_t)EEPROM[EEPROM_POS_AGE]);
    mySerial.print((uint8_t)EEPROM[EEPROM_POS_AGE]);
    mySerial.print("024420"); 
    mySerial.println();
}