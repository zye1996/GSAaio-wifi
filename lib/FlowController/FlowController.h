//
// Created by Zhenyi Ye on 5/20/21.
//

#ifndef GSAAIO_WIFI_FLOWCONTROLLER_H
#define GSAAIO_WIFI_FLOWCONTROLLER_H

#include <PID_v1.h>
#include <Arduino.h>
#include <Pump.h>
#include "define.h"

class FlowController {

public:

    FlowController()
            : controller(&this->input, &this->output, &this->setpoint, KP, KI, KD, P_ON_E, DIRECT) {};

    double getFlowRate();

    void setFlowRate(double target);

    void drivePump() const;

    void initPump(Pump *pump);

    void update();

    void init(Pump *pump);

    void setPID(double kp, double ki, double kd);

    void printData();

private:

    PID controller;
    Pump *pump;
    double Kp = KP, Ki = KI, Kd = KD;
    double setpoint, input, output;

};

#endif //GSAAIO_WIFI_FLOWCONTROLLER_H
