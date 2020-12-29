#ifndef __BSP_INT_H
#define __BSP_INT_H

#include "imx6ul.h"
/*定义中断处理函数*/
typedef void (*system_irq_handler_t)(unsigned int gicciar, void* param);

typedef struct _sys_irq_handler
{
    system_irq_handler_t irqHandler;
    void *userParam;
}sys_irq_handle_t;

void default_irq_hadler_t(unsigned int gicciar, void* param);
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void* param);
void int_init(void);

#endif // !__BSP_INT_H#define __BSP_INT_H
