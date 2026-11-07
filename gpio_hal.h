#ifndef GPIO_HAL_H
#define GPIO_HAL_H

#include <stdbool.h>
#include <stdint.h>

// Номера пинов для nRF52840 Dongle (PCA10059)
#define BUTTON_PIN      38   // Port 1, Pin 6 (32 + 6)
#define LED2_RED_PIN    8    // Port 0, Pin 8
#define LED2_GREEN_PIN  41   // Port 1, Pin 9 (32 + 9)
#define LED2_BLUE_PIN   12   // Port 0, Pin 12

typedef enum {
    COLOR_OFF = 0,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
} led_color_t;

void gpio_hal_init(void);
void gpio_hal_set_led(led_color_t color);
bool gpio_hal_is_button_pressed(void);

#endif // GPIO_HAL_H