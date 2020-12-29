
#include "main.h"


void imx6ul_init(void)
{
	int_init();
	imx6u_clk_init();
	clk_enable();
	led_init();
	delay_init();
	uart_init();
}

int main(void)
{
	
	imx6ul_init();
	static int led = 0;

	while(1)
	{
		printf("%d.\r\n", led);
		delay_ms(1000);
		led_control(led);
		led = !led;
	}

	return 0;
}

