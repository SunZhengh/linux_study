#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#include "imx6ul.h"

#define KEY_DOWN 0
#define KEY_UP 1

void delay_us(unsigned int us);
void delay_ms(unsigned int ms);
void delay_init(void);
void delay(volatile unsigned int ms);
void gpt1_handler(unsigned int gicciar, void* param);

#endif // !__BSP_DELAY_H