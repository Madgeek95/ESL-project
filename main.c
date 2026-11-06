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

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"

// Прямое определение пинов для nRF52840 Dongle (PCA10059) без сторонних заголовочных файлов
// Порт 0: пины 0-31. Порт 1: пины 32-63 (32 + номер пина)
#define BUTTON_1       38   // Port 1, Pin 6 (32 + 6)
#define LED2_R         8    // Port 0, Pin 8
#define LED2_G         41   // Port 1, Pin 9 (32 + 9)
#define LED2_B         12   // Port 0, Pin 12

int main(void)
{
    // 1. Настраиваем кнопку как вход с подтяжкой к питанию
    nrf_gpio_cfg_input(BUTTON_1, NRF_GPIO_PIN_PULLUP);

    // 2. Настраиваем пины светодиодов как выходы
    nrf_gpio_cfg_output(LED2_R);
    nrf_gpio_cfg_output(LED2_G);
    nrf_gpio_cfg_output(LED2_B);

    // Выключаем все светодиоды на старте (1 = выкл)
    nrf_gpio_pin_write(LED2_R, 1);
    nrf_gpio_pin_write(LED2_G, 1);
    nrf_gpio_pin_write(LED2_B, 1);

    int step = 0;

    while (true) 
    {
        // Проверяем, нажата ли кнопка (активный уровень 0)
        bool button_pressed = (nrf_gpio_pin_read(BUTTON_1) == 0);

        if (button_pressed)
        {
            if (step == 0) {
                nrf_gpio_pin_write(LED2_R, 0);   
                nrf_delay_ms(300);
                nrf_gpio_pin_write(LED2_R, 1);   
            } 
            else if (step == 1) {
                nrf_gpio_pin_write(LED2_G, 0); 
                nrf_delay_ms(300);
                nrf_gpio_pin_write(LED2_G, 1); 
            } 
            else if (step == 2) {
                nrf_gpio_pin_write(LED2_B, 0);  
                nrf_delay_ms(300);
                nrf_gpio_pin_write(LED2_B, 1);  
            }

            nrf_delay_ms(200); 

            step = (step + 1) % 3;
        }
        else 
        {
            nrf_delay_ms(50);
        }
    }
}

/**
 *@}
 **/
