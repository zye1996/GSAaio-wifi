#ifndef GSAAIO_VALVE_H
#define GSAAIO_VALVE_H

#include <Arduino.h>

class Valve {

    public:
        void begin(uint8_t pinNum);
        void turn_on();
        void turn_off();

    private:
        uint8_t pin_num;
};


#endif //GSAAIO_VALVE_H