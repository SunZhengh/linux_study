#ifndef __BSP_BACKLIGHT_H
#define __BSP_BACKLIGHT_H

#include "imx6ul.h"
#include "../bsp/interrupt/bsp_int.h"
#include "../bsp/gpio/bsp_gpio.h"

typedef struct{
    unsigned char pwmduty;
}PWM_PARAM;

extern PWM_PARAM backlight_pwm_duty;

void backlight_init(void);
void pwm1_duty_set(unsigned char duty);

#endif // !__BSP_BACKLIGHT_H
