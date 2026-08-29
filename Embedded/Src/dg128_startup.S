/* Runs after crt1 loads SP=0x4000, but before its first subroutine call. */
        .section .install1,"ax",@progbits
        movb    #0x21,0x0010       /* INITRM: RAM at 0x2000-0x3fff */

/* crt1 calls exit only if main returns. Embedded main must never return. */
        .section .fini4,"ax",@progbits
        .globl exit
exit:
        bra     exit
