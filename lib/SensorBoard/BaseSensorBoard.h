//
// Created by Zhenyi Ye on 5/25/21.
//

#ifndef GSAAIO_WIFI_BASESENSORBOARD_H
#define GSAAIO_WIFI_BASESENSORBOARD_H

#include <map>

class Stream;

class BaseSensorBoard {
public:
    explicit BaseSensorBoard(Stream* ser):_ser(ser){};
    virtual void begin() = 0;
    virtual void read() = 0;
    virtual void print() = 0;

protected:
    Stream *_ser;
};


#endif //GSAAIO_WIFI_BASESENSORBOARD_H
