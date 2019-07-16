DATA SEGMENt 
Ivpr1 DD ?
PromoIv DD ?
Ivpromo DD ?
Ivfirst DD ?
Ivpr18 DD ?
Ivpr19 DD ?
Bestpr DD ?
Ivpr19my DD ?
Ivpr20 DD ?
DATA ENDS
CODE SEGEMENt
ASSUME CS:CODE, DS:DATA
MAIN :
MOV AX,DATA
MOV DS,AX
etiq0 : MOV Ivpromo, 2019
etiq1 : MOV Ivfirst, 2016
etiq2 : MOV AX, 2016
	 ADD AX, 2
etiq3 : MOV Ivpr18, AX
etiq4 : MOV AX, 2019
	CMP AX, Ivpr19
	JNE etiq4
etiq5 : JMP etiq8
etiq6 : MOV AX, 2019
CMP AX, Ivpr20
	JL etiq8
etiq7 : MOV AX, 2019
	CMP AX, Ivpr19
	JLE etiq8
FIN :
MOV AH,4CH
INt 21h
CODE ENDS
END MAIN
