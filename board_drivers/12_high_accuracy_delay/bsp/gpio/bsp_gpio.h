#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"

typedef enum _gpio_interrupt_mode
{
    kGPIO_NoIntMode = 0U, 
    kGPIO_IntLowLevel = 1U,
    kGPIO_IntHighLevel = 2U,
    kGPIO_IntRisingEdge = 3U,
    kGPIO_IntFallingEdge = 4U,
    kGPIO_IntRisingOrFallingEdge = 5U,
}gpio_interrupt_mode_t;

/* 枚举类型和GPIO结构体 */
typedef enum _gpio_pin_direction
{
   kGPIO_DigitalInput = 0U,
   kGPIO_DigitalOutput = 1U,
}gpio_pin_direction_t;

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction;
    uint8_t outputLogic;
    gpio_interrupt_mode_t InterruptMode;
}gpio_pin_config_t;

void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config);
void gpio_pinwrite(GPIO_Type *base, int pin, int value);
int gpio_pinread(GPIO_Type *base, int pin);
void gpio_interrupt_enable(GPIO_Type *base, unsigned int pin);
void gpio_interrupt_disable(GPIO_Type *base, unsigned int pin);
void gpio_interrupt_flag_clear(GPIO_Type *base, unsigned int pin);
void gpio_interrupt_config(GPIO_Type *base, unsigned int pin, gpio_interrupt_mode_t mode);
#endif