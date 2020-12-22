#include "bsp_uart.h"

void bsp_uart_init(void)
{
    CCM->CSCDR1 &= ~(1 << 6) ;
    CCM->CSCDR1 &= ~(0x3F << 0);

}

int bsp_uart_send(char* buf, int len)
{


}
