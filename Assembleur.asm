DATA SEGMENt 
Ojjsd DD ?
Plkjd DD ?
Xx DD ?
Yy DD ?
Zz DD ?
Ol DD ?
Tfd DD ?
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
etiq6 : JMP etiq8
etiq7 : MOV Tfd, Yy
etiq8 : MOV AX, 95
	 ADD AX, 354
etiq9 : MOV At, AX
etiq10 : MOV OMM, Ma
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
