
#include "main.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"

int main(void)
{
	clk_enable();
	led_init(LED0);
	while(1){
		delay(1000);
		led_control(LED0, LED_ON);

		delay(1000);
		led_control(LED0, LED_OFF);
	}
	return 0;
}

