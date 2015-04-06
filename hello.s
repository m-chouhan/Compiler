.data
.globl hello
hello:
.string "Hello, world!"

.text
.global main
main:
    pushq   %rbp
    movq    %rsp,       %rbp
    Loop:
    movq    $hello,     %rdi
    call    puts
    movq    $0,         %rax
    beqz $0,	Loop
    leave
    ret
