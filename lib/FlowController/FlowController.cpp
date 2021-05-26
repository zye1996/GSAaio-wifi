//
// Created by Zhenyi Ye on 5/20/21.
//

#include "FlowController.h"
#include <Wire.h>

double FlowController::getFlowRate() {

#ifndef FLOW_METER_ANALOG
    uint16_t rate;

    Wire.requestFrom(0x07, 2);    // request 6 bytes from slave device #8

    while (Wire.available()) { // slave may send less than requested
        byte b1 = Wire.read();
        byte b2 = Wire.read();// receive a byte as character
        rate = b1 << 8 | b2;
    }

    return rate;
#else
    double vout = analogRead(FLOW_METER_IN) * 5 / 1024.0;
    return 1000 * (vout - 1) * 0.25;
#endif

}

void FlowController::initPump(Pump *pump){
    this->pump = pump;
    this->pump->begin(PUMP);
}

void FlowController::drivePump() const{
    this->pump->set_speed(this->output);
}

void FlowController::init(Pump *pump) {
#ifdef FLOW_METER_ANALOG
    pinMode(FLOW_METER_IN, INPUT);
#endif
    this->initPump(pump);
    this->controller.SetOutputLimits(0, 255); // if PWM
    this->setFlowRate(DEFAULT_FLOW_RATE); // set default flow rate
    this->controller.SetMode(AUTOMATIC);
}

void FlowController::setFlowRate(double target){
    this->setpoint = target;
}

void FlowController::setPID(double kp, double ki, double kd) {
    this->Kp = kp;
    this->Ki = ki;
    this->Kd = kd;
    this->controller.SetTunings(this->Kp, this->Kd, this->Ki);
}

void FlowController::update() {
    this->input = this->getFlowRate();
    this->controller.Compute();
    this->drivePump();
}

void FlowController::printData() {
    DEBUG_SERIAL.print(this->input);
    DEBUG_SERIAL.print(',');
    DEBUG_SERIAL.print(this->output);
    DEBUG_SERIAL.print(',');
}