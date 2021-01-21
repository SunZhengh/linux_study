#include "bsp_spi.h"

void spi_init(ECSPI_Type *base)
{
    base->CONREG = 0;
    base->CONREG |= (1 << 0)|(1 << 3)|(1 << 4)|(7<<20);
    base->CONFIGREG = 0;
    base->PERIODREG = 0x2000;
    base->CONREG &= ~((0xF << 12)|(0xF << 8));
    base->CONREG |= (9 << 12);
}

//spi发送/接收函数
unsigned char spich0_readwrite_byte(ECSPI_Type *base, unsigned char txdata)
{
    uint32_t spitxdata = txdata;
    uint32_t spirxdata = 0;

    base->CONREG &= ~(3 << 18);

    while((base->STATREG & (1 << 0)) == 0);
    base->TXDATA = spitxdata;

    while((base->STATREG & (1 << 3)) == 0);
    spirxdata = base->RXDATA;

    return spirxdata;
}