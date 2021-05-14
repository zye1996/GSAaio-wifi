#ifndef GSAAIO_PUMP_H
#define GSAAIO_PUMP_H

#include <define.h>
#include <Arduino.h>

class Pump {

    public:
        void begin(uint8_t pinNum);
        void set_speed(uint8_t speed);
        void stop();

    private:
        uint8_t pin_num;
};


#endif //GSAAIO_PUMP_H