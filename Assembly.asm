        global  main
	extern  printf
        section .text
main:
push rbx

;Block
push		RBP
mov		RBP,RSP
sub		RSP,32;	Allocating variables
mov		rbx, 1	; #Integer# 
mov		[RBP-8],rbx;	 #Integer#  , [x , 1,undef] ;
mov		rbx, [RBP-8]	;undef
push		rbx
mov		rbx, 3	; #Integer# 
add		rbx,[RSP]	;
add		RSP,8		; Popping Stack
mov 		rsi,rbx
mov		rdi,format
xor		rbx,rbx
call		printf
add		RSP,32;	Popping Variables
pop		RBP

pop rbx
ret
format:
        db "%d", 10 , 0
