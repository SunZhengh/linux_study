#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "imx6ul.h"
#include "bsp_gpio.h"

void uart_init(void);
void puts(char *buf);
void putc(unsigned char c);
unsigned char getc(void);
void raise(int sig_nr);

#endif // !__BSP_UART_H
