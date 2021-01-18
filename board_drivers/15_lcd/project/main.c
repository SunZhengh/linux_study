
#include "main.h"


void imx6ul_init(void)
{
	int_init();
	imx6u_clk_init();
	delay_init();
	uart_init();
	clk_enable();
	led_init();
	beep_init();
	key_init();
	lcd_init();
}

int main(void)
{
	static unsigned char led = 0;
	imx6ul_init();
	lcd_info.forecolor = LCD_RED;
	lcd_info.backcolor = LCD_WHITE;
	lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPAH IMX6U");
	lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
	lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM&ALIENTEK");
	lcd_show_string(10, 130, 240, 12, 12,(char*)"2020/1/18 14:36");

	while(1)
	{
		delay_ms(1000);
		led_control(led);
		led = !led;
	}

	return 0;
}

