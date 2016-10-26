#include <Arduino.h>

#include "vibrations.h"

void setup() {
    Serial.begin(115200);

    while (!Serial) {
    }

    vibration_sensors_setup(vibrationSensors);

    Serial.println("Ready..");
}

uint32_t timer = 0;

void loop() {
    while (true) {
        int8_t pressed = vibration_sensors_detect_press(vibrationSensors);
        if (pressed != -1) {
            Serial.print(millis());
            Serial.print(" ");
            Serial.print(pressed);
            Serial.println();
        }

        if (millis() - timer > 1000) {
            Serial.println(".");
            timer = millis();
        }

        delay(10);
    }
}
