/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */
#include "gpio_hal.h"
#include "nrf_delay.h"

// Заданная последовательность: RRGGGB
static const led_color_t sequence[] = {
    COLOR_RED,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_GREEN,
    COLOR_GREEN,
    COLOR_BLUE
};

#define SEQUENCE_LENGTH (sizeof(sequence) / sizeof(sequence[0]))

int main(void)
{
    gpio_hal_init();

    static size_t current_index = 0;
    static led_color_t active_color = COLOR_RED;

    gpio_hal_set_led(active_color);

    while (true)
    {
        if (gpio_hal_is_button_pressed())
        {
            // Берем следующий шаг последовательности
            active_color = sequence[current_index];
            gpio_hal_set_led(active_color);

            // Длительность отображения шага
            nrf_delay_ms(300);

            // Переход к следующему элементу
            current_index = (current_index + 1) % SEQUENCE_LENGTH;

            nrf_delay_ms(100);
        }
        else
        {
            // Кнопка отпущена — светодиод продолжает гореть последним цветом (пауза)
            gpio_hal_set_led(active_color);
            nrf_delay_ms(20);
        }
    }
}

/**
 *@}
 **/
