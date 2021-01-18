#include "bsp_lcd.h"
#include "../bsp/gpio/bsp_gpio.h"
#include "../bsp/delay/bsp_delay.h"

lcd_info_s lcd_info = {0};

/* 像素时钟配置
 * @prediv      分频值1-8
 * @div         分频值1-8
 * @loopdiv     DIV_SELECT 27-54
 * 像素时钟 = 24 * loopdiv / (prediv * div)
*/
static void lcd_clk_init(unsigned char loopdiv, unsigned char prediv, unsigned char div)
{ 
    CCM_ANALOG->PLL_VIDEO_NUM = 0;
    CCM_ANALOG->PLL_VIDEO_DENOM = 0;
    CCM_ANALOG->PLL_VIDEO = (1 << 13)|(2 << 19)|(loopdiv << 0);
    CCM_ANALOG->MISC2 &= ~(3 << 30);
    CCM->CSCDR2 &= ~(7 << 15);
    CCM->CSCDR2 |= (2 << 15);
    CCM->CSCDR2 &= ~(7 << 12);
    CCM->CSCDR2 |= ((prediv - 1) << 12);
    CCM->CBCMR &= ~(7 << 23);
    CCM->CBCMR |= ((div - 1) << 23);
    CCM->CSCDR2 &= ~(7 << 9);
    CCM->CSCDR2 |= 0 << 9;
}

//读取屏幕ID
static unsigned short read_lcd_panelid(void)
{
    unsigned char idx = 0;
    //打开VSYNC
    gpio_pin_config_t lcdio_config;
    IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_GPIO3_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_GPIO3_IO03, 0x10B0);

    lcdio_config.direction = kGPIO_DigitalOutput;
    lcdio_config.outputLogic = 1;
    gpio_init(GPIO3, 3, &lcdio_config);

    //读取ID
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_GPIO3_IO12, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_GPIO3_IO20, 0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_GPIO3_IO28, 0);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_GPIO3_IO12, 0xF080);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_GPIO3_IO20, 0xF080);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_GPIO3_IO28, 0xF080);

    lcdio_config.direction = kGPIO_DigitalInput;
    gpio_init(GPIO3, 12, &lcdio_config);
    gpio_init(GPIO3, 20, &lcdio_config);
    gpio_init(GPIO3, 28, &lcdio_config);

    idx = (unsigned char)gpio_pinread(GPIO3, 28);
    idx |= (unsigned char)gpio_pinread(GPIO3, 20) << 1;
    idx |= (unsigned char)gpio_pinread(GPIO3, 12) << 2;

    switch(idx){
    case 0:
        return ATK_4342;
    case 1:
        return ATK_7084;
    case 2:
        return ATK_7016;
    case 4:
        return ATK_4384;
    case 5:
        return ATK_1018;
    default:
        return 0;
    }
}

//LCD io初始化
static void lcd_io_init(void)
{
    /* 设置IO复用 */
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA00_LCDIF_DATA00,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA01_LCDIF_DATA01,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA02_LCDIF_DATA02,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA03_LCDIF_DATA03,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA04_LCDIF_DATA04,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA05_LCDIF_DATA05,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA06_LCDIF_DATA06,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_LCDIF_DATA07,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA08_LCDIF_DATA08,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA09_LCDIF_DATA09,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA10_LCDIF_DATA10,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA11_LCDIF_DATA11,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA12_LCDIF_DATA12,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA13_LCDIF_DATA13,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA14_LCDIF_DATA14,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_LCDIF_DATA15,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA16_LCDIF_DATA16,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA17_LCDIF_DATA17,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA18_LCDIF_DATA18,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA19_LCDIF_DATA19,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA20_LCDIF_DATA20,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA21_LCDIF_DATA21,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA22_LCDIF_DATA22,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_LCDIF_DATA23,0);

    IOMUXC_SetPinMux(IOMUXC_LCD_CLK_LCDIF_CLK,0);	
    IOMUXC_SetPinMux(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0);	
    IOMUXC_SetPinMux(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0);
    IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0);

    /* 设置电气属性 */
    /* 2、配置LCD IO属性	
        *bit 16:0 HYS关闭
        *bit [15:14]: 0 默认22K上拉
        *bit [13]: 0 pull功能
        *bit [12]: 0 pull/keeper使能 
        *bit [11]: 0 关闭开路输出
        *bit [7:6]: 10 速度100Mhz
        *bit [5:3]: 111 驱动能力为R0/7
        *bit [0]: 1 高转换率
        */
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA00_LCDIF_DATA00,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA01_LCDIF_DATA01,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA02_LCDIF_DATA02,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA03_LCDIF_DATA03,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA04_LCDIF_DATA04,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA05_LCDIF_DATA05,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA06_LCDIF_DATA06,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_LCDIF_DATA07,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA08_LCDIF_DATA08,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA09_LCDIF_DATA09,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA10_LCDIF_DATA10,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA11_LCDIF_DATA11,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA12_LCDIF_DATA12,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA13_LCDIF_DATA13,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA14_LCDIF_DATA14,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_LCDIF_DATA15,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA16_LCDIF_DATA16,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA17_LCDIF_DATA17,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA18_LCDIF_DATA18,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA19_LCDIF_DATA19,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA20_LCDIF_DATA20,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA21_LCDIF_DATA21,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA22_LCDIF_DATA22,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_LCDIF_DATA23,0xB9);

    IOMUXC_SetPinConfig(IOMUXC_LCD_CLK_LCDIF_CLK,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0xB9);
    IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0xB9);

    /* 点亮背光 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08 ,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08 ,0X10b0);

    /* 背光GPIO初始化 */
    gpio_pin_config_t bl_config;
    bl_config.direction = kGPIO_DigitalOutput;
    bl_config.outputLogic = 1;
    gpio_init(GPIO1, 8, &bl_config);
}

//复位LCD控制器
static void lcd_reset(void)
{
    LCDIF->CTRL |= 1 << 31;
}

//停止复位
static void lcd_unreset(void)
{
    LCDIF->CTRL &= ~(1 << 31);
}

//屏幕ID匹配
static void screen_id_match(unsigned short id)
{
    switch(id){
    case ATK_4342:
        lcd_info.height = 272;
        lcd_info.width = 480;
        lcd_info.vspw = 1;
        lcd_info.vbpd = 8;
        lcd_info.vfpd = 8;
        lcd_info.hspw = 1;
        lcd_info.hbpd = 40;
        lcd_info.hfpd = 5;
        lcd_clk_init(27, 8, 8);
        break;
    case ATK_7084:
        lcd_info.height = 480;
        lcd_info.width = 800;
        lcd_info.vspw = 1;
        lcd_info.vbpd = 23;
        lcd_info.vfpd = 22;
        lcd_info.hspw = 1;
        lcd_info.hbpd = 46;
        lcd_info.hfpd = 210;
        lcd_clk_init(30, 3, 7);
        break;
    case ATK_4384:
        lcd_info.height = 480;
        lcd_info.width = 800;
        lcd_info.vspw = 3;
        lcd_info.vbpd = 32;
        lcd_info.vfpd = 13;
        lcd_info.hspw = 48;
        lcd_info.hbpd = 88;
        lcd_info.hfpd = 40;
        lcd_clk_init(42, 4, 8);
        printf("ATK_4384 matched.\r\n");
        break;
    }
    lcd_info.pixelsize = 4;
    lcd_info.framebufer = LCD_FRAMEBUF_ADDR;
    lcd_info.forecolor = LCD_WHITE;
    lcd_info.backcolor = LCD_BLACK;
} 

static void lcd_enable(void)
{
    LCDIF->CTRL |= (1 << 0);
}

//LCD 初始化
void lcd_init(void)
{
    unsigned short lcd_id = 0; 
    lcd_id = read_lcd_panelid();
    lcd_io_init();
    lcd_reset();
    delay_ms(10);
    lcd_unreset();
    screen_id_match(lcd_id);

    LCDIF->CTRL = 0;
    LCDIF->CTRL |= (1 << 5)|(3 << 8)|(3 << 10)|(1 << 17)|(1 << 19);
    LCDIF->CTRL1 = 0;
    LCDIF->CTRL1 |= (7 << 16);
    LCDIF->TRANSFER_COUNT = 0;
    LCDIF->TRANSFER_COUNT = (lcd_info.height << 16)|(lcd_info.width << 0);
    LCDIF->VDCTRL0 = 0;
    LCDIF->VDCTRL0 = (lcd_info.vspw << 0) | (1 << 20) | (1 << 21) | (1 << 24) | (0 << 25) | (0 << 26) | (0 << 27) | (1 << 28) | (0 << 29);
    LCDIF->VDCTRL1 = lcd_info.vspw + lcd_info.vbpd + lcd_info.vfpd + lcd_info.height;
    LCDIF->VDCTRL2 = (lcd_info.hspw + lcd_info.hbpd + lcd_info.width + lcd_info.hfpd) | (lcd_info.hspw << 18);
    LCDIF->VDCTRL3 = (lcd_info.vbpd + lcd_info.vspw) | ((lcd_info.hbpd + lcd_info.hspw) << 16);
    LCDIF->VDCTRL4 = lcd_info.width | (1 << 18);
    LCDIF->CUR_BUF = (unsigned int)lcd_info.framebufer;
    LCDIF->NEXT_BUF = (unsigned int)lcd_info.framebufer;

    lcd_enable();
    delay_ms(20);
    lcd_clear(LCD_WHITE);
    printf("LCD init done.\r\n");
}

//打点函数
inline void lcd_drawpoint(unsigned short x, unsigned short y, unsigned int color)
{
    *(unsigned int *)((unsigned int)lcd_info.framebufer + 
        lcd_info.pixelsize * (lcd_info.width * y + x)) = color;
}
//读点函数
inline unsigned int lcd_readpoint(unsigned short x, unsigned short y)
{
    return *(unsigned int *)((unsigned int)lcd_info.framebufer + 
                lcd_info.pixelsize * (lcd_info.width * y + x));
}
//清屏函数
void lcd_clear(unsigned int color)
{
    unsigned int num = 0;
    unsigned int i = 0;
    unsigned int* start_addr = (unsigned int *)lcd_info.framebufer;
    num = (unsigned int)(lcd_info.width * lcd_info.height);
    for(i=0;i<num;i++)
    {
        start_addr[i] = color;
    }
}
