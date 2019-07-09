DATA SEGMENt 
Ihjdhs DD ?
Ujjsd DD ?
Plkjd DD ?
Ohds DD ?
Mk DD ?
Po DD ?
Pml DD ?
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
	JG etiq7
etiq3 : MOV AX, Gjd
	 ADD AX, Ojh
etiq4 : SUB AX, 5795
etiq5 : MOV Ohds, AX
etiq6 : JMP etiq
etiq7 : MOV AX, 3
	CMP AX, 9
	JGE etiq12
etiq8 : MOV AX, 3
	DIV AX, 1
etiq9 : ADD AX, 9
etiq10 : MOV Mk, AX
etiq11 : JMP etiq
etiq12 : MOV Po, 6666
etiq13 : MOV Pml, 99
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
