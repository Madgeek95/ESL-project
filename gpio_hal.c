#include "gpio_hal.h"
#include "nrf_gpio.h"

void gpio_hal_init(void)
{
    // Настройка кнопки как вход с подтяжкой
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);

    // Настройка пинов RGB светодиода на выход
    nrf_gpio_cfg_output(LED2_RED_PIN);
    nrf_gpio_cfg_output(LED2_GREEN_PIN);
    nrf_gpio_cfg_output(LED2_BLUE_PIN);

    // Выключение всех светодиодов (Active-Low: 1 = ВЫКЛ)
    nrf_gpio_pin_write(LED2_RED_PIN, 1);
    nrf_gpio_pin_write(LED2_GREEN_PIN, 1);
    nrf_gpio_pin_write(LED2_BLUE_PIN, 1);
}

void gpio_hal_set_led(led_color_t color)
{
    // Гасим все светодиоды перед включением нужного
    nrf_gpio_pin_write(LED2_RED_PIN, 1);
    nrf_gpio_pin_write(LED2_GREEN_PIN, 1);
    nrf_gpio_pin_write(LED2_BLUE_PIN, 1);

    // Включаем заданный цвет (Active-Low: 0 = ВКЛ)
    switch (color)
    {
        case COLOR_RED:
            nrf_gpio_pin_write(LED2_RED_PIN, 0);
            break;
        case COLOR_GREEN:
            nrf_gpio_pin_write(LED2_GREEN_PIN, 0);
            break;
        case COLOR_BLUE:
            nrf_gpio_pin_write(LED2_BLUE_PIN, 0);
            break;
        case COLOR_OFF:
        default:
            break;
    }
}

bool gpio_hal_is_button_pressed(void)
{
    // Активный уровень — 0 (LOW)
    return (nrf_gpio_pin_read(BUTTON_PIN) == 0);
}