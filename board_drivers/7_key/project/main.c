
#include "main.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_key.h"
#include "bsp_led.h"

int main(void)
{
	clk_enable();
	led_init();
	key_init();
	while(1){
		if(KEY_ON == key_getvalue()){ 
			led_control(LED_ON);
		}
		else{ 
			led_control(LED_OFF);
		}
		delay(10);
	}
	return 0;
}

