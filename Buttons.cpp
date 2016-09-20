#include "buttons.h"
#include "pitches.h"

#define COLOR_RGB(r, g, b)                                    (((uint32_t)r << 16) | ((uint32_t)g <<  8) | b)

static Buttons *singleton = nullptr;

static void irq_buttons() {
    singleton->irq();
}

Button::Button(uint8_t sense, uint32_t note, uint8_t ledIndex, uint32_t color) :
    sense(sense), note(note), ledIndex(ledIndex), color(color) {
}

void Button::setup() {
    pinMode(sense, INPUT);
    attachInterrupt(digitalPinToInterrupt(sense), irq_buttons, RISING);
}

void Button::tick() {
    uint8_t pressedNow = digitalRead(sense);
    if (downAt > 0 && millis() - downAt > 50) {
        if (pressedNow) {
            pressed = true;
        }
        downAt = 0;
    }
}

void Button::irq() {
    rawPressed = digitalRead(sense);
    if (rawPressed && downAt == 0) {
        downAt = millis();
    }
}

void Buttons::play(uint8_t number) {
    Button *button = &buttons[number];
    pixels->setPixelColor(button->ledIndex, button->color);
    pixels->show();
    speaker->play(button->note);
}

Buttons::Buttons(Speaker *speaker, Adafruit_NeoPixel *pixels) :
    speaker(speaker), pixels(pixels),
    buttons({
            Button(PIN_BUTTON_SENSE_1, NOTE_C4, 0, COLOR_RGB(255, 0, 0)),
            Button(PIN_BUTTON_SENSE_2, NOTE_G3, 0, COLOR_RGB(0, 255, 0)),
            Button(PIN_BUTTON_SENSE_3, NOTE_A3, 0, COLOR_RGB(9, 0, 255)),
            Button(PIN_BUTTON_SENSE_4, NOTE_B3, 0, COLOR_RGB(255, 255, 0))
            }) {
    singleton = this;
}

void Buttons::off() {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        Button *button = &buttons[i];
        pixels->setPixelColor(button->ledIndex, COLOR_RGB(0, 0, 0));
        pixels->show();
    }
}

void Buttons::setup() {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        buttons[i].setup();
    }
}

void Buttons::tick() {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        buttons[i].tick();
    }
}

void Buttons::irq() {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        buttons[i].irq();
    }
}
