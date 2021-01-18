#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_int.h"

static void delay_short(volatile unsigned int n)
{
    while(n--) {}
}

/* 延时，一次循环大概是1ms，在主频396MHz
 * n ：延时ms数
  */
void delay(volatile unsigned int ms)
{
    while(ms--) {
        delay_short(0x7ff);
    }
}

/*延时初始化*/
void delay_init(void)
{
    GPT1->CR = 0;
    GPT1->CR = 1 << 15;
    while(GPT1->CR >> 15 & 0X1);
    /*设置RESET模式，设置66mhz时钟*/
    GPT1->CR &= ~(0X7 << 6);
    GPT1->CR = (1 << 1) | (1 << 6);
    GPT1->CR &= ~(1 << 9);
    //设置分频66
    GPT1->PR = 65;
    
    GPT1->OCR[0] = 0xFFFFFFFF; //71min轮回
#if 0
    //设置中断
    GPT1->IR = (1 << 0);

    GIC_EnableIRQ(GPT1_IRQn);
    system_register_irqhandler(GPT1_IRQn, gpt1_handler, NULL);
    //使能定时器   
#endif
    GPT1->CR |= (1 << 0);
}

void delay_us(unsigned int us)
{
    unsigned int oldct, newct;
    unsigned int pass = 0;
    oldct = GPT1->CNT;
    while(1)
    {
        newct = GPT1->CNT;
        if(newct > oldct)
        {
            pass = newct - oldct;
        }
        else if(newct < oldct)
        {
            pass = newct + 0xFFFFFFFF-oldct;
        }
        if(pass >= us)
            break;
    }
}

void delay_ms(unsigned int ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}

//GPT中断服务函数
void gpt1_handler(unsigned int gicciar, void* param)
{
    static unsigned char state = 0;
    if(GPT1->SR & (1 << 0))
    {
        state = !state;
        led_control(state);
    }
    GPT1->SR |= (1 << 0);
}

