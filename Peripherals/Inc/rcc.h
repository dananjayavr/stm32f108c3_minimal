/*
 * rcc.h
 *
 *  Created on: Mar 6, 2021
 *      Author: danan
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "main.h"

/**
 * @brief HSE Configuration
 */
void rcc_HSE_config(void);

/**
 * @brief SysTick Configuration
 */
void rcc_SysTick_config(uint32_t reloadValue);

/**
 * @brief Increment ms Tick
 */
void rcc_msIncTicks(void);

/**
 * @brief Get ms Ticks
 */
uint32_t rcc_msGetTicks(void);

/**
 * @brief ms Tick delay
 */
void rcc_msDelay(uint32_t delay);

#endif /* INC_RCC_H_ */
