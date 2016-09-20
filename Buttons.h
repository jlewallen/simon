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
    uint8_t rawPressed;
    uint32_t note;
    uint32_t downAt;
    uint8_t ledIndex;
    uint32_t color;
    bool pressed;

public:
    Button(uint8_t sense, uint32_t note, uint8_t ledIndex, uint32_t color);

public:
    void setup();
    void tick();
    void irq();
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

public:
    Buttons(Speaker *speaker, Adafruit_NeoPixel *pixels);

public:
    void setup();
    void tick();
    void irq();
    int8_t anyPressed() {
        for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
            if (buttons[i].wasPressed()) {
                return i;
            }
        }
        return -1;
    }

};

#endif
