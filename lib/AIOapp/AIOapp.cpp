#include "AIOapp.h"
#include "SoftwareSerial.h"

extern SoftwareSerial mySerial;

AIOapp::AIOapp(Stream *comm_ser, Stream *debug_ser):_comm_ser(comm_ser), _dbg_ser(debug_ser), sensorBoard(debug_ser){}

void AIOapp::begin(){
    sensorBoard.begin();
    valve_switch.begin(VALVE_SWITCH);
    pump.begin(PUMP);
    pump_speed(p_speed.airspeed);
    // startsample();
    f_ctler.init(&pump);
}

void AIOapp::readSensor() {
    sensorBoard.readVoltage();
}

void AIOapp::pump_speed(uint8_t speed) {
    pump.set_speed(speed);
}

void AIOapp::fragOn() {
    valve_switch.turn_on();
}

/* turn off target gas */
void AIOapp::fragOff() {
    valve_switch.turn_off();
}

void AIOapp::fragFlow(uint8_t speed) {
    fragOn();
    pump.set_speed(p_speed.fragspeed);
}

/* let air gas flow */
void AIOapp::airFlow(uint8_t speed) {
    fragOff();
    pump.set_speed(p_speed.airspeed);
}

void AIOapp::printData(){
    sensorBoard.print();
}

void AIOapp::startsample(){
    Sample_flag = true;
    sample_count = 0;
    sample_period = 0; 
}

void AIOapp::stopsample(){
    Sample_flag = false;
    sample_count = -1;
    sample_period = 0;
    valve_switch.turn_off();    
}

void AIOapp::sampling(){
    if(sample_count == SAMPLE_VALVE_ON){
        valve_switch.turn_on();
    }
    if(sample_count == SAMPLE_VALVE_OFF){
        valve_switch.turn_off();
    }
    if(0 <= sample_count && sample_count <SAMPLE_NUM){
        //TODO:SD
    }
    sample_count ++;
    if(sample_count == SAMPLE_DUR){
        sample_count=0;
        sample_period++;
    }
    if(sample_period == SAMPLE_PERIOD){
        stopsample();
    }
}