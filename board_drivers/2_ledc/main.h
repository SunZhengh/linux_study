#ifndef __MAIN_H
#define __MAIN_H

#define CCM_CCGR0 *((volatile unsigned int *)0x020c4068)
#define CCM_CCGR1 *((volatile unsigned int *)0x020c406c)
#define CCM_CCGR2 *((volatile unsigned int *)0x020c4070)
#define CCM_CCGR3 *((volatile unsigned int *)0x020c4074)
#define CCM_CCGR4 *((volatile unsigned int *)0x020c4078)
#define CCM_CCGR5 *((volatile unsigned int *)0x020c407c)
#define CCM_CCGR6 *((volatile unsigned int *)0x020c4080)

#define SW_MUX_GPIO1_IO03 *((volatile unsigned int *)0x020E0068)
#define SW_PAD_GPIO1_IO03 *((volatile unsigned int *)0x020E02F4)

#define GPIO1_DR *((volatile unsigned int * )0x0209C000)
#define GPIO1_GDIR *((volatile unsigned int *)0x0209C004)

#endif
