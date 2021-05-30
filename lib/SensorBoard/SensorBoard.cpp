//
// Created by Zhenyi Ye on 5/25/21.
//

#include "SensorBoard.h"
#include <Stream.h>

void SensorBoard::begin() {
    //initialization
    for (int i = 0; i < ADC_NUM; i++){
        // Adafruit_ADS1115 adc;
        // adc.setDataRate(RATE_ADS1115_128SPS);
        // adc.begin(ADC_ADDRESS[i]);
        Adafruit_ADS1115 adc(ADC_ADDRESS[i]);
        adc.setSPS(ADS1115_DR_128SPS);
        adc.begin();
        adc_l[i] = adc;
    }
    _setResolution();
}

void SensorBoard::read() {}

void SensorBoard::readRaw() {
    for(int i = 0; i < 4*ADC_NUM; i++){
        _raw_data[i] = adc_l[i/ADC_NUM].readADC_SingleEnded(i%ADC_NUM);
    }
}

void SensorBoard::readVoltage() {
    readRaw();
    for(int i = 0; i < 4*ADC_NUM; i++){
    _voltage_data[i] = _resolution * _raw_data[i];
    }
}

void SensorBoard::print() {
    for (double i : _voltage_data){
        _ser->print(i*0.001,7); _ser->print(",");
    }
    _ser->println();
}

void SensorBoard::_setResolution() {
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