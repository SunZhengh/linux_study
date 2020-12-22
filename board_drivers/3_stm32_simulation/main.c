
#include "imx6u.h"

void clk_enable(void)
{
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;
	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0xFFFFFFFF;
}

void led_init(void)
{
	IOMUX_SW_MUX->GPIO1_IO03 = 0x5;
	IOMUX_SW_PAD->GPIO1_IO03 = 0x10b0;
	GPIO1->GDIR = 0x8;
	GPIO1->DR = 0x0;
}

int main(void)
{
	CCM->CCGR1 = 0XFFFFFFFF;
	led_init();
	while(1){}
	return 0;
}

