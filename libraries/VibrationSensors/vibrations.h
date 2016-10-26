#ifndef VIBRATIONS_H_INCLUDED
#define VIBRATIONS_H_INCLUDED

typedef struct vibration_sensor_t {
    uint8_t which;
    int32_t vibrations;
    uint32_t first;
    uint32_t last;
    uint8_t pin;
    void (*irq_handler)(void);
} vibration_sensor_t;

extern vibration_sensor_t vibrationSensors[];

void vibration_sensors_setup(vibration_sensor_t *sensors);

vibration_sensor_t *vibration_sensors_detect_press(vibration_sensor_t *sensors);

#endif
