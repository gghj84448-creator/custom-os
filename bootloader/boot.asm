; Boot loader for Custom OS
; This is a simple multiboot-compliant bootloader

[BITS 32]
[EXTERN kernel_main]

; Multiboot header
MB_MAGIC equ 0x1BADB002
MB_FLAGS equ 0x00000003
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

align 4
multiboot_header:
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0

; Entry point
section .text
global _start
_start:
    ; Set up stack
    mov esp, kernel_stack_top
    
    ; Clear EFLAGS
    push 0
    popf
    
    ; Call kernel
    call kernel_main
    
    ; Hang if kernel returns
    cli
.hang:
    hlt
    jmp .hang

; Stack
section .bss
align 16
kernel_stack:
    resb 16384
kernel_stack_top:
