.global _start



_start:
    ldr pc, =Reset_Handler
    ldr pc, =Undefined_Handler
    ldr pc, =SVC_Handler
    ldr pc, =Preabort_Handler
    ldr pc, =Databort_Handler
    ldr pc, =Notused_Handler
    ldr pc, =IRQ_Handler
    ldr pc, =FIQ_Handler

Reset_Handler:
    cpsid i
    /*关闭I/D cache and mmu */
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(1 << 12)
    bic r0, r0, #(7 << 0)
    mcr p15, 0, r0, c1, c0, 0
#if 0
    /*设置中断向量偏移 */
    ldr r0, =0x87800000
    dsb
    isb
    mcr p15, 0, r0, c12, c0, 0
    dsb
    isb
#endif

.global _bss_start
_bss_start:
    .word __bss_start

.global _bss_end
_bss_end:
    .word __bss_end

    /*清除BSS段*/
    ldr r0, _bss_start
    ldr r1, _bss_end
    mov r2, #0x0
bss_loop:
    stmia r0!, {r2}
    cmp r0, r1
    ble bss_loop

    /*设置IRQ模式SP指针*/
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x12
    msr cpsr, r0
    ldr sp, =0x80600000
    /*设置sys模式SP指针*/
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x1f
    msr cpsr, r0
    ldr sp, =0x80400000
    /*设置SVC模式SP指针*/
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x13
    msr cpsr, r0
    ldr sp, =0x80200000

    cpsie i
    /*jump to main */
    b main

Undefined_Handler:
    ldr r0, =Undefined_Handler
    bx r0
SVC_Handler:
    ldr r0, =SVC_Handler
    bx r0
Preabort_Handler:
    ldr r0, =Preabort_Handler
    bx r0
Databort_Handler:
    ldr r0, =Databort_Handler
    bx r0
Notused_Handler:
    ldr r0, =Notused_Handler
    bx r0
IRQ_Handler:
    push {lr}                   //保存程序运行地址
    push {r0-r3, r12}
    mrs r0, spsr 
    push {r0}
    mrc p15, 4, r1, c15, c0, 0  //读取GIC基地址
    add r1, r1, #0x2000
    ldr r0, [r1, #0xc]      //保存中断ID在r0
    push {r0, r1}
    cps #0x13           //进入SVC模式
    push {lr}
    ldr r2, =system_irqhandler  //进入中断处理函数
    blx r2

    pop {lr}
    cps #0x12           //进入IRQ模式
    pop {r0, r1}
    str r0, [r1, #0x10]     //中断处理完成
    pop {r0}
    msr spsr_cxsf, r0
    pop {r0-r3, r12}
    pop {lr}
    subs pc, lr, #4         //lr-4赋值给pc

FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0




