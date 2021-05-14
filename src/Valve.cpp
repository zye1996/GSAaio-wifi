#include "Valve.h"

void Valve::begin(uint8_t pinNum) {
    pinMode(pinNum, OUTPUT);
    pin_num = pinNum;
}

void Valve::turn_on() {

    digitalWrite(pin_num, HIGH);

}

void Valve::turn_off() {
    digitalWrite(pin_num, LOW);
}