#include "Buttons.h"
#include "pitches.h"
#include "vibrations.h"

#define COLOR_RGB(r, g, b)                                    (((uint32_t)r << 16) | ((uint32_t)g <<  8) | b)

Button::Button(uint8_t sense, uint32_t note, uint8_t ledIndex, uint32_t color) :
    sense(sense), note(note), ledIndex(ledIndex), color(color), pressed(false) {
}

void Button::setup() {

}

void Button::tick() {

}

void Button::irq() {

}

void Buttons::play(uint8_t number) {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        Button *button = &buttons[i];
        pixels->setPixelColor(button->ledIndex, COLOR_RGB(0, 0, 0));
    }

    Button *button = &buttons[number];
    pixels->setPixelColor(button->ledIndex, button->color);
    pixels->show();
    speaker->play(button->note);
}

void Buttons::fail() {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        Button *button = &buttons[i];
        pixels->setPixelColor(button->ledIndex, COLOR_RGB(128, 128, 128));
    }
    pixels->show();
    speaker->fail();
}

Buttons::Buttons(Speaker *speaker, Adafruit_NeoPixel *pixels) :
    speaker(speaker), pixels(pixels),
    buttons({
            Button(PIN_BUTTON_SENSE_1, NOTE_C4, 0, COLOR_RGB(255, 0, 0)),
            Button(PIN_BUTTON_SENSE_3, NOTE_A3, 1, COLOR_RGB(9, 0, 255)),
            Button(PIN_BUTTON_SENSE_4, NOTE_B3, 2, COLOR_RGB(255, 255, 0)),
            Button(PIN_BUTTON_SENSE_2, NOTE_G3, 3, COLOR_RGB(0, 255, 0)),
            }) {
}

void Buttons::off() {
    for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
        Button *button = &buttons[i];
        pixels->setPixelColor(button->ledIndex, COLOR_RGB(0, 0, 0));
        pixels->show();
    }
}

void Buttons::setup() {
    vibration_sensors_setup(vibrationSensors);
}

void Buttons::tick() {
    vibration_sensor_t *pressed = vibration_sensors_detect_press(vibrationSensors);
    if (pressed != nullptr) {
        for (uint8_t i = 0; i < NUMBER_OF_BUTTONS; ++i) {
            if (buttons[i].sense == pressed->pin) {
                buttons[i].pressed = true;
            }
        }
    }
}

void Buttons::irq() {

}
