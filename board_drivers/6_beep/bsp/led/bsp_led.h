#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define LED_ON      1
#define LED_OFF     0
#define LED0        0

void led_init(char led);
void led_control(char led, char commond);

#endif // !__BSP_LED_H#define __BSP_LED_H

