#include "bsp_delay.h"

static void delay_short(volatile unsigned int n)
{
    while(n--) {}
}

/* 延时，一次循环大概是1ms，在主频396MHz
 * n ：延时ms数
  */
void delay(volatile unsigned int ms)
{
    while(ms--) {
        delay_short(0x7ff);
    }
}
