#ifndef __AP3216C_H
#define __AP3216C_H

#include "imx6ul.h"
#include "../bsp/i2c/bsp_i2c.h"
#include "../bsp/gpio/bsp_gpio.h"
#include "../bsp/delay/bsp_delay.h"

#define AP3216C_ADDR 0x1E
/* 寄存器地址 */
#define AP3216C_SYSTEMCONG      0X00
#define AP3216C_INTSTATUS       0X01
#define AP3216C_INTCLEAR        0X02
#define AP3216C_IRDATALOW       0X0A
#define AP3216C_IRDATAHIGH      0X0B
#define AP3216C_ALSDATALOW      0X0C
#define AP3216C_ALSDATAHIGH     0X0D
#define AP3216C_PSDATALOW       0X0E
#define AP3216C_PSDATAHIGH      0X0F

extern unsigned short ir, ps, als;

void ap3216c_init(void);
void ap3216c_read_data(unsigned short *ir, unsigned short *ps, unsigned short *als);

#endif // !__AP3216C_H
