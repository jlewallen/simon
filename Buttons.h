#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Speaker.h"

#define NUMBER_OF_BUTTONS                     4
#define PIN_BUTTON_SENSE_1                    A1
#define PIN_BUTTON_SENSE_2                    A2
#define PIN_BUTTON_SENSE_3                    A3
#define PIN_BUTTON_SENSE_4                    A4

class Button {
    friend class Buttons;

private:
    uint8_t sense;
    uint32_t note;
    uint8_t ledIndex;
    uint32_t color;
    bool pressed;

public:
    Button(uint8_t sense, uint32_t note, uint8_t ledIndex, uint32_t color);

public:
    boolean wasPressed() {
        bool yes = pressed;
        pressed = false;
        return yes;
    }
};

class Buttons {
private:
    Speaker *speaker;
    Adafruit_NeoPixel *pixels;
    Button buttons[NUMBER_OF_BUTTONS];
    bool areAnyOn;

public:
    Buttons(Speaker *speaker, Adafruit_NeoPixel *pixels);

public:
    bool anyOn() {
        return areAnyOn;
    }
    void off();
    void setup();
    void tick();
    void irq();
    void play(uint8_t number);
    void fail();
    int8_t dequeuePress() {
        for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
            if (buttons[i].wasPressed()) {
                return i;
            }
        }
        return -1;
    }
};

#endif
