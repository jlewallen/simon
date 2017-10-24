#include "Speaker.h"

#define PIN_SPEAKER_SOUND                     A0
#define PIN_SPEAKER_ENABLE                    6

void Speaker::setup() {
    pinMode(PIN_SPEAKER_ENABLE, OUTPUT);
    digitalWrite(PIN_SPEAKER_ENABLE, LOW);

    pinMode(PIN_SPEAKER_SOUND, OUTPUT);
#ifndef ARDUINO_SAMD_ZERO
    // On the ATSAMD this will hang if, gotta call tone first.
    noTone(PIN_SPEAKER_SOUND);
#endif
}

void Speaker::fail() {
    digitalWrite(PIN_SPEAKER_ENABLE, HIGH);
    tone(PIN_SPEAKER_SOUND, NOTE_C2);
    offTime = millis() + 1000;
}

void Speaker::play(uint32_t note) {
    digitalWrite(PIN_SPEAKER_ENABLE, HIGH);
    tone(PIN_SPEAKER_SOUND, note, 500);
    offTime = millis() + 500;
}

void Speaker::tick() {
    if (offTime > 0 && millis() > offTime) {
        digitalWrite(PIN_SPEAKER_ENABLE, LOW);
        noTone(PIN_SPEAKER_SOUND);
        offTime = 0;
    }
}
