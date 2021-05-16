#include <stdint.h>
#include <AIOapp.h>
#include <define.h>

#ifdef _SERIAL_
#else
#define _SERIAL_

const uint8_t S_BUFF_SIZE = 255;

typedef struct msgBuff {
	uint16_t len;
	uint8_t buff[S_BUFF_SIZE];
} msgBuff;


//void parseSerial();
//void parseCmd();
void parseSerial();
void parseCmd();

uint8_t calcRX_CSum(msgBuff *mb);
uint8_t calcTX_CSum(msgBuff *mb);
uint8_t calc_CSum(uint8_t *buff, uint16_t len);

bool msgBuffAddByte(msgBuff *mb, uint8_t b);
bool msgBuffAdd(msgBuff *mb, void * data, uint16_t size);
void sendMsgBuff(msgBuff *mb);
void setNewMsgCallback(void (*cb)(void));

void sendTemps(msgBuff *mb);
void sendRecipe(msgBuff *mb);


#endif