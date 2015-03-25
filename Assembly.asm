
#Block
Push x
Push y
Load  R1 , 10;
Load  R1 , 20;

#Block
Load  R1 , 5;
Load  R2 , mem[x,1];
ADD R3 , R1 , R2 ;
STORE R3 , mem[x , 1] ;
STORE R3 , mem[y , 2] ;
#
Load  R1 , 15;
Load  R2 , mem[x,1];
ADD R3 , R1 , R2 ;
BEQZ R3 , ELSE1

#Block
Load  R4 , 10;
Load  R5 , 10;
ADD R6 , R4 , R5 ;
Load  R1 , 20;
Load  R2 , mem[x,1];
ADD R3 , R1 , R2 ;
#
ELSE1:
Load  R1 , 5;
BEQZ R1 , ELSE2
JUMP IF3
ELSE2:

#Block
Push z
Load  R2 , mem[x,2];
Load  R3 , mem[z,1];
ADD R4 , R2 , R3 ;
Pop z
#
IF3: 
LOOP4: 

#Block
Load  R1 , 1;
BEQZ R1 , ELSE5
ELSE5:
Load  R1 , 4;
Load  R2 , mem[x,1];
ADD R3 , R1 , R2 ;
STORE R3 , mem[x , 1] ;
#
Load  R1 , 2;
BEQZ R1 , LOOP4
Load  R1 , 4;
Load  R2 , 3;
ADD R3 , R1 , R2 ;
Load  R4 , 2;
ADD R5 , R3 , R4 ;
Load  R6 , 1;
ADD R7 , R5 , R6 ;
Pop x
Pop y
#
