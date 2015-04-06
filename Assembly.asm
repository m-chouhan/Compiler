
#Block
Push i #Byte# ;
Push x #Double# ;
Push y #Double# ;
Push z #Integer# ;
Push zz #Double# ;
Load  R1 , 10.5 #Double# ;
Load  R1 , 4 #Integer# ;
Load  R2 , mem[x,3, #Double# ];
DIV R3 #Double#  , R1 #Integer#  , R2 #Double#  ;
STORE R3 #Double#  , mem[y , 2, #Double# ] ;

#Block
Push z #Byte# ;
Load  R1 , 51 #Byte# ;
STORE R1 #Byte#  , mem[z , 1, #Byte# ] ;
Load  R1 , 53 #Byte# ;
STORE R1 #Byte#  , mem[z , 1, #Byte# ] ;
Pop z;
#
Load  R1 , 0 #Integer# ;
Load  R2 , mem[i,5, #Byte# ];
DIV R3 #Integer#  , R1 #Integer#  , R2 #Byte#  ;
BEQZ R3 , ELSE1

#Block
Load  R4 , 49 #Byte# ;
Load  R5 , mem[i,5, #Byte# ];
ADD R6 #Byte#  , R4 #Byte#  , R5 #Byte#  ;
STORE R6 #Byte#  , mem[i , 5, #Byte# ] ;
#
JUMP IF2
ELSE1:

#Block
Load  R1 , 49 #Byte# ;
Load  R2 , mem[i,5, #Byte# ];
SUB R3 #Byte#  , R1 #Byte#  , R2 #Byte#  ;
STORE R3 #Byte#  , mem[i , 5, #Byte# ] ;
#
IF2: 
LOOP3: 

#Block
Load  R1 , 0 #Integer# ;
Load  R2 , mem[i,5, #Byte# ];
DIV R3 #Integer#  , R1 #Integer#  , R2 #Byte#  ;
BEQZ R3 , ELSE4

#Block
Load  R4 , mem[y,2, #Double# ];
STORE R4 #Double#  , mem[x , 3, #Double# ] ;
#
ELSE4:
#
Load  R1 , mem[x,3, #Double# ];
BEQZ R1 , LOOP3
Pop i;
Pop x;
Pop y;
Pop z;
Pop zz;
#
