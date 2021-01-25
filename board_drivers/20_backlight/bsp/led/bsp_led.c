#include "bsp_led.h"

void led_init(void)
{
    int led = LED0;
    switch(led)
    {
        case LED0:
        {
            IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
            IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);
            GPIO1->GDIR = 0x8;
            GPIO1->DR = 0x0;
            
            break;
        }
    }
    printf("led_init done.\r\n");
}

void led_control(char commond)
{
    int led = LED0;
    switch(led)
    {
        case LED0:
        {
            if(commond == LED_ON)
            {
                GPIO1->DR &= ~(1<<3);
            }
            if(commond == LED_OFF)
            {
                GPIO1->DR |= (1<<3);
            }
            break;
        }
    }
    
}

