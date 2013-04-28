#ifndef _SUNTALK
#define _SUNTALK

#define BASE_PERIOD 6000
#define _HIGH    (BASE_PERIOD / 5)
#define _LOW     (_HIGH * 2)
#define START   (_HIGH * 3)
#define STOP    (_HIGH * 4)

#define ONE         1
#define ZERO        0
#define START_BIT   2
#define STOP_BIT    3o

#include <Arduino.h>

class SunTalk
{
    public:
        SunTalk();
        ~SunTalk();
       void attach(int pin);
       void write(unsigned char *byte_buffer, int len);
       void write(int val);
       void write(String str);
    private:
       unsigned char buffer[128];
       int len;
       unsigned char char_byte;
       int _pin;
       void sendOne();
       void sendZero();
       void sendStart();
       void sendStop();
       void throwBits(int n);
};
extern SunTalk Suntalk;
#endif
