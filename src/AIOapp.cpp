#include "AIOapp.h"

SoftwareSerial mySerial(5, 6); // RX, TX

void AIOapp::begin(){
    //initialization
    for (int i = 0; i < ADC_NUM; i++){
        Adafruit_ADS1115 adc(ADC_ADDRESS[i]);
        adc.setSPS(ADS1115_DR_128SPS);
        adc.begin();
        adc_l[i] = adc;
    }
    _setResolution();

    valve_switch.begin(VALVE_SWITCH);
    pump.begin(PUMP);
    pump_speed(p_speed.airspeed);
    startsample();
    fmeter.begin();
}

void AIOapp::readRaw() {
    for(int i = 0; i < 4*ADC_NUM; i++){
        _raw_data[i] = adc_l[i/ADC_NUM].readADC_SingleEnded(i%ADC_NUM);
    }
    flowvalue = fmeter.readflow();    
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

void AIOapp::readVoltage() {
    readRaw();
    for(int i = 0; i < 4*ADC_NUM; i++){
        _voltage_data[i] = _resolution * _raw_data[i];
    }
}

void AIOapp::_setResolution() {
    switch (adc_l[0].getGain()){
        case GAIN_TWOTHIRDS:
            _resolution = 0.1875;
            break;
        case GAIN_ONE:
            _resolution = 0.125;
            break;
        case GAIN_TWO:
            _resolution = 0.0625;
            break;
        case GAIN_FOUR:
            _resolution = 0.03125;
            break;
        case GAIN_EIGHT:
            _resolution = 0.015625;
            break;
        case GAIN_SIXTEEN:
            _resolution = 0.0078125;
            break;
    }
}

void AIOapp::printData(){
    for (int i = 0; i < ADC_NUM*4; i++){
    mySerial.print(_voltage_data[i]*0.001,7);mySerial.print(",");
    }
    mySerial.print(flowvalue);
    mySerial.println();
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
        for(int i = 0; i< ADC_NUM*4 ; i++){
            _record_data[sample_count*ADC_NUM*4 + i ] = _voltage_data[i];      
        }       
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