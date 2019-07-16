DATA SEGMENt 
Ojjsd DD ?
Plkjd DD ?
Xx DD ?
Yy DD ?
Zz DD ?
OMM DD ?
Maa DD ?
At DD ?
Ma DD ?
DATA ENDS
CODE SEGEMENt
ASSUME CS:CODE, DS:DATA
MAIN :
MOV AX,DATA
MOV DS,AX
etiq0 : MOV Ojjsd, Plkjd
etiq1 : MOV Xx, 0
etiq2 : MOV AX, 95
	 ADD AX, 354
etiq3 : MOV Zz, AX
etiq4 : MOV AX, Lo
	CMP AX, 9
	JNE etiq7
etiq5 : MOV AX, 98
	CMP AX, 5
	JGE etiq7
etiq6 : MOV OMM, Maa
etiq7 : MOV At, AX
etiq8 : MOV OMM, Ma
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
