//
// Created by Zhenyi Ye on 5/25/21.
//

#ifndef GSAAIO_WIFI_SENSORBOARD_H
#define GSAAIO_WIFI_SENSORBOARD_H

#include "BaseSensorBoard.h"
#include "Adafruit_ADS1X15.h"
#include "define.h"

const uint8_t ADC_ADDRESS[] = {0x48, 0x49, 0x4a, 0x4b};
const uint8_t ADC_NUM = 4;

class Stream;

class SensorBoard: public BaseSensorBoard {
public:
    SensorBoard(Stream* ser): BaseSensorBoard(ser){};
    void begin() override;
    void read() override;
    void print() override;
    void dump();

    void readVoltage();
    void readRaw();

private:
    void _setResolution();

    Adafruit_ADS1115 adc_l[ADC_NUM];
    uint16_t _raw_data[4*ADC_NUM] = {0};
    double _voltage_data[4*ADC_NUM] = {0};
    double _record_data[4*ADC_NUM*SAMPLE_NUM] = {0};
    double _resolution;
};


#endif //GSAAIO_WIFI_SENSORBOARD_H
