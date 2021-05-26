#ifndef GSAAIO_DEFINES_H
#define GSAAIO_DEFINES_H

#define SAMPLE_NUM 800 //800
#define SAMPLE_DUR 1600 //1600
#define SAMPLE_VALVE_ON 1700 //10
#define SAMPLE_VALVE_OFF 1702 //12
#define SAMPLE_PERIOD 20
 
#define VALVE_SWITCH 12
#define OLD_PUMP 13

#define PUMP A2
#define DEFAULT_FLOW_RATE 400
// #define FLOW_METER_ANALOG

const double KP = 0.3;
const double KI = 0.1;
const double KD = 0;

#define DEBUG_SERIAL Serial3

#endif //GSAAIO_DEFINES_H