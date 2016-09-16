#include <Arduino.h>

#include "pitches.h"

#define PIN_SPEAKER                     A0

uint32_t melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

uint32_t durations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
    pinMode(PIN_SPEAKER, OUTPUT);

    while (true) {
        // tone(PIN_SPEAKER, NOTE_C4);
        // delay(1000);
        // noTone(PIN_SPEAKER);

        for (uint8_t thisNote = 0; thisNote < 8; thisNote++) {
            uint32_t duration = 1000 / durations[thisNote];
            tone(PIN_SPEAKER, melody[thisNote], duration);
            uint32_t pauseBetweenNotes = duration * 1.30;
            delay(pauseBetweenNotes);
            noTone(PIN_SPEAKER);
        }

        delay(1000);
    }
}

void loop() {

}
