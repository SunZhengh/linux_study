.global _start

_start:
    mrs r0, cpsr
    bic r0, r0, #0x1f
    orr r0, r0, #0x13
    msr cpsr, r0 

    ldr sp, =0x80200000

    b main

