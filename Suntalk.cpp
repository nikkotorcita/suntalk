#ifndef _SUNTALK_CPP
#define _SUNTALK_CPP

#include "Arduino.h"
#include "Suntalk.h"

SunTalk Suntalk;

SunTalk::SunTalk() {
    len = 0;
    char_byte = 0;
}

SunTalk::~SunTalk() {

}

void SunTalk::attach(int pin) {
    pinMode(pin, OUTPUT);
    _pin = pin;
}

void SunTalk::write(unsigned char *byte_buffer, int len) {
    unsigned char buf = 0;
    
    throwBits(12);
    for(int i = 0; i < len; i++) {
        buf = *(byte_buffer + i);
        sendStart();
        for(int j = 0; j < 8; j++) {
            if((buf & (128 >> j)) > 0)
                sendOne();
            else
                sendZero();
        }
        sendStop();
    }
    throwBits(1);
}

void SunTalk::write(int val) {
    throwBits(12);
    sendStart();
    for(int i = 0; i < 8; i++) {
        if((val & (128 >> i)) > 0)
            sendOne();
        else
            sendZero();
    }
    sendStop();
    throwBits(1);
}

void SunTalk::write(String str) {
    unsigned char buf = 0;
    unsigned char char_array[128];
    int len;

    len = str.length();
    str.getBytes(char_array, 128);

    throwBits(12);
    for(int i = 0; i < len; i++) {
        buf = char_array[i];
        sendStart();
        for(int j = 0; j < 8; j++) {
            if((buf & (128 >> j)) > 0)
                sendOne();
            else
                sendZero();
        }
        sendStop();
    }
    throwBits(1);
}

void SunTalk::sendOne() {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(BASE_PERIOD - _HIGH);
    digitalWrite(_pin, LOW);
    delayMicroseconds(_HIGH);
}

void SunTalk::sendZero() {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(BASE_PERIOD - _LOW);
    digitalWrite(_pin, LOW);
    delayMicroseconds(_LOW);
}

void SunTalk::sendStart() {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(BASE_PERIOD - START);
    digitalWrite(_pin, LOW);
    delayMicroseconds(START);
}

void SunTalk::sendStop() {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(BASE_PERIOD - STOP);
    digitalWrite(_pin, LOW);
    delayMicroseconds(STOP);
}

void SunTalk::throwBits(int n) {
    for(int i = 0; i < n; i++)
        sendOne();
}
#endif
