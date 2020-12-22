#include "bsp_epit.h"
#include "bsp_int.h"
#include "bsp_led.h"
#include "bsp_delay.h"

/*初始化EPIT，frac分频值，value加载值*/
void epit_init(unsigned int frac, unsigned int value)
{
    if(frac > 4095)
        frac = 4095;
    EPIT1->CR = 0;

    EPIT1->CR = (1 << 1) | (1 << 2) | (1 << 3) | (frac << 4) | (1 << 24);

    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn, (system_irq_handler_t)EPIT_handler, NULL);
    EPIT1->CR |= 1 << 0;
    led_control(1);
    delay(1000);
    led_control(0);
    delay(1000);
    led_control(1);
    delay(1000);
    led_control(0);
}

/*EPIT中断处理函数*/
void EPIT_handler(unsigned int gicciar, void* param)
{
    static unsigned char state = 0;
    state = !state;
    led_control(state);

    EPIT1->SR |= (1 << 0);
}
