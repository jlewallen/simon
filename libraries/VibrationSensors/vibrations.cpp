#include <Arduino.h>
#include "vibrations.h"

#define VIBRATION_SENSORS_NUMBER                              4
#define VIBRATION_SENSORS_HYSTERESIS                          250

void vibration_sensors_irq(vibration_sensor_t *sensor) {
    if (sensor->first == 0) {
        sensor->first = millis();
    }
    sensor->vibrations++;
    sensor->last = millis();
}

bool vibration_sensors_any_detected(vibration_sensor_t *sensors) {
    for (uint8_t i = 0; i < VIBRATION_SENSORS_NUMBER; ++i) {
        vibration_sensor_t *sensor = &sensors[i];

        if (sensor->first > 0 && millis() - sensor->last > VIBRATION_SENSORS_HYSTERESIS) {
            return true;
        }
    }

    return false;
}

bool vibration_sensors_bad_vibration(vibration_sensor_t *sensors, vibration_sensor_t *pressed) {
    bool tooClose = false;
    bool allLessThan10 = true;

    for (uint8_t i = 0; i < VIBRATION_SENSORS_NUMBER; ++i) {
        vibration_sensor_t *sensor = &sensors[i];

        if (sensors[i].vibrations >= 10) {
            allLessThan10 = false;
        }

        if (sensor != pressed) {
            int32_t difference = sensors[i].vibrations - pressed->vibrations;
            if (difference == 0) {
                tooClose = true;
            }
        }
    }

    if (allLessThan10 || tooClose) {
        Serial.print("BAD:");
        if (allLessThan10) Serial.print(" <10");
        if (tooClose) Serial.print(" Close");
        Serial.println();
    }

    return allLessThan10 || tooClose;
}

void vibration_sensors_dump(vibration_sensor_t *sensors) {
    for (uint8_t i = 0; i < VIBRATION_SENSORS_NUMBER; ++i) {
        vibration_sensor_t *sensor = &sensors[i];
        Serial.print(sensor->which);
        Serial.print(": ");
        Serial.print(sensor->first);
        Serial.print(" ");
        Serial.print(sensor->last);
        Serial.print(" ");
        Serial.print(sensor->vibrations);
        Serial.println();
    }
}

void vibration_sensors_clear(vibration_sensor_t *sensors) {
    for (uint8_t i = 0; i < VIBRATION_SENSORS_NUMBER; ++i) {
        vibration_sensor_t *sensor = &sensors[i];
        sensor->vibrations = 0;
        sensor->first = 0;
        sensor->last = 0;
    }
}

void vibration_sensors_setup(vibration_sensor_t *sensors) {
    for (uint8_t i = 0; i < VIBRATION_SENSORS_NUMBER; ++i) {
        vibration_sensor_t *sensor = &sensors[i];

        pinMode(sensor->pin, INPUT);
        attachInterrupt(digitalPinToInterrupt(sensor->pin), sensor->irq_handler, RISING);
    }
}

vibration_sensor_t *vibration_sensors_detect_press(vibration_sensor_t *sensors) {
    vibration_sensor_t *pressed = nullptr;
    uint32_t maximumVibrations = 0;

    if (!vibration_sensors_any_detected(sensors)) {
        return nullptr;
    }

    vibration_sensors_dump(sensors);

    for (uint8_t i = 0; i < VIBRATION_SENSORS_NUMBER; ++i) {
        vibration_sensor_t *sensor = &sensors[i];

        if (sensor->first > 0) {
            if (sensor->vibrations > maximumVibrations) {
                maximumVibrations = sensor->vibrations;
                pressed = sensor;
            }
        }
    }

    if (vibration_sensors_bad_vibration(sensors, pressed)) {
        vibration_sensors_clear(sensors);
        return nullptr;
    }

    vibration_sensors_clear(sensors);

    return pressed;
}

static void irq_button0(void);
static void irq_button1(void);
static void irq_button2(void);
static void irq_button3(void);

vibration_sensor_t vibrationSensors[VIBRATION_SENSORS_NUMBER] = {
    { 0, 0, 0, 0, A1, irq_button0 },
    { 1, 0, 0, 0, A2, irq_button1 },
    { 2, 0, 0, 0, A3, irq_button2 },
    { 3, 0, 0, 0, A4, irq_button3 }
};

static void irq_button0(void) {
    vibration_sensors_irq(&vibrationSensors[0]);
}

static void irq_button1(void) {
    vibration_sensors_irq(&vibrationSensors[1]);
}

static void irq_button2(void) {
    vibration_sensors_irq(&vibrationSensors[2]);
}

static void irq_button3(void) {
    vibration_sensors_irq(&vibrationSensors[3]);
}
