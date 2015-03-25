Load  R1 , 10;
Load  R1 , 20;
Load  R1 , 5;
Load  R2 , symbolTable[23];
ADD R3 , R1 , R2 ;
Load  R1 , 15;
Load  R2 , symbolTable[23];
ADD R3 , R1 , R2 ;
BEQZ R3 , Lable0
Load  R4 , 10;
Load  R5 , 10;
ADD R6 , R4 , R5 ;
Lable0:
Load  R1 , 5;
BEQZ R1 , Lable1
JUMP Lable2
Lable1:
Load  R2 , symbolTable[25];
Lable2: 
Lable: 
Load  R1 , 1;
BEQZ R1 , Lable3
Lable3:
Load  R1 , 2;
BEQZ R1 , Lable
Load  R1 , 4;
Load  R2 , 3;
ADD R3 , R1 , R2 ;
Load  R4 , 2;
ADD R5 , R3 , R4 ;
Load  R6 , 1;
ADD R7 , R5 , R6 ;
