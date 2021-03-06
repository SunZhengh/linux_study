
#include "main.h"
#include "../bsp/clk/bsp_clk.h"
#include "../bsp/delay/bsp_delay.h"
#include "../bsp/key/bsp_key.h"
#include "../bsp/led/bsp_led.h"
#include "../bsp/beep/bsp_beep.h"
#include "../bsp/interrupt/bsp_int.h"
#include "../bsp/exti/bsp_exti.h"

void imx6ul_init(void)
{
	int_init();
	clk_enable();
	imx6u_clk_init();
	led_init();
	key_init();
	beep_init();
//	exti_init();
}

int main(void)
{
	imx6ul_init();
	while(1) {;}
	return 0;
}

