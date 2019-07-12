DATA SEGMENt 
Ihjdhs DD ?
Ujjsd DD ?
Plkjd DD ?
Ohds DD ?
Gjd DD ?
Mk DD ?
Po DD ?
Pml DD ?
Mlk DD ?
DATA ENDS
CODE SEGEMENt
ASSUME CS:CODE, DS:DATA
MAIN :
MOV AX,DATA
MOV DS,AX
etiq0 : MOV Ihjdhs, 5764
etiq1 : MOV Ujjsd, Plkjd
etiq2 : MOV AX, Upm88
	CMP AX, Pml
	JG etiq5
etiq3 : MOV Ohds, Gjd
etiq4 : JMP etiq
etiq5 : MOV AX, 3
	CMP AX, 9
	JGE etiq8
etiq6 : MOV Mk, 9
etiq7 : JMP etiq
etiq8 : MOV Po, 6666
etiq9 : MOV Pml, 99
etiq10 : MOV Mlk, 111
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
