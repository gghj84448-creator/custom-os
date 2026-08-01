.section .text
.global _start
.extern kernel_main
.type _start, @function

_start:
    /* set up a simple stack and call kernel_main */
    lea stack_top(%rip), %rsp
    xor %rbp, %rbp
    call kernel_main

.hlt_loop:
    hlt
    jmp .hlt_loop

/* reserve stack in the binary's BSS */

.section .bss
.align 16
.global stack_top
stack_bottom:
    .zero 0x4000
stack_top:
