        .section .text.nonpaged,"ax",@progbits

        .globl timer_ch7_vector
timer_ch7_vector:
        jsr timer_ch7_handler
        rti

        .section .vectors,"a",@progbits

/* MC9S12DG128 vectors, 0xff80 through 0xffff. */
        .rept 48
        .word default_isr
        .endr
        .word timer_ch7_vector /* ffe0: 1 ms tick and PP4 GPIO poll */
        .word default_isr   /* ffe2: TC6 */
        .word default_isr   /* ffe4: TC5 */
        .word default_isr   /* ffe6: TC4 */
        .word default_isr   /* ffe8: TC3 */
        .word default_isr   /* ffea: TC2 */
        .word default_isr   /* ffec: TC1 */
        .word default_isr   /* ffee: TC0 */
        .word default_isr   /* fff0: RTI */
        .word default_isr   /* fff2: IRQ */
        .word default_isr   /* fff4: XIRQ */
        .word default_isr   /* fff6: SWI */
        .word default_isr   /* fff8: trap */
        .word default_isr   /* fffa: COP */
        .word default_isr   /* fffc: clock monitor */
        .word _start        /* fffe: reset */
