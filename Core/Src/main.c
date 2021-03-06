#include "main.h"
#include <stdio.h>

int main(void)
{
  // Max clock of 72 MHz
  rcc_HSE_config();
  rcc_SysTick_config(72000);

  // UART Configuration
  uart_UART1_config();
  uart_UART1_GPIO_config();

  printf("Program is starting...\r\n");

  while(1)
  {
    printf("Hello, World!\r\n");
    rcc_msDelay(1000);
  }
}
