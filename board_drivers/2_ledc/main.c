
#include "main.h"

void clk_enable(void)
{
	CCM_CCGR0 = 0XFFFFFFFF;
	CCM_CCGR1 = 0XFFFFFFFF;
	CCM_CCGR2 = 0XFFFFFFFF;
	CCM_CCGR3 = 0XFFFFFFFF;
	CCM_CCGR4 = 0XFFFFFFFF;
	CCM_CCGR5 = 0XFFFFFFFF;
	CCM_CCGR6 = 0xFFFFFFFF;
}

void led_init(void)
{
	SW_MUX_GPIO1_IO03 = 0x5;
	SW_PAD_GPIO1_IO03 = 0x10b0;
	GPIO1_GDIR = 0x8;
	GPIO1_DR = 0x0;
}

int main(void)
{
	CCM_CCGR1 = 0XFFFFFFFF;
	SW_MUX_GPIO1_IO03 = 0x5;
	SW_PAD_GPIO1_IO03 = 0x10B0;
	GPIO1_GDIR = 0x8;
	GPIO1_DR = 0x0;
	while(1){}
	return 0;
}
