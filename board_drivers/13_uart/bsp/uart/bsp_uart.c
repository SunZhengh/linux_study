#include "bsp_uart.h"

/*
* uart gpio init
*/
void bsp_uart_io_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);
}

/*
* enable uart
*/
void bsp_uart_enable(UART_Type *uart_base)
{
    uart_base->UCR1 |= (1 << 0);
}

/*
* disable uart
*/
void bsp_uart_disable(UART_Type *uart_base)
{
    uart_base->UCR1 &= ~(1 << 0);
}

/*
* uart reset
*/
void bsp_uart_reset(UART_Type *uart_base)
{
    uart_base->UCR2 &= ~(1 << 0);
    while((uart_base->UCR2 & 0x1) == 0)
    {
        ;
    }
}

/*
* uart init
*/
void bsp_uart_init(void)
{
    bsp_uart_io_init();
    bsp_uart_disable(UART1);
    bsp_uart_reset(UART1);

    CCM->CSCDR1 &= ~(1 << 6) ;
    CCM->CSCDR1 &= ~(0x3F << 0);

    UART1->UCR1 = 0;
    UART1->UCR2 = 0;
    UART1->UCR2 |= (1 << 1) | (1 << 2) | (1 << 5) | (1 << 14);
    UART1->UCR3 |= (1 << 2);

    //baudrate config
    UART1->UFCR &= ~(7 << 7);
    UART1->UFCR &= (5 << 7);
    UART1->UBMR = 3124;
    UART1->UBIR = 71;

    bsp_uart_enable(UART1);
}

/*
* uart1 send byte
*/
int putc(uint8_t c)
{
    while(((UART1->USR2)&(0x1 << 3)) == 0)
    {
        ;
    }
    UART1->UTXD = 0;
    UART1->UTXD = c;
    return 0;
}

/*
* uart1 recv byte
* return: recv data(byte)
*/
uint8_t getc(void)
{
    while(((UART1->USR2)&(0x1)) == 0)
    {
        ;
    }

    return UART1->URXD &(0xff);
}

/*
* uart send string
* @buf:  tring to send
* return: send length
*/
uint32_t puts(uint8_t *buf)
{
    uint8_t *p = buf;
    uint32_t len = 0;
    while(*p != '\0')
    {
        putc(*p);
        p++;
        len++;
    }
    return len;
}
