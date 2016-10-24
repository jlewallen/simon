#ifndef DEMO_MODE_H_INCLUDED
#define DEMO_MODE_H_INCLUDED

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

enum class DemoState {
    CHASE,
    THEATER_CHASE,
    FLASH
};

class DemoMode {
private:
    DemoState state;
    uint32_t transitionAt;
    uint32_t delayUntil;
    Adafruit_NeoPixel *strip;
    uint32_t colorsByIndex[4];
    uint8_t position;

public:
    DemoMode(Adafruit_NeoPixel *strip);
    void chase();
    void theaterChase(uint32_t c);
    void flash();
    void tick();
    void delayAndCheck(uint32_t ms);

};

#endif
