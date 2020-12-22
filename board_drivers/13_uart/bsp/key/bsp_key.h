#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "fsl_iomuxc.h"

enum key_value {
    KEY_NONE = 0,
    KEY0_VALUE,
};

void key_init(void);
uint8_t read_key(void);
uint8_t key_getvalue(void);

#endif // !__BSP_KEY_H
