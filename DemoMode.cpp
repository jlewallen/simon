#include "DemoMode.h"

DemoMode::DemoMode(Adafruit_NeoPixel *strip) :
    strip(strip), state(DemoState::FLASH), transitionAt(0), delayUntil(0) {
    colorsByIndex[0] = strip->Color(255, 0, 0);
    colorsByIndex[1] = strip->Color(0, 0, 255);
    colorsByIndex[2] = strip->Color(255, 255, 0);
    colorsByIndex[3] = strip->Color(0, 255, 0);
}

void DemoMode::delayAndCheck(uint32_t ms) {
    delayUntil = millis() + ms;
}

void DemoMode::chase() {
    for (uint8_t j = 0; j < 4; ++j) {
        if  (position % 4 == j) {
            strip->setPixelColor(j, colorsByIndex[j]);
        }
        else {
            strip->setPixelColor(j, strip->Color(0, 0, 0));
        }
    }
    strip->show();
    delayAndCheck(100);
    position++;
}

void DemoMode::theaterChase(uint32_t c) {
    for (uint8_t q = 0; q < 3; q++) {
        for (uint8_t i = 0; i < 4; i= i + 3) {
            strip->setPixelColor(i + q, c);
        }
        strip->show();

        delay(50);

        for (uint8_t i = 0; i < 4; i = i +3) {
            strip->setPixelColor(i + q, 0);
        }
    }
}

void DemoMode::flash() {
    if (position % 2 == 0) {
        for (uint8_t i = 0; i < 4; ++i) {
            strip->setPixelColor(i, colorsByIndex[i]);
        }
    }
    else {
        for (uint8_t i = 0; i < 4; ++i) {
            strip->setPixelColor(i, strip->Color(0, 0, 0));
        }
    }

    strip->show();
    delayAndCheck(250);
    position++;

}

void DemoMode::tick() {
    if (delayUntil > 0) {
        if (millis() >= delayUntil) {
            delayUntil = 0;
        }
        return;
    }
    switch (state) {
    case DemoState::FLASH: {
        if (millis() - transitionAt > 5 * 1000) {
            transitionAt = millis();
            state = DemoState::CHASE;
            position = 0;
        }
        flash();
        break;
    }
    case DemoState::CHASE: {
        if (millis() - transitionAt > 5 * 1000) {
            transitionAt = millis();
            state = DemoState::THEATER_CHASE;
            position = 0;
        }
        chase();
        break;
    }
    case DemoState::THEATER_CHASE: {
        if (millis() - transitionAt > 5 * 1000) {
            transitionAt = millis();
            state = DemoState::FLASH;
            position = 0;
        }
        theaterChase(strip->Color(255, 255, 255));
        break;
    }
    }
}
