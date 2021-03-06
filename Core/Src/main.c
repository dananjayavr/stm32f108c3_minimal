#include "main.h"
#include <stdio.h>
#include "gpio.h"

int main(void)
{
  // Max clock of 72 MHz
  rcc_HSE_config();
  rcc_SysTick_config(72000);

  // UART Configuration
  uart_UART1_config();
  uart_UART1_GPIO_config();

  // LEDs configuration
  gpio_LED_config();
  gpio_LED_ToggleRed();
  printf("Program is starting...\r\n");

  while(1)
  {
    gpio_LED_ToggleRed();
    gpio_LED_ToggleGreen();
    printf("Hello, World!\r\n");
    rcc_msDelay(500);
  }
}
