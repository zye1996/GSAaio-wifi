// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <PID_v1.h>
#include <Wire.h>

double Setpoint = 100;
int manualSetpoint = 50;
double Output ;
double Input ;
//double Kp=2, Ki=1, Kd=0;//connect to valve common inlet ,turn off
//double Kp=0.2, Ki=0.2, Kd=0;//connect to no valve
//double Kp=0.3, Ki=0.1, Kd=0;
//double Kp=1, Ki=0.3, Kd=0;//new pump,with pump turned off,delay(100);
double Kp=0.1,Ki=0.1, Kd=0;//new pump,with pump turned on,delay(100);
const int ValvePin = 11;
PID pid_controler = PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

const int Pum_pin = 3; 
const int Pum_supply = 6;
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output

  pid_controler.SetOutputLimits(0, 90);
//turn the PID on
  pid_controler.SetMode(AUTOMATIC);
  analogWrite(Pum_pin, 80);
  pinMode(ValvePin, OUTPUT);
  digitalWrite(ValvePin,HIGH);
  analogWrite(Pum_supply, 255);
}

//void loop() {
//for(Setpoint = 500; Setpoint <=600;Setpoint++){
//  for(int i=0;i<40;i++){
//    Wire.requestFrom(0x07, 2);    // request 2 bytes from slave device #8
//    int b ;
//    if (Wire.available()) { // slave may send less than requested
//        byte b1 = Wire.read();
//        byte b2 = Wire.read();// receive a byte as character
//        b = b1*256+b2;
//        
//        delay(200);
//    }
//    Input = b;
//    Serial.print("Mass Flow:");
//    Serial.print(Input);
//    Serial.print(",");
//    Serial.print("Setpoint:");
//    Serial.print(Setpoint);
//    if (!pid_controler.Compute()){
//        Serial.println("Compute Failed!");
//        //analogWrite(Pum_pin, manualSetpoint);
//        return;
//    }
//    analogWrite(Pum_pin, Output);
//    Serial.print(",");
//    Serial.print("PWM:");
//    Serial.println(Output);
//  }
//  analogWrite(Pum_pin, 0);
//  }
//}

void loop() {
    Wire.requestFrom(0x07, 2);    // request 2 bytes from slave device #8
    int b ;
    if (Wire.available()) { // slave may send less than requested
        byte b1 = Wire.read();
        byte b2 = Wire.read();// receive a byte as character
        b = b1*256+b2;
        
        delay(100);
    }
    Input = b;
    Serial.print("Mass Flow:");
    Serial.print(Input);
    Serial.print(",");
    Serial.print("Setpoint:");
    Serial.print(Setpoint);
    if (!pid_controler.Compute()){
        Serial.println("Compute Failed!");
        //analogWrite(Pum_pin, manualSetpoint);
        return;
    }
    analogWrite(Pum_pin, Output);
    Serial.print(",");
    Serial.print("PWM:");
    Serial.println(Output);
 }
