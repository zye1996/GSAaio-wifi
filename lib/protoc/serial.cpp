#include "serial.h"
#include "AIOapp.h"
#include "SoftwareSerial.h"
// #include <Arduino.h>

SoftwareSerial mySerial(5, 6); // RX, TX

msgBuff rxBuff;
msgBuff txBuff;
bool ser_escape = false;
bool ser_reading = false;
uint8_t rxByte;

void (*msgHandler)();

void setNewMsgCallback(void (*cb)(void)) {
  msgHandler = cb;
}

void parseSerial()
{
    while(mySerial.available()) {
        rxByte = mySerial.read();
        // mySerial.println(rxByte,HEX);
        if (!ser_escape) {
            if (rxByte == '^') {
                rxBuff.len = 0;
                ser_reading = true;
                return;
            }
            if (rxByte == '?' && ser_reading) {
                ser_escape = true;
                return;
            }
            if (rxByte == '\n') {
                ser_reading = false;
                // DBGprint("Len: ");
                // DBGprintln(rxBuff.len);
                parseCmd();
            }
        }
        if (ser_reading && rxBuff.len < S_BUFF_SIZE) {
            if (ser_escape) {
                ser_escape = false;
            }
            rxBuff.buff[rxBuff.len++] = rxByte;
            return;
        }
        if (rxBuff.len >= S_BUFF_SIZE) {
            rxBuff.len = 0;
            ser_reading = false;
            ser_escape = false;
        }
    }
}

void parseCmd()
{

  byte our_csum = calcRX_CSum(&rxBuff);
  byte snt_csum = rxBuff.buff[rxBuff.len - 1];

  if (our_csum != snt_csum) {
    //complete csum error return
    //SLAVE_SERIAL.write("^E\n");
  }
  else{
    //SLAVE_SERIAL.println("{\"RESP\":1}");

    msgHandler();
  }
}

uint8_t calcRX_CSum(msgBuff *mb)
{
  return calc_CSum(mb->buff, mb->len - 1);
}

uint8_t calcTX_CSum(msgBuff *mb)
{
  return calc_CSum(mb->buff, mb->len);
}

uint8_t calc_CSum(uint8_t *buff, uint16_t len)
{
  uint8_t csum = 0;
  for (uint16_t i = 0; i < len; i++)
  {
      csum ^= *(buff + i);
  }
  return csum;
}


bool msgBuffAddByte(msgBuff *mb, uint8_t b)
{
  if (mb->len < S_BUFF_SIZE) {
    mb->buff[mb->len++] = b;
    return true;
  }
  return false;
}

bool msgBuffAdd(msgBuff *mb, void * data, uint16_t size)
{
  if (mb->len + size >= S_BUFF_SIZE)
  {
    return false;
  }
  uint8_t *b = (mb->buff + mb->len);
  uint8_t *d = (uint8_t *)data;
  
  for (uint16_t i = 0; i < size; i++) {
    *(b + i) = *(d + i);
  }
  mb->len += size;
  return true;
}

void sendMsgBuff(msgBuff *mb) 
{
  uint8_t csum = calcTX_CSum(mb);
  msgBuffAddByte(mb,csum);
  mySerial.write('^');
  for (uint16_t i = 0; i < mb->len; i++) {
    switch (mb->buff[i])
    {
      case '?':
      case '^':
      case '\n': 
        mySerial.write('?');
      default:
        mySerial.write(mb->buff[i]);
    }
  }
  mySerial.write('\n');
}


