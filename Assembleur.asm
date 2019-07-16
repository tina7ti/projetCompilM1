DATA SEGMENt 
Ojjsd DD ?
Plkjd DD ?
Xx DD ?
Yy DD ?
Zz DD ?
Ol DD ?
At DD ?
OMM DD ?
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
etiq5 : MOV Ol, -66
etiq6 : JMP etiq9
etiq7 : MOV AX, 95
	 ADD AX, 354
etiq8 : MOV At, AX
etiq9 : MOV OMM, Ma
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
