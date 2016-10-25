#ifndef DEMO_MODE_H_INCLUDED
#define DEMO_MODE_H_INCLUDED

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Buttons.h"

enum class DemoState {
    CHASE,
    THEATER_CHASE,
    FLASH,
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
    uint8_t position;
    uint8_t tune[RANDOM_TUNE_LENGTH];

public:
    DemoMode(Adafruit_NeoPixel *strip, Buttons *buttons);
    void chase();
    void theaterChase(uint32_t c);
    void flash();
    void tick();
    void delayAndCheck(uint32_t ms);
    void generateRandomTune();
    void start() {
        startedAt = millis();
    }

};

#endif
