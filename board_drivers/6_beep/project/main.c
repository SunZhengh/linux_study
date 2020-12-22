
#include "main.h"
#include "bsp_beep.h"
#include "bsp_clk.h"
#include "bsp_delay.h"

int main(void)
{
	clk_enable();
	beep_init();
	while(1){
		delay(500);
		beep_control(BEEP_ON);

		delay(500);
		beep_control(BEEP_OFF);
	}
	return 0;
}

