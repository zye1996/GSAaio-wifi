#ifndef GSAAIO_DEFINES_H
#define GSAAIO_DEFINES_H

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <HardwareSerial.h>

// extern SoftwareSerial mySerial(5, 6);
// #define SLAVE_SERIAL mySerial

// #define DEBUG_SERIAL Serial
// #define DBGprint(...) Serial.print(__VA_ARGS__)
// #define DBGprintln(...) Serial.println(__VA_ARGS__)
// 


#define ADC_NUM 4

#define SAMPLE_NUM 800 //800
#define SAMPLE_DUR 1600 //1600
#define SAMPLE_VALVE_ON 1700 //10
#define SAMPLE_VALVE_OFF 1702 //12
#define SAMPLE_PERIOD 20
 
#define VALVE_SWITCH 12
#define OLD_PUMP 13
#define PUMP A2


#define DEBUG_SERIAL Serial3

#endif //GSAAIO_DEFINES_H