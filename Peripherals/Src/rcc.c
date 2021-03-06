/*
 * rcc.c
 *
 *  Created on: Mar 6, 2021
 *      Author: danan
 */

#include "rcc.h"

// ms_Tick
static volatile uint32_t msTicks = 0;

void rcc_HSE_config(void)
{
  /*
   * Configuration parameters --> STM32F103 Clock Tree (from CubeMX)
   *
   * HSE = 8 MHz
   * PLL  = x9
   * USB prescaler = 1.5
   * AHB Prescaler = 1
   * Cortex Prescaler = 1 (ex. SysTick)
   * ---> 72 MHz System Clock
   *
   * APB1 Prescaler = 2 (36, 72 MHz)
   * APB2 Prescaler = 1 (72, 72 MHz)
   * ADC Prescaler = 6 (12 MHz, Refer to Reference Manual for the figure)
   */

  // PLL Configuration
  // PLL = x9
  // Clear register fields (21:18)
  //RCC->CFGR &= ~(0xFUL << 18);
  RCC->CFGR &= ~(RCC_CFGR_PLLMULL); // Same as above, except using a CMSIS define
  // Setting the PLL multiplier to 9, by writing 0111 (7UL) in the register
  RCC->CFGR |= (7UL << 18);
  //RCC->CFGR |= (RCC_CFGR_PLLMULL9); // Same as above, except using a CMSIS define
  //RCC->CFGR |= (0x7UL << RCC_CFGR_PLLMULL_Pos);

  // USB Prescaler = 1.5
  RCC->CFGR &= ~(RCC_CFGR_USBPRE);
  //RCC->CFGR &= ~(0x1UL << 22);

  // HSE Oscillator
  // Enable HSE Oscillator
  RCC->CR |= RCC_CR_HSEON;
  // Waiting for it to stabilize
  while((RCC->CR & RCC_CR_HSERDY) == 0);
  // Select HSE as PLL source
  RCC->CFGR |= RCC_CFGR_PLLSRC;
  // Enable PLL
  RCC->CR |= RCC_CR_PLLON;
  // Waiting for it to stabilize
  while((RCC->CR & RCC_CR_PLLRDY) == 0);

  // Flash prefetch and wait-state
  // 2WS = 72 MHz

  // Clearing the latency bits
  FLASH->ACR &= ~(FLASH_ACR_LATENCY);
  // Setting the latency to 2 wait state (0-indexed)
  FLASH->ACR |= FLASH_ACR_LATENCY_1;
  // Setting up the prefetch buffer
  FLASH->ACR |= FLASH_ACR_PRFTBE;

  // Setting the PLL as the System Clock at the Multiplexer
  // Clear the bitfields
  RCC->CFGR &= ~(RCC_CFGR_SW);
  // Selecting the source
  RCC->CFGR |= RCC_CFGR_SW_1;
  // Waiting until PLL to be active clock source
  while((RCC->CFGR & RCC_CFGR_SWS_1) == 0);

  // Setting up peripheral clocks
  // AHB prescaler
  RCC->CFGR &= ~(RCC_CFGR_HPRE);
  // APB1 prescaler = 2
  RCC->CFGR &= ~(RCC_CFGR_PPRE1);
  RCC->CFGR |= RCC_CFGR_PPRE1_2;
  // APB2 prescaler = 1
  RCC->CFGR &= ~(RCC_CFGR_PPRE2);
  // ADC prescaler = 6
  RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
  RCC->CFGR |= RCC_CFGR_ADCPRE_1;

}

void rcc_SysTick_config(uint32_t reloadValue)
{
  // Reset control register
  SysTick->CTRL = 0;
  // Set the RELOAD value
  SysTick->LOAD = reloadValue - 1;
  // Priority SysTick interrupt (NVIC)
  NVIC_SetPriority(SysTick_IRQn,0);
  // Reset SysTick value to 0
  SysTick->VAL = 0;
  // Enable SysTick from Control register
  SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void rcc_msIncTicks(void)
{
  msTicks++;
}

uint32_t rcc_msGetTicks(void)
{
  return msTicks;
}

void rcc_msDelay(uint32_t delay)
{
  uint32_t startTicks = rcc_msGetTicks();
  while(rcc_msGetTicks() - startTicks < delay);
}

void SysTick_Handler()
{
  NVIC_ClearPendingIRQ(SysTick_IRQn);
  rcc_msIncTicks();
}
