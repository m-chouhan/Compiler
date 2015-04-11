        global  main
	extern  printf
        section .text
main:
push rbx

;Block
push		RBP
mov		RBP,RSP
sub		RSP,24;	Allocating variables
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
mov		rbx, [RBP-8]	;undef
jz ELSE1

;Block
push		RBP
mov		RBP,RSP
sub		RSP,8;	Allocating variables
mov		rbx, 1	; #Integer# 
mov		[RBP-8],rbx;	 #Integer#  , [x , 1,undef] ;
mov		rbx, [RBP-8]	;undef
mov 		rsi,rbx
mov		rdi,format
xor		rbx,rbx
call		printf
add		RSP,8;	Popping Variables
pop		RBP

ELSE1:
add		RSP,24;	Popping Variables
pop		RBP

pop rbx
ret
format:
        db "%d", 10 , 0
