#include "bsp_backlight.h"

PWM_PARAM backlight_pwm_duty;

static void pwm1_period_set(unsigned int value)
{
    unsigned int regvalue = 0;
    if(value < 2){
        regvalue = 2;
    }
    else{
        regvalue = value - 2;
    }
    PWM1->PWMPR = (regvalue & 0xFFFF);
}

void pwm1_duty_set(unsigned char duty)
{
    unsigned short period;
    unsigned short sample;
    period = PWM1->PWMPR + 2;
    sample = period * duty / 100;
    PWM1->PWMSAR = (sample & 0xFFFF);
}

void pwm1_handler(unsigned int gicciar, void* param)
{
    if(PWM1->PWMSR & (1 << 3)){
        pwm1_duty_set(backlight_pwm_duty.pwmduty);
        PWM1->PWMSR |= 1 << 3;
    }
}

void backlight_init(void)
{
    unsigned char i = 0;
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_PWM1_OUT, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_PWM1_OUT, 0xB090);

    PWM1->PWMCR = 0;
    PWM1->PWMCR |= (1 << 26)|(1 << 16)|(65 << 4);

    pwm1_period_set(1000);
    backlight_pwm_duty.pwmduty = 50;
    for(i=0;i<4;i++){
        pwm1_duty_set(backlight_pwm_duty.pwmduty);
    }

    PWM1->PWMIR = 1 << 0;
    GIC_EnableIRQ(PWM1_IRQn);
    system_register_irqhandler(PWM1_IRQn, (system_irq_handler_t)pwm1_handler, NULL);
    PWM1->PWMSR = 0xFF;

    PWM1->PWMCR |= 1;
}