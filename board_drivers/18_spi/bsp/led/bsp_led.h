#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "imx6ul.h"

#define LED_ON      1
#define LED_OFF     0
#define LED0        0

void led_init(void);
void led_control(char commond);

#endif // !__BSP_LED_H#define __BSP_LED_H

