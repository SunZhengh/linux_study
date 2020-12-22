#ifndef __BEEP_H
#define __BEEP_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

#define BEEP_ON 1
#define BEEP_OFF 0

void beep_init(void);
void beep_control(char command);

#endif