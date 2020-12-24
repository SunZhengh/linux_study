#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "imx6ul.h"
#include "bsp_gpio.h"

void bsp_uart_init(void);
uint32_t puts(uint8_t *buf);

#endif // !__BSP_UART_H
