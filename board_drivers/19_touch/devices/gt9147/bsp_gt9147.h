#ifndef _GT9147_H
#define _GT9147_H

#include "imx6ul.h"
#include "stdio.h"
#include "../bsp/i2c/bsp_i2c.h"
#include "../bsp/gpio/bsp_gpio.h"
#include "../bsp/delay/bsp_delay.h"
#include "../bsp/interrupt/bsp_int.h"

#define gpio_enableint gpio_interrupt_enable
#define gpio_clearintflags gpio_interrupt_flag_clear

/* 宏定义 */
#define GT9147_ADDR				0X14	/* GT9147设备地址 		    */

#define GT_CTRL_REG 	        0X8040  /* GT9147控制寄存器         */
#define GT_MODSW_REG 	        0X804D  /* GT9147模式切换寄存器        */
#define GT_CFGS_REG 	        0X8047  /* GT9147配置起始地址寄存器    */
#define GT_CHECK_REG 	        0X80FF  /* GT9147校验和寄存器       */
#define GT_PID_REG 		        0X8140  /* GT9147产品ID寄存器       */

#define GT_GSTID_REG 	        0X814E  /* GT9147当前检测到的触摸情况 */
#define GT_TP1_REG 		        0X8150  /* 第一个触摸点数据地址 */
#define GT_TP2_REG 		        0X8158	/* 第二个触摸点数据地址 */
#define GT_TP3_REG 		        0X8160  /* 第三个触摸点数据地址 */
#define GT_TP4_REG 		        0X8168  /* 第四个触摸点数据地址  */
#define GT_TP5_REG 		        0X8170	/* 第五个触摸点数据地址   */
										 
#define GT9147_XYCOORDREG_NUM	30		/* 触摸点坐标寄存器数量 */
#define GT9147_INIT_FINISHED	1		/* 触摸屏初始化完成 			*/
#define GT9147_INIT_NOTFINISHED	0		/* 触摸屏初始化未完成 			*/


/* 触摸屏结构体 */
struct gt9147_dev_struc
{	
	unsigned char initfalg;		/* 触摸屏初始化状态 */
	unsigned char intflag;		/* 标记中断有没有发生 */
	unsigned char point_num;	/* 触摸点 		*/
	unsigned short x[5];		/* X轴坐标 	*/ 
	unsigned short y[5];		/* Y轴坐标 	*/
};

extern struct gt9147_dev_struc gt9147_dev;

/* 函数声明 */
void gt9147_init(void);

void gt9147_irqhandler(void);
unsigned char gt9147_write_byte(unsigned char addr,unsigned int reg, unsigned char data);
unsigned char gt9147_read_byte(unsigned char addr,unsigned int reg);
void gt9147_read_len(unsigned char addr,unsigned int reg,unsigned int len,unsigned char *buf);
void gt9147_write_len(unsigned char addr,unsigned int reg,unsigned int len,unsigned char *buf);
void gt9147_read_tpnum(void);
void gt9147_read_tpcoord(void);
void gt9147_send_cfg(unsigned char mode);
void gt9147_read_tpcoord(void);
#endif

