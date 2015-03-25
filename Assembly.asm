
#Block
Push x
Push y
Load  R1 , 10;

#Block
Push z
Load  R1 , 5;
Load  R2 , search[z,0];
ADD R3 , R1 , R2 ;
Pop
#
Load  R1 , 2;
Load  R2 , search[y,0];
ADD R3 , R1 , R2 ;
LOOP1: 

#Block
Push z
Load  R1 , 123;
Load  R2 , search[z,0];
ADD R3 , R1 , R2 ;
Pop
#
Load  R1 , 2;
BEQZ R1 , LOOP1
Load  R1 , 4;
Load  R2 , 3;
ADD R3 , R1 , R2 ;
Load  R4 , 2;
ADD R5 , R3 , R4 ;
Load  R6 , 1;
ADD R7 , R5 , R6 ;
Pop
Pop
#
