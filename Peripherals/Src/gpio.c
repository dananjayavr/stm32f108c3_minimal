/*
 * gpio.c
 *
 *  Created on: 6 mars 2021
 *      Author: Dananjaya Ramanayake
 */


#include "gpio.h"

/**
 * @brief LED GPIO Configuration (PB13 -> Green / PB14 -> Red)
 */
void gpio_LED_config(void)
{
  // Enable port B clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  // Set the mode to output and push-pull
  //CLEAR_BIT(GPIOB->CRH, (3UL << 20));
  // Mode to output
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_MODE13);
  SET_BIT(GPIOB->CRH, GPIO_CRH_MODE13_1);
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_MODE14);
  SET_BIT(GPIOB->CRH, GPIO_CRH_MODE14_1);
  // Mode to output Push-Pull
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_CNF13);
  CLEAR_BIT(GPIOB->CRH, GPIO_CRH_CNF14);
}

/**
 * @brief Write/Toggle LEDs
 */
void gpio_LED_writeGreen(bool state)
{
  if(state)
  {
    GPIOB->ODR |= (GPIO_ODR_ODR13);
  }
  else
  {
    GPIOB->ODR &= ~(GPIO_ODR_ODR13);
  }
}

void gpio_LED_writeRed(bool state)
{
  if(state)
  {
    GPIOB->ODR |= (GPIO_ODR_ODR14);
  }
  else
  {
    GPIOB->ODR &= ~(GPIO_ODR_ODR14);
  }
}

void gpio_LED_ToggleGreen(void)
{
  GPIOB->ODR ^= GPIO_ODR_ODR13;
}

void gpio_LED_ToggleRed(void)
{
  GPIOB->ODR ^= GPIO_ODR_ODR14;
}
