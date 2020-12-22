#ifndef __BSP_EPIT_H
#define __BSP_EPIT_H
#include "imx6ul.h"

void epit_init(unsigned int frac, unsigned int value);
void EPIT_handler(unsigned int gicciar, void *param);

#endif