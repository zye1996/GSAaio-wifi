#include <Pump.h>

void Pump::begin(uint8_t pinNum) {
    pinMode(pinNum, OUTPUT);
    pin_num = pinNum;
}

void Pump::set_speed(uint8_t speed) {
    if (speed==0){
        stop();
        return;
    }
    // DBGprintln(speed);
    analogWrite(pin_num, speed);
}

void Pump::stop() {
    analogWrite(pin_num, 0);
}