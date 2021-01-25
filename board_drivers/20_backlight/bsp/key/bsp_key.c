#include "bsp_key.h"
#include "bsp_delay.h"

static uint8_t key_value;

void key_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);
    GPIO1->GDIR &= ~(1<<18);
    printf("key_init done.\r\n");
}

uint8_t read_key(void)
{
    uint8_t ret = 0;
    ret = ((GPIO1->DR) >> 18) & 0X1;
    return ret;
}

uint8_t key_getvalue(void)
{
    uint8_t last_value = 0;
    uint8_t count = 4;
    uint8_t true_flag = 1;
    last_value = read_key();
    while(count--)
    {
        if(true_flag){
            if(last_value == read_key()){
                delay(2);
            }
            else{
                true_flag = 0;
                break;
            } 
        }  
    }
    if(true_flag){
        key_value = last_value;
    }
    return key_value;
}
