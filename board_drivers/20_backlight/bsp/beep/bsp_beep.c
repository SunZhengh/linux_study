#include "bsp_beep.h"

void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10B0);
    GPIO5->DR |= (1<<1);
    GPIO5->GDIR |= (1<<1);
    printf("beep_init done.\r\n");
}

void beep_control(char command)
{
    switch(command)
    {
        case BEEP_OFF:
            GPIO5->DR |= (1<<1);
            break;
        case BEEP_ON:
            GPIO5->DR &= ~(1<<1);
            break;
    }
}