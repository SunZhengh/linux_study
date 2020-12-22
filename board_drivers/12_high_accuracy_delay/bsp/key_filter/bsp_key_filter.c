#include "bsp_key_filter.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_led.h"
/*按键滤波初始化*/
void key_filter_init(void)
{
    gpio_pin_config_t key_exit;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    key_exit.direction = kGPIO_DigitalInput;
    key_exit.InterruptMode = kGPIO_IntFallingEdge;
    gpio_init(GPIO1, 18, &key_exit);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, gpio1_io18_exit_filter_handler, NULL);
    gpio_interrupt_enable(GPIO1, 18);
    key_filter_time_init(66000000/100);
}
/*按键滤波定时器初始化*/
void key_filter_time_init(unsigned int value)
{

    EPIT1->CR = 0;

    EPIT1->CR = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 24);

    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn, EPIT_filter_handler, NULL);

}
/*关闭定时器*/
void  epti_timer_close(void)
{
    EPIT1->CR &= ~(1 << 0);
}
/*重启定时器*/
void  epti_timer_restart(unsigned int value)
{
    EPIT1->CR &= ~(1 << 0);
    EPIT1->LR = value;
    EPIT1->CR |= (1 << 0);
}
/*定时器消抖中断处理函数*/
void EPIT_filter_handler(unsigned int gicciar, void* param)
{
   static unsigned char state = LED_OFF;
   if(EPIT1->SR & (1 << 0))
    {
        epti_timer_close();
        if(gpio_pinread(GPIO1, 18) == 0)
        {
            state = !state;
            led_control(state);
        }
    }
    EPIT1->SR |= (1 << 0);
}

/*按键消抖中断处理函数*/
void gpio1_io18_exit_filter_handler(unsigned int gicciar, void* param)
{
    epti_timer_restart(66000000/100);
    gpio_interrupt_flag_clear(GPIO1, 18);
}
