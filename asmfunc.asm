section .text
bits 64
default rel
global asm_kernel

; RCX = x1
; RDX = x2
; R8  = y1
; R9  = y2
; [rsp+48] = z
; [rsp+56] = n

asm_kernel:
    push rbp
    mov rbp, rsp

    mov r10, [rbp + 48] ; z
    mov r11d, [rbp + 56] ; n

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
    pop rbp
    xor rax, rax
    ret
