#include "ap3216c.h"
unsigned short ir, ps, als;

static unsigned char ap3216c_readonebyte(unsigned char addr, unsigned char reg)
{
    unsigned char val = 0;
    struct i2c_transfer masterxfer;
    masterxfer.slaveAddress = addr;
    masterxfer.direction = ki2c_read;
    masterxfer.subaddress = reg;
    masterxfer.subaddressSize = 1;
    masterxfer.data = &val;
    masterxfer.dataSize = 1;

    i2c_master_transfer(I2C1, &masterxfer);

    return val;
}

static unsigned char ap3216c_writeonebyte(unsigned char addr, unsigned char reg, unsigned char data)
{
    struct i2c_transfer masterxfer;
    masterxfer.slaveAddress = addr;
    masterxfer.direction = ki2c_write;
    masterxfer.subaddress = reg;
    masterxfer.subaddressSize = 1;
    masterxfer.data = &data;
    masterxfer.dataSize = 1;

    return i2c_master_transfer(I2C1, &masterxfer);
}

void ap3216c_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART4_TX_DATA_I2C1_SCL, 1);
    IOMUXC_SetPinConfig(IOMUXC_UART4_TX_DATA_I2C1_SCL, 0x70B0);
    IOMUXC_SetPinMux(IOMUXC_UART4_RX_DATA_I2C1_SDA, 1);
    IOMUXC_SetPinConfig(IOMUXC_UART4_RX_DATA_I2C1_SDA, 0x70B0);

    i2c_init(I2C1);
    ap3216c_writeonebyte(AP3216C_ADDR, AP3216C_SYSTEMCONG, 0x4);
    delay_ms(50);
    ap3216c_writeonebyte(AP3216C_ADDR, AP3216C_SYSTEMCONG, 0x3);
    printf("ap3216c_init done. AP3216C_SYSTEMCONG:%#X.\r\n", ap3216c_readonebyte(AP3216C_ADDR, AP3216C_SYSTEMCONG));
}

void ap3216c_read_data(unsigned short *ir, unsigned short *ps, unsigned short *als)
{
    unsigned char buf[6] = {0};
    unsigned char i = 0;
    for(i = 0;i<6;i++){
        buf[i] = ap3216c_readonebyte(AP3216C_ADDR, AP3216C_IRDATALOW);
    }
    if(buf[0] & 0x80) { /* 为真表示IR和PS数据无效 */
        *ir = 0;
        *ps = 0;
    } else {
        *ir = ((unsigned short)buf[1] << 2) | (buf[0] & 0x03);
        *ps = (((unsigned short)buf[5] & 0x3F) << 4) | (buf[4] & 0x0F);
    }
    *als  = ((unsigned short)buf[3] << 8) | buf[2]; 
}
