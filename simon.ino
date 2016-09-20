#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "Speaker.h"
#include "Buttons.h"
#include "Game.h"

#define PIN_BUTTON_LEDS                       A5

Speaker speaker;
Adafruit_NeoPixel pixels(1, PIN_BUTTON_LEDS, NEO_GRB + NEO_KHZ800);
Buttons buttons(&speaker, &pixels);
Game game(&speaker, &buttons);

void setup() {
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    Serial.begin(115200);

    speaker.setup();
    pixels.begin();
    buttons.setup();

    if (false) {
        game.startOver();
    }
    else {
        game.welcome();
    }

    while (true) {
        speaker.tick();
        game.tick();
        delay(10);
    }
}

void loop() {

}
