        global  main
	extern  printf
	extern	scanf
        section .text
main:
push rbx

;Block
push		RBP
mov		RBP,RSP
sub		RSP,24;	Allocating variables
mov		rbx, 10	; #Integer# 
mov		[RBP-8],rbx;	 #Integer#  , [x , 1,undef] ;
mov		rsi,RBP
sub		rsi,8
mov	 	rdi,scanstring;	parameters
mov		al,0
call		scanf

mov		rbx, [RBP-8]	;undef
mov 		rsi,rbx
mov		rdi,format
xor		rbx,rbx
call		printf

LOOP1: 
mov		rbx, [RBP-8]	;undef
cmp		rbx,0
jz EXIT_LOOP1

;Block
mov		rbx, 2	; #Integer# 
push		rbx
mov		rbx, [RBP-8]	;undef
sub		rbx,[RSP]	;
add		RSP,8		; Popping Stack
mov		[RBP-8],rbx;	 #Integer#  , [x , 1,undef] ;
mov		rbx, [RBP-8]	;undef
mov 		rsi,rbx
mov		rdi,format
xor		rbx,rbx
call		printf


jmp LOOP1
EXIT_LOOP1:

add		RSP,24;	Popping Variables
pop		RBP

pop rbx
ret
format:
        db "%d", 10 , 0
scanstring:
        db "%d",0
