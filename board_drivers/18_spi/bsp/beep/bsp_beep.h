#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "imx6ul.h"

#define BEEP_ON 1
#define BEEP_OFF 0

void beep_init(void);
void beep_control(char command);

#endif