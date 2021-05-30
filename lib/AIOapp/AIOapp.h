#ifndef GSAAIO_AIOAPP_H
#define GSAAIO_AIOAPP_H

#include <define.h>
#include "AIOapp.h"
#include "ELClientWebServer.h"
#include "FlowController.h"
#include "SensorBoard.h"
#include "Valve.h"
#include "Pump.h"

const uint32_t UPDATE_INTERVAL = 500;

struct AppConfig{
    uint8_t airspeed = 80;
    uint8_t fragspeed = 80;
};

class AIOapp {

    public:
        AIOapp(Stream *comm_ser, Stream *debug_ser);
        void printData();
        void readSensor();
        void fragOn();
        void fragOff();
        void begin();

        void startsample();
        void stopsample();
        void sampling();

        void pump_speed(uint8_t speed);
        void fragFlow(uint8_t speed);
        void airFlow(uint8_t speed);

        void update(){
            //TODO : Interval
            unsigned long cur = millis();
            if (cur - last_release >= UPDATE_INTERVAL){
                last_release = cur;
                readSensor();
                if (Sample_flag && (sample_count >= 0)){
                    sampling();
                }
                printData();
            }
        }
        
    private:

        unsigned long last_release = 0;
        bool Sample_flag;
        int16_t sample_count = -1;
        uint16_t sample_period = 0;

        // ELClient esp;
        Stream * _comm_ser;
        Stream * _dbg_ser;

        SensorBoard sensorBoard;
        Valve valve_switch;
        Pump pump;
        FlowController f_ctler;
        AppConfig p_speed = {30, 30};

};

#endif //GSAAIO_AIOAPP_H