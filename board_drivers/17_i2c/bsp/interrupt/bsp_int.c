
#include "bsp_int.h"

static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];
static int irqNesting;  //记录中断嵌套
//默认中断处理函数
void default_irq_hadler_t(unsigned int gicciar, void* param)
{
    while(1){;}
}
//初始化中断处理函数
void system_irqtable_init(void)
{
    int i = 0;
    irqNesting = 0;
    for(i=0; i < NUMBER_OF_INT_VECTORS; i++)
    {
        irqTable[i].irqHandler = default_irq_hadler_t;
        irqTable[i].userParam = NULL;
    }
}
//注册中断处理函数
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void* param)
{
    irqTable[irq].irqHandler = handler;
    irqTable[irq].userParam = param;
}
//中断分发函数
void system_irqhandler(unsigned int gicciar)
{
    uint32_t intNum = gicciar & 0x3fff;
    if(intNum > NUMBER_OF_INT_VECTORS)
    {
        return;
    }
    irqNesting++;
    irqTable[intNum].irqHandler(intNum, irqTable[intNum].userParam);
    irqNesting--;
}
//中断初始化函数
void int_init(void)
{
    GIC_Init();
    system_irqtable_init();
    __set_VBAR(0X87800000);
}
