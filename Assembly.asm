
#Block
Push x #Double# 
Push y #INTEGER# 
Push z #INTEGER# 
Load  R1 , 10.5 #Double# ;
Load  R1 , 4 #INTEGER# ;
Load  R2 , mem[x,3, #Double# ];
STORE R2 #Double#  , mem[y , 1, #INTEGER# ] ;
DIV 3 #INTEGER#  , R1 #INTEGER#  , R2undef ;

#Block
Push z #BYTE# 
Load  R1 , 10 #INTEGER# ;
STORE R1 #INTEGER#  , mem[z , 1, #BYTE# ] ;
Load  R1 , 53 #BYTE# ;
STORE R1 #BYTE#  , mem[z , 1, #BYTE# ] ;
Pop z
#
Pop x
Pop y
Pop z
#
