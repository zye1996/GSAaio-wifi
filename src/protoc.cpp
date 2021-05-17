#include <protoc.h>
#include <AIOapp.h>

extern AIOapp aiOapp;
extern msgBuff txBuff;
extern msgBuff rxBuff;

// app configuration
AppConfig appConfig;

// Functional Command
void parseAirflow(){
    aiOapp.airFlow(appConfig.airspeed);
    // mySerial.println("command accepted");
}

void parseFragflow(){
    aiOapp.fragFlow(appConfig.fragspeed);
}

// Debug Command
void parsePumpPwm(){
    uint8_t speed = rxBuff.buff[1];
    aiOapp.airFlow(speed);
}

void parseValveSet(){
    uint8_t valve_index = rxBuff.buff[1];
    uint8_t valve_state = rxBuff.buff[2];
    if (valve_state == 1)
        valve_state = HIGH;
    else
        valve_state = LOW;
    switch (valve_index){
        case 1:
            break;
        case 2:
            break;
        case 3:
            digitalWrite(VALVE_SWITCH, valve_state);
            break;
        default:
            break;

    }
}

// Parse Command Function
void parseCommand(){

    uint8_t command_type = rxBuff.buff[0];

    switch (command_type){

        // functional command
        case AIRFLOW:
            parseAirflow();
            break;
        case FRAGFLOW:
            parseFragflow();
            break;
        case CHAMCLOSE:
            break;

        // debug command
        case PUMP_PWM:
            parsePumpPwm();
            break;
        case VALVE_SET:
            parseValveSet();
            break;
    }

}