#include "bsp_gpio.h"


/* GPIO初始化 */
void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config)
{
    if(config->direction == kGPIO_DigitalInput) /* 输入 */
    {
        base->GDIR &= ~(1 << pin);
    }
    else
    {
        base->GDIR |= (1 << pin);
        /* 设置默认输出电平 */
        gpio_pinwrite(base, pin, config->outputLogic);
    }
    gpio_interrupt_config(base, pin, config->InterruptMode);
}

/* 控制GPIO高低电平 */
void gpio_pinwrite(GPIO_Type *base, int pin, int value)
{
    if(value == 0)      /* 写入0 */
    {
        base->DR &= ~(1 << pin);
    }
    else                /* 写1 */
    {
        base->DR |= (1 << pin);
    }
    
}

/* 读取指定IO电平 */
int gpio_pinread(GPIO_Type *base, int pin)
{
    return (((base->DR) >> pin) & 0x1);
}
/*使能gpio中断*/
void gpio_interrupt_enable(GPIO_Type *base, unsigned int pin)
{
    base->IMR |= (1 << pin);
}
/*禁用gpio中断*/
void gpio_interrupt_disable(GPIO_Type *base, unsigned int pin)
{
    base->IMR &= ~(1 << pin);
}
/*清除中断标志位*/
void gpio_interrupt_flag_clear(GPIO_Type *base, unsigned int pin)
{
    base->ISR |= (1 << pin);
}

/*配置中断初始化*/
void gpio_interrupt_config(GPIO_Type *base, unsigned int pin, gpio_interrupt_mode_t mode)
{
    volatile uint32_t *icr;
    uint32_t icrShift = pin;
    base->EDGE_SEL &= ~(1 << pin);
    if(pin < 16)
    {
        icr = &(base->ICR1);
    }
    else
    {
        icr = &(base->ICR2);
        icrShift -= pin;
    }
    switch(mode)
    {
        case kGPIO_IntLowLevel:
            *icr |= ~(3 << (2*icrShift));
            break;
        case kGPIO_IntHighLevel:
            *icr |= ~(3 << (2*icrShift));
            *icr |= (1 << (2*icrShift));
            break;
        case kGPIO_IntRisingEdge:
            *icr |= ~(3 << (2*icrShift));
            *icr |= (2 << (2*icrShift));
            break;
        case kGPIO_IntFallingEdge:
            *icr |= ~(3 << (2*icrShift));
            *icr |= (3 << (2*icrShift));
            break;
        default:
            break;
    }
}
