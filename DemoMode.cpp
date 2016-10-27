#include "DemoMode.h"

#define NUMBER_OF_PIXELS                                      4

DemoMode::DemoMode(Adafruit_NeoPixel *strip, Buttons *buttons) :
    strip(strip), buttons(buttons), state(DemoState::FLASH), transitionAt(0), delayUntil(0), startedAt(0), position(0), direction(1) {
    colorsByIndex[0] = strip->Color(255, 0, 0);
    colorsByIndex[1] = strip->Color(0, 0, 255);
    colorsByIndex[2] = strip->Color(255, 255, 0);
    colorsByIndex[3] = strip->Color(0, 255, 0);
}

void DemoMode::delayAndCheck(uint32_t ms) {
    delayUntil = millis() + ms;
}

uint32_t DemoMode::wheel(byte position) {
    position = 255 - position;
    if(position < 85) {
        return strip->Color(255 - position * 3, 0, position * 3);
    }
    if(position < 170) {
        position -= 85;
        return strip->Color(0, position * 3, 255 - position * 3);
    }
    position -= 170;
    return strip->Color(position * 3, 255 - position * 3, 0);
}

void DemoMode::chase() {
    for (uint8_t j = 0; j < NUMBER_OF_PIXELS; ++j) {
        if  (position == j) {
            strip->setPixelColor(j, colorsByIndex[j]);
        }
        else {
            strip->setPixelColor(j, strip->Color(0, 0, 0));
        }
    }
    strip->show();
    delayAndCheck(100);

    position += direction;
    if (position > NUMBER_OF_PIXELS - 1) position = 0;
    if (position < 0) position = NUMBER_OF_PIXELS - 1;
}

void DemoMode::theaterChase(uint32_t c) {
    for (uint8_t q = 0; q < 3; q++) {
        for (uint8_t i = 0; i < NUMBER_OF_PIXELS; i= i + 3) {
            strip->setPixelColor(i + q, c);
        }
        strip->show();

        delay(50);

        for (uint8_t i = 0; i < NUMBER_OF_PIXELS; i = i +3) {
            strip->setPixelColor(i + q, 0);
        }
    }
}

void DemoMode::flash() {
    if (position % 2 == 0) {
        for (uint8_t i = 0; i < NUMBER_OF_PIXELS; ++i) {
            strip->setPixelColor(i, colorsByIndex[i]);
        }
    }
    else {
        for (uint8_t i = 0; i < NUMBER_OF_PIXELS; ++i) {
            strip->setPixelColor(i, strip->Color(0, 0, 0));
        }
    }

    strip->show();
    delayAndCheck(250);
    position++;

}

void DemoMode::generateRandomTune() {
    for (uint8_t i = 0; i < RANDOM_TUNE_LENGTH; ++i) {
        tune[i] = random(0, 4);
    }
}

#define RAINBOW_CYCLE_END                                     (256 * 5)

void DemoMode::rainbowCycle() {
    uint16_t i, j;

    for (uint8_t i = 0; i < NUMBER_OF_PIXELS; ++i) {
        strip->setPixelColor(i, wheel(((i * 256 / NUMBER_OF_PIXELS) + position) & 255));
    }
    strip->show();
    delayAndCheck(50);

    position++;
    if (position >= RAINBOW_CYCLE_END) {
        position = 0;
    }
}

void DemoMode::tick() {
    if (delayUntil > 0) {
        if (millis() >= delayUntil) {
            delayUntil = 0;
        }
        return;
    }

    if (millis() - startedAt > 1000 * 60 * 5) {
        generateRandomTune();
        transitionAt = millis();
        state = DemoState::RANDOM_TUNE;
        position = 0;
        startedAt = millis();
    }

    switch (state) {
    case DemoState::FLASH: {
        if (millis() - transitionAt > 5 * 1000) {
            transitionAt = millis();
            state = DemoState::CHASE_FORWARD;
            position = 0;
            direction = 1;
        }
        flash();
        break;
    }
    case DemoState::CHASE_FORWARD: {
        if (millis() - transitionAt > 5 * 1000) {
            transitionAt = millis();
            state = DemoState::CHASE_BACKWARD;
            position = 0;
            direction = -1;
        }
        chase();
        break;
    }
    case DemoState::CHASE_BACKWARD: {
        if (millis() - transitionAt > 5 * 1000) {
            transitionAt = millis();
            state = DemoState::RAINBOW;
            position = random(0, RAINBOW_CYCLE_END);
        }
        chase();
        break;
    }
    case DemoState::RAINBOW: {
        if (millis() - transitionAt > 5 * 1000) {
            transitionAt = millis();
            state = DemoState::THEATER_CHASE;
            position = 0;
        }
        rainbowCycle();
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
    case DemoState::RANDOM_TUNE: {
        if (position == RANDOM_TUNE_LENGTH) {
            transitionAt = millis();
            state = DemoState::FLASH;
            position = 0;
        }
        else {
            buttons->play(tune[position]);
            delayAndCheck(500);
            position++;
        }
        break;
    }
    }
}
