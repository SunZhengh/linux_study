#include "bsp_i2c.h"

struct i2c_transfer i2c_trans_s = {0};

void i2c_init(I2C_Type *base)
{
    base->I2CR &= ~(1 << 7);
    base->IFDR = 0x15;
    base->I2CR |= (1 << 7);
    printf("i2c_init done.\r\n");
}

//start信号产生以及从机地址发送
static unsigned char i2c_master_start(I2C_Type *base, unsigned char address, enum i2c_direction direction)
{
    if(base->I2SR & (1 << 5)){
        printf("i2c_master_start: I2C_STATUS_BUSY.\r\n");
        return I2C_STATUS_BUSY;
    }
    base->I2CR |= (1 << 5) | (1 << 4);
    base->I2DR = ((unsigned int)address << 1) | ((direction == ki2c_read)? 1:0);
    printf("i2c_master_start: I2CR:%#X.\r\n", base->I2CR);
    printf("i2c_master_start: I2SR:%#X.\r\n", base->I2SR);
    return I2C_STATUS_OK;
}

//stop
static unsigned char i2c_master_stop(I2C_Type *base)
{
    unsigned short timeout = 0xFFFF;
    base->I2CR &= ~((1 << 5) | (1 << 4) | (1 << 3));
    while((base->I2SR & (1 << 5))){
        timeout--;
        if(timeout == 0){
            printf("i2c_master_stop: I2C_STATUS_TIMEOUT.\r\n");
            return I2C_STATUS_TIMEOUT;
        }
    }
    return I2C_STATUS_OK;
}

//repeat start信号产生以及从机地址发送
static unsigned char i2c_master_repeat_start(I2C_Type *base, unsigned char address, enum i2c_direction direction)
{
    if((base->I2SR & (1 << 5)) && ((base->I2CR & (1 << 5)) == 0)){
        printf("i2c_master_repeat_start: I2C_STATUS_BUSY.\r\n");
        return I2C_STATUS_BUSY;
    }
    base->I2CR |= (1 << 4) | (1 << 2);
    base->I2DR = ((unsigned int)address << 1) | ((direction == ki2c_read)? 1:0);
    return I2C_STATUS_OK;
}

//错误检查清除
static unsigned char i2c_check_and_clear_error(I2C_Type *base, unsigned int status)
{
    if(status & (1 << 4)){
        printf("i2c_check_and_clear_error:I2C_STATUS_ARBITRATIONLOST. I2SR:%#X.\r\n", base->I2SR);
        base->I2SR &= ~(1 << 4);
        base->I2CR &= ~(1 << 7);
        base->I2CR |= (1 << 7);
        return I2C_STATUS_ARBITRATIONLOST;
    }
    else if(status & 0x1){
        return I2C_STATUS_NAK;
    }
    return I2C_STATUS_OK;
}

//send
static void i2c_master_send(I2C_Type *base, const unsigned char *buf, unsigned int size)
{
    while(!(base->I2SR & (1 << 7)));
    base->I2SR &= ~(1 << 1);
    base->I2CR |= 1 << 4;

    while(size--){
        base->I2DR = *buf++;
        while(!(base->I2SR & (1 << 1)));
        base->I2SR &= ~(1 << 1);
        if(i2c_check_and_clear_error(base, base->I2SR))
            break;
    }
    base->I2SR &=~(1 << 1);
    i2c_master_stop(base);
}

//read
static void i2c_master_read(I2C_Type *base, unsigned char *buf, unsigned int size)
{
    volatile uint8_t dummy = 0;
    dummy++;

    while(!(base->I2SR & (1 << 7)));
    base->I2SR &= ~(1 << 1);
    base->I2CR &= ~((1 << 4) | (1 << 3));
    if(size == 1)
        base->I2CR |= (1 << 3);
    dummy = base->I2DR;
    while(size--){
        while(!(base->I2SR & (1 << 1)));
        base->I2SR &= ~(1 << 1);
        if(size==0){
            i2c_master_stop(base);
        }
        if(size==1){
            base->I2CR |= (1 << 3);
        }
        *buf++ = base->I2DR;
    }
}

/*
 * @description	: I2C数据传输，包括读和写
 * @param - base: 要使用的IIC
 * @param - xfer: 传输结构体
 * @return 		: 传输结果,0 成功，其他值 失败;
 */
unsigned char i2c_master_transfer(I2C_Type *base, struct i2c_transfer *xfer)
{
    unsigned char ret = 0;
        enum i2c_direction direction = xfer->direction;

    base->I2SR &= ~((1 << 1) | (1 << 4));           /* 清除标志位 */

    /* 等待传输完成 */
    while(!((base->I2SR >> 7) & 0X1)){}; 

    /* 如果是读的话，要先发送寄存器地址，所以要先将方向改为写 */
    if ((xfer->subaddressSize > 0) && (xfer->direction == ki2c_read))
    {
        direction = ki2c_write;
    }

    ret = i2c_master_start(base, xfer->slaveAddress, direction); /* 发送开始信号 */
    if(ret)
    {
        return ret;
    }

    while(!(base->I2SR & (1 << 1))){};                  /* 等待传输完成 */

    ret = i2c_check_and_clear_error(base, base->I2SR);  /* 检查是否出现传输错误 */
    if(ret)
    {
        printf("i2c_master_transfer find error 1.\r\n");
        i2c_master_stop(base);                  /* 发送出错，发送停止信号 */
        return ret;
    }

    /* 发送寄存器地址 */
    if(xfer->subaddressSize)
    {
        do
        {
            base->I2SR &= ~(1 << 1);            /* 清除标志位 */
            xfer->subaddressSize--;             /* 地址长度减一 */

            base->I2DR =  ((xfer->subaddress) >> (8 * xfer->subaddressSize)); //向I2DR寄存器写入子地址

            while(!(base->I2SR & (1 << 1)));        /* 等待传输完成 */

            /* 检查是否有错误发生 */
            ret = i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
                printf("i2c_master_transfer find error 2.\r\n");
             	i2c_master_stop(base);          /* 发送停止信号 */
             	return ret;
            }  
        } while ((xfer->subaddressSize > 0) && (ret == I2C_STATUS_OK));

        if(xfer->direction == ki2c_read)        /* 读取数据 */
        {
            base->I2SR &= ~(1 << 1);            /* 清除中断挂起位 */
            i2c_master_repeat_start(base, xfer->slaveAddress, ki2c_read); /* 发送重复开始信号和从机地址 */
            while(!(base->I2SR & (1 << 1))){};/* 等待传输完成 */

            /* 检查是否有错误发生 */
            ret = i2c_check_and_clear_error(base, base->I2SR);
            if(ret)
            {
                printf("i2c_master_transfer find error 3.\r\n");
             	ret = I2C_STATUS_ADDRNAK;
                i2c_master_stop(base); 		/* 发送停止信号 */
                return ret;  
            }
        }
    }


    /* 发送数据 */
    if ((xfer->direction == ki2c_write) && (xfer->dataSize > 0))
    {
        i2c_master_send(base, xfer->data, xfer->dataSize);
    }

    /* 读取数据 */
    if ((xfer->direction == ki2c_read) && (xfer->dataSize > 0))
    {
        i2c_master_read(base, xfer->data, xfer->dataSize);
    }
    return 0;
}
