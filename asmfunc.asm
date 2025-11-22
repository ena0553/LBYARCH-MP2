section .data
msg1 db "Hello World!",10,0
msg2 db "The first fp number is %1.2lf",10,0
msg3 db "The fp numbers are %1.2lf and %1.2lf",10,0
msg4 db "The sum is %1.2lf",10,0
msg5 db "Five integers: %lld, %lld, %lld, %lld, %lld",10,0
var1 dq 0.0
var2 dq 0.0
var3 dq 0.0 ;sum
var4 dq 111, 222, 333, 444, 555
prompt1 db "Type any character to continue...",10,0
prompt2 db "Enter a floating point number: ",0
prompt3 db "Enter another floating point number: ",0
;
scanfp db "%lf",0
scanstr db "%s",0
;
section .text
bits 64
default rel
global asmhello
extern printf, scanf
asmhello:
    mov rbp, rsp; for correct debugging
    ;write your code here
    sub rsp, 7*8
    
    lea rcx, [msg1]
    call printf  ; printf("Hello")
    
    mov rcx, prompt1 ;Type any character
    call printf
    mov rcx, scanstr
    call scanf
    
    mov rcx, prompt2 ;Enter a floating point number:
    call printf
    
    mov rcx, scanfp
    lea rdx, [var1]
    call scanf ; scanf("%lf",var1)
    
    mov rcx, msg2 ; "The first fp number is "
    mov rdx, [var1]
    call printf   ; printf("The first fp number is %lf", var1)
   
    mov rcx, prompt3 ;Enter another floating point number:
    call printf
    
    mov rcx, scanfp
    lea rdx, [var2]
    call scanf
               
    mov rcx, msg3 ; "The fp numbers are..."
    mov rdx, [var1] ; 2nd param
    mov r8, [var2]  ; 3rd param
    call printf   ; printf("The fp numbers are...", var1, var2)
    
    movsd xmm1, [var1]
    addsd xmm1, [var2]
    movsd [var3], xmm1 ;xmm1 contains sum 
    
    mov rcx, msg4 ;The sum is
    mov rdx, [var3]
    call printf 
    
    mov rcx, msg5 ;1st param (Five integers:...)
    mov rdx, [var4] ;2nd param
    mov r8, [var4+1*8] ;3rd param
    mov r9, [var4+2*8] ;4th param
    mov rax, [var4+3*8] ;5th param
    mov [rsp+32], rax
    mov rax, [var4+4*8] ;6th param
    mov [rsp+40], rax
    call printf

    add rsp, 7*8
    xor rax, rax
    ret