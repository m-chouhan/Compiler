        global  main
	extern  printf
        section .text
main:
push rbx

;Block
mov		rbx,0
push		rbx
mov		rbx, 3	; #Integer# 
push		rbx
mov		rbx, [RSP+8]	; #Integer# 
add		rbx,[RSP]	;
add		RSP,8		;
mov 		rsi,rbx
mov		rdi,format
xor		rbx,rbx
call		printf
pop		rbx

pop rbx
ret
format:
        db "%d", 10 , 0
