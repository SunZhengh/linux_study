
#include "main.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_key.h"
#include "bsp_led.h"

int imx6ul_init(void)
{
	clk_enable();
	imx6u_clk_init();
	led_init();
	key_init();
	beep_init();
}

int main(void)
{
	imx6ul_init();
	while(1){
		delay(1000);
		led_control(LED_ON);

		delay(1000);
		led_control(LED_OFF);
	}
	return 0;
}

