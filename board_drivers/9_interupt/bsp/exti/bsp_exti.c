#include "bsp_exti.h"
#include "../bsp/gpio/bsp_gpio.h"
#include "../bsp/interrupt/bsp_int.h"
#include "../bsp/led/bsp_led.h"
#include "../bsp/delay/bsp_delay.h"

void gpio1_io18_exit_handler(unsigned int gicciar, void* param);

/*按键中断初始化*/
void exti_init(void)
{
    gpio_pin_config_t key_exit;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    key_exit.direction = kGPIO_DigitalInput;
    key_exit.InterruptMode = kGPIO_IntFallingEdge;
    gpio_init(GPIO1, 18, &key_exit);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, gpio1_io18_exit_handler, NULL);
    gpio_interrupt_enable(GPIO1, 18);
}

/*按键中断LED亮处理函数*/
void gpio1_io18_exit_handler(unsigned int gicciar, void* param)
{
    static unsigned char state = 0;
    state = !state;
    led_control(state);
    gpio_interrupt_flag_clear(GPIO1, 18);
}
