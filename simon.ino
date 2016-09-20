#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "Speaker.h"
#include "Buttons.h"

#define PIN_BUTTON_LEDS                       A5

Speaker speaker;
Adafruit_NeoPixel pixels(1, PIN_BUTTON_LEDS, NEO_GRB + NEO_KHZ800);
Buttons buttons(&speaker, &pixels);

void setup() {
    Serial.begin(115200);

    speaker.setup();
    pixels.begin();
    buttons.setup();

    while (true) {
        buttons.tick();
        speaker.tick();
        delay(10);
    }
}

void loop() {

}
