
#include "main.h"


/*
 * @description	: 使能I.MX6U的硬件NEON和FPU
 * @param 		: 无
 * @return 		: 无
 */
static void imx6ul_hardfpu_enable(void)
{
	uint32_t cpacr;
	uint32_t fpexc;

	/* 使能NEON和FPU */
	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
		   |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);

	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;	
	__set_FPEXC(fpexc);
}


static void imx6ul_init(void)
{
	int_init();
	imx6u_clk_init();
	delay_init();
	clk_enable();
	uart_init();
	printf("********** APP Start **********.\r\n");
	led_init();
	beep_init();
	key_init();
	rtc_init();
	lcd_init();
	ap3216c_init();
	icm20608_init();
	gt9147_init();
}

int main(void)
{
	char buf[160] = {0};
	static unsigned char led = 0;

	imx6ul_init();
	imx6ul_hardfpu_enable(); /* 开启硬件浮点运算及ENON */

#ifdef SCONFIG_ICM20608
	lcd_show_string(50, 100, 200, 16, 16, (char*)"ICM20608 Ready");
	
	lcd_show_string(50, 130, 200, 16, 16, (char*)"accel x:");  
	lcd_show_string(50, 150, 200, 16, 16, (char*)"accel y:");  
	lcd_show_string(50, 170, 200, 16, 16, (char*)"accel z:");  
	lcd_show_string(50, 190, 200, 16, 16, (char*)"gyro  x:"); 
	lcd_show_string(50, 210, 200, 16, 16, (char*)"gyro  y:"); 
	lcd_show_string(50, 230, 200, 16, 16, (char*)"gyro  z:"); 
	lcd_show_string(50, 250, 200, 16, 16, (char*)"temp   :"); 

	lcd_show_string(50 + 181, 130, 200, 16, 16, (char*)"g");  
	lcd_show_string(50 + 181, 150, 200, 16, 16, (char*)"g");  
	lcd_show_string(50 + 181, 170, 200, 16, 16, (char*)"g");  
	lcd_show_string(50 + 181, 190, 200, 16, 16, (char*)"o/s"); 
	lcd_show_string(50 + 181, 210, 200, 16, 16, (char*)"o/s"); 
	lcd_show_string(50 + 181, 230, 200, 16, 16, (char*)"o/s"); 
	lcd_show_string(50 + 181, 250, 200, 16, 16, (char*)"C");
#endif

	while(1)
	{
#ifdef SCONFIG_RTC
		rtc_getdatetime(&rtcDate);
		sprintf(buf,"%d/%d/%d %d:%d:%d", rtcDate.year, rtcDate.month, rtcDate.day, rtcDate.hour, rtcDate.minute, rtcDate.second);
		lcd_show_string(639, 463, 160, 16, 16, (char*)buf);  /* 显示字符串 */
#endif
#ifdef SCONFIG_AP3216C
		ap3216c_read_data(&ir, &ps, &als);		/* 读取数据		  	*/
		lcd_shownum(30 + 32, 160, ir, 5, 16);	/* 显示IR数据 		*/
		lcd_shownum(30 + 32, 180, ps, 5, 16);	/* 显示PS数据 		*/
		lcd_shownum(30 + 32, 200, als, 5, 16);	/* 显示ALS数据 		*/ 
#endif
#ifdef SCONFIG_LED
		delay_ms(1000);
		led_control(led);
		led = !led;
#endif
#ifdef SCONFIG_ICM20608
		icm20608_getdata();
		integer_display(50 + 70, 130, 16, icm20608_dev.accel_x_adc);
		integer_display(50 + 70, 150, 16, icm20608_dev.accel_y_adc);
		integer_display(50 + 70, 170, 16, icm20608_dev.accel_z_adc);
		integer_display(50 + 70, 190, 16, icm20608_dev.gyro_x_adc);
		integer_display(50 + 70, 210, 16, icm20608_dev.gyro_y_adc);
		integer_display(50 + 70, 230, 16, icm20608_dev.gyro_z_adc);
		integer_display(50 + 70, 250, 16, icm20608_dev.temp_adc);

		decimals_display(50 + 70 + 50, 130, 16, icm20608_dev.accel_x_act);
		decimals_display(50 + 70 + 50, 150, 16, icm20608_dev.accel_y_act);
		decimals_display(50 + 70 + 50, 170, 16, icm20608_dev.accel_z_act);
		decimals_display(50 + 70 + 50, 190, 16, icm20608_dev.gyro_x_act);
		decimals_display(50 + 70 + 50, 210, 16, icm20608_dev.gyro_y_act);
		decimals_display(50 + 70 + 50, 230, 16, icm20608_dev.gyro_z_act);
		decimals_display(50 + 70 + 50, 250, 16, icm20608_dev.temp_act);
#endif
#ifdef SCONFIG_TOUCH
		printf("x = %d, y = %d.\r\n", gt9147_dev.x[0], gt9147_dev.y[0]);
#endif
	}

	return 0;
}

