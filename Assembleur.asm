DATA SEGMENt 
Ihjdhs DD ?
Ujjsd DD ?
Plkjd DD ?
Xx DD ?
Yy DD ?
Zz DD ?
At DD ?
DATA ENDS
CODE SEGEMENt
ASSUME CS:CODE, DS:DATA
MAIN :
MOV AX,DATA
MOV DS,AX
etiq0 : MOV Ihjdhs, 5764
etiq1 : MOV Ujjsd, Plkjd
etiq2 : MOV Xx, 0
etiq3 : MOV AX, 95
	 ADD AX, 354
etiq4 : MOV Zz, AX
etiq5 : MOV AX, Lo
	CMP AX, 9
	JNE etiq8
etiq6 : MOV Yy, 63
etiq7 : MOV At, 6
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
