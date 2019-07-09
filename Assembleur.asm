DATA SEGMENt 
Ihjdhs DD ?
Ujjsd DD ?
Plkjd DD ?
Ohds DD ?
Pokl DD ?
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
etiq6 : MOV Pokl, 526
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
