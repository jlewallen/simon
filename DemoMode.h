#ifndef DEMO_MODE_H_INCLUDED
#define DEMO_MODE_H_INCLUDED

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Buttons.h"

enum class DemoState {
    CHASE_FORWARD,
    CHASE_BACKWARD,
    THEATER_CHASE,
    FLASH,
    FADE,
    RAINBOW,
    RANDOM_TUNE
};

#define RANDOM_TUNE_LENGTH   4

class DemoMode {
private:
    Adafruit_NeoPixel *strip;
    Buttons *buttons;
    DemoState state;
    uint32_t startedAt;
    uint32_t transitionAt;
    uint32_t delayUntil;
    uint32_t colorsByIndex[4];
    int16_t position;
    int16_t direction;
    uint8_t tune[RANDOM_TUNE_LENGTH];

private:
    void chase();
    void theaterChase(uint32_t c);
    void flash();
    void rainbowCycle();
    void delayAndCheck(uint32_t ms);
    void generateRandomTune();
    uint32_t wheel(byte position);

public:
    DemoMode(Adafruit_NeoPixel *strip, Buttons *buttons);
    void tick();
    void start() {
        startedAt = millis();
    }

};

#endif
