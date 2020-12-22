#ifndef __BSP_KEY_FILTER_H
#define __BSP_KEY_FILTER_H
#include "imx6ul.h"

void key_filter_init(void);
void key_filter_time_init(unsigned int value);
void  epti_timer_close(void);
void  epti_timer_restart(unsigned int value);
void EPIT_filter_handler(unsigned int gicciar, void* param);
void gpio1_io18_exit_filter_handler(unsigned int gicciar, void* param);

#endif