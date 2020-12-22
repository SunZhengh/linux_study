.global _start 

_start:
    @clock enable
    ldr r0, =0x020C406C
    ldr r1, =0x0C0C0000
    str r1, [r0]

    @set output mode
    ldr r0, =0x020E0068
    ldr r1, =0x00000005
    str r1, [r0]

    @set electircal property
    ldr r0, =0x020E02F4
    ldr r1, =0x10B0
    str r1, [r0]

    @set output mode
    ldr r0, =0x0209C004
    ldr r1, =0x8
    str r1, [r0]

    @output
    ldr r0, =0x0209C000
    ldr r1, =0x0
    str r1, [r0]

loop:
    b loop


