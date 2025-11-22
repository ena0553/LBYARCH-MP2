section .text
bits 64
default rel
global asm_kernel

; RCX = x1
; RDX = x2
; R8  = y1
; R9  = y2
; [rsp+40] = z
; [rsp+48] = n

asm_kernel:
    mov rbp, rsp

    mov r10, [rbp + 40] ; z
    mov r11d, [rbp + 48] ; n

    xor rax, rax

.loop:
    cmp rax, r11
    jge .done

    ; x2 - x1
    movss xmm0, dword [rdx + rax*4]
    movss xmm1, dword [rcx + rax*4]
    subss xmm0, xmm1
    mulss xmm0, xmm0

    ; y2 - y1
    movss xmm2, dword [r9 + rax*4]
    movss xmm3, dword [r8 + rax*4]
    subss xmm2, xmm3
    mulss xmm2, xmm2

    addss xmm0, xmm2
    sqrtss xmm0, xmm0

    movss dword [r10 + rax*4], xmm0

    inc rax
    jmp .loop

.done:
    xor rax, rax
    ret
