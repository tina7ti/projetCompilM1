DATA SEGMENt 
Uyhd DD ?
Xx DD ?
Yy DD ?
Zz DD ?
Aa DD ?
Bb DD ?
Pxe DD ?
DATA ENDS
CODE SEGEMENT
ASSUME CS:CODE, DS:DATA
MAIN :
etiq0 : MOV Zz, 2
etiq1 : MOV AX, Pob
	CMP AX, 6
	JGE etiq5
etiq2 : MOV AX, 77
	CMP AX, 77
	JNE etiq5
etiq3 : MOV AX, 4
	 ADD AX, 4
etiq4 : ADD AX, 4
etiq5 : MOV Zz, AX
etiq6 : MOV AX, 321
	CMP AX, Zz
	JE etiq8
etiq7 : JMP etiq10
etiq8 : MOV AX, Mlk
CMP AX, 5
	JL etiq9
etiq9 : JMP etiq10
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
