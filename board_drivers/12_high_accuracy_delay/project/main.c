
#include "main.h"
#include "../bsp/clk/bsp_clk.h"
#include "../bsp/delay/bsp_delay.h"
#include "../bsp/key/bsp_key.h"
#include "../bsp/led/bsp_led.h"
#include "../bsp/beep/bsp_beep.h"
#include "../bsp/interrupt/bsp_int.h"
#include "../bsp/exti/bsp_exti.h"
#include "../bsp/epit/bsp_epit.h"
#include "../bsp/key_filter/bsp_key_filter.h"

void imx6ul_init(void)
{
	int_init();
	imx6u_clk_init();
	clk_enable();
	led_init();
	key_init();
	beep_init();
	delay_init();
}

int main(void)
{
	imx6ul_init();
	static char state = 0;
	while(1) {
		state = !state;
		led_control(state);
		delay_ms(500);
	}
	return 0;
}

