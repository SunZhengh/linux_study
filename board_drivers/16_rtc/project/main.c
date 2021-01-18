
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
	rtc_init();
	lcd_init();
	printf("init done.\r\n");
}

int main(void)
{
	char buf[160] = {0};
	RTC_TIME_TYPE rtcdate;
	static unsigned char led = 0;
	imx6ul_init();
	lcd_info.forecolor = LCD_RED;
	lcd_info.backcolor = LCD_WHITE;
	//lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPAH IMX6U");

	rtcdate.year = 2019;
	rtcdate.month = 8;
	rtcdate.day = 17;
	rtcdate.hour = 9;
	rtcdate.minute = 19;
	rtcdate.second = 0;
	rtc_setdatetime(&rtcdate); /* 初始化时间和日期 */

	while(1)
	{
		rtc_getdatetime(&rtcdate);
		sprintf(buf,"%d/%d/%d %d:%d:%d",rtcdate.year, rtcdate.month, rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
		lcd_show_string(639, 463, 160, 16, 16,(char*)buf);  /* 显示字符串 */
		delay_ms(1000);
		led_control(led);
		led = !led;
	}

	return 0;
}

