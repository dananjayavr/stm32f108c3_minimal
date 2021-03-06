/*
 * gpio.h
 *
 *  Created on: 6 mars 2021
 *      Author: Dananjaya Ramanayake
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "main.h"

/**
 * @brief LED GPIO Configuration (PB13 -> Green / PB14 -> Red)
 */
void gpio_LED_config(void);

/**
 * @brief Write/Toggle LEDs
 */
void gpio_LED_writeGreen(bool state);
void gpio_LED_writeRed(bool state);
void gpio_LED_ToggleGreen(void);
void gpio_LED_ToggleRed(void);

#endif /* INC_GPIO_H_ */
