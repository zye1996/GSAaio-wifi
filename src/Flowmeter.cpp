#include <Flowmeter.h>
#include <Wire.h>

void Flowmeter::begin(){
    Wire.begin();
}

int Flowmeter::readflow(){
    Wire.requestFrom(0x07, 2);    

  if (Wire.available()) {
        byte b1 = Wire.read();
        byte b2 = Wire.read();
        int b = b1*256+b2;
        return b;
    }
}