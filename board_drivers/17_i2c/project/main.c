
#include "main.h"


void imx6ul_init(void)
{
	int_init();
	imx6u_clk_init();
	delay_init();
	clk_enable();
	uart_init();
	led_init();
	beep_init();
	key_init();
	rtc_init();
	lcd_init();
	ap3216c_init();
}

int main(void)
{
	char buf[160] = {0};
	static unsigned char led = 0;

	imx6ul_init();

	while(1)
	{
		rtc_getdatetime(&rtcDate);
		sprintf(buf,"%d/%d/%d %d:%d:%d", rtcDate.year, rtcDate.month, rtcDate.day, rtcDate.hour, rtcDate.minute, rtcDate.second);
		lcd_show_string(639, 463, 160, 16, 16, (char*)buf);  /* 显示字符串 */

		ap3216c_read_data(&ir, &ps, &als);		/* 读取数据		  	*/
		lcd_shownum(30 + 32, 160, ir, 5, 16);	/* 显示IR数据 		*/
		lcd_shownum(30 + 32, 180, ps, 5, 16);	/* 显示PS数据 		*/
		lcd_shownum(30 + 32, 200, als, 5, 16);	/* 显示ALS数据 	*/ 

		delay_ms(500);
		led_control(led);
		led = !led;
	}

	return 0;
}

