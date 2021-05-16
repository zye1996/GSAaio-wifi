#ifndef GSAAIO_PROTOC_H
#define GSAAIO_PROTOC_H

#endif //GSAAIO_PROTOC_H

#include <Arduino.h>
#include "serial.h"

// DEBUG COMMAND
const uint8_t VALVE_SET    = 0xF0;
const uint8_t PUMP_PWM     = 0xF1;

// FUNCTIONAL COMMAND
const uint8_t AIRFLOW      = 0x00;
const uint8_t FRAGFLOW     = 0x01;
const uint8_t CHAMCLOSE    = 0x02;



// Function Header
void parseAirflow();
void parseFragflow();


void parseValveSet();
void parsePumpPwm();

// Parse Command Function