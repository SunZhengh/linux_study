#include "bsp_uart.h"

/*
* uart gpio init
*/
static void bsp_uart_io_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);
}

/*
* enable uart
*/
static void bsp_uart_enable(UART_Type *uart_base)
{
    uart_base->UCR1 |= (1 << 0);
}

/*
* disable uart
*/
static void bsp_uart_disable(UART_Type *uart_base)
{
    uart_base->UCR1 &= ~(1 << 0);
}

/*
* uart reset
*/
static void bsp_uart_reset(UART_Type *uart_base)
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
void uart_init(void)
{
    bsp_uart_io_init();
 
    bsp_uart_disable(UART1);
    bsp_uart_reset(UART1);


    UART1->UCR1 = 0;
    UART1->UCR1 &= ~(1 << 14);
    UART1->UCR2 |= (1 << 14) | (1 << 5) | (1 << 2) | (1 << 1);
    UART1->UCR3 |= (1 << 2);

    //baudrate config
    UART1->UFCR = (5 << 7);
    UART1->UBIR = 71;
    UART1->UBMR = 3124;

    bsp_uart_enable(UART1);
}

/*
* uart1 send byte
*/
void putc(unsigned char c)
{
    while(((UART1->USR2 >> 3 ) & 0X01) == 0);
    UART1->UTXD = c & 0xFF;
}

/*
* uart1 recv byte
* return: recv data(byte)
*/
unsigned char getc(void)
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
void puts(char *buf)
{
    char *p = buf;
    while(*p)
    {
        putc(*p++);
    }
        
}

void raise(int sig_nr)
{
    
}