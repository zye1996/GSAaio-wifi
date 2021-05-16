#ifndef GSAAIO_AIOAPP_H
#define GSAAIO_AIOAPP_H
#include <Adafruit_ADS1015.h>
#include <define.h>
#include <SoftwareSerial.h>
#include <Valve.h>
#include <Pump.h>
#include <Flowmeter.h>



const uint8_t ADC_ADDRESS[] = {0x48, 0x49, 0x4a, 0x4b};
extern SoftwareSerial mySerial; 
const uint32_t UPDATE_INTERVAL = 500;

struct AppConfig{
    uint8_t airspeed = 80;
    uint8_t fragspeed = 80;
};

class AIOapp {

    public:
        AIOapp(){};
        void printData();
        void readVoltage();
        void readRaw();
        void fragOn();
        void fragOff();
        void begin();
        void airFlow();
        void targetgasFlow();
        void startsample();
        void stopsample();
        void sampling();
        inline void update() __attribute__((always_inline));
        void pump_speed(uint8_t speed);
        
        void fragFlow(uint8_t speed);
        void airFlow(uint8_t speed);
        
    private:
        Adafruit_ADS1115 adc_l[ADC_NUM];
        uint16_t _raw_data[4*ADC_NUM];
        float _voltage_data[4*ADC_NUM];
        float _record_data[4*ADC_NUM*SAMPLE_NUM];
        float _resolution;
        void _setResolution();
        unsigned long last_release;
        Valve valve_switch;
        bool Sample_flag;
        int16_t sample_count = -1;
        uint16_t sample_period = 0;
        Pump pump1;
        uint8_t p_speed=100;
        Flowmeter fmeter;
        int flowvalue;
        
};

void AIOapp::update() {
    //TODO : Interval
    unsigned long cur = millis();
    if (cur - last_release >= UPDATE_INTERVAL){
        last_release = cur;
        readVoltage();
        if (Sample_flag && (sample_count >= 0)){
            sampling();
         }
        printData();
    }
    

}

#endif //GSAAIO_AIOAPP_H