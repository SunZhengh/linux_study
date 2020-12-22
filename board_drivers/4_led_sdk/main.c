
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

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
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);
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

