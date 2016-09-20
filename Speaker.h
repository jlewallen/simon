#ifndef SPEAKER_H_INCLUDED
#define SPEAKER_H_INCLUDED

#include <Arduino.h>

class Speaker {
private:
    uint32_t offTime;

public:
    void setup();
    void tick();
    void play(uint32_t note);
};

#endif
