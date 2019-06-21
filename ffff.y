%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
#include "fonct.h"
int yylex();
int yyerror(char * msg);
extern int line;
extern int col;
int nTemp=1; char tempC[12]=""; 
%}

%union
{
char * n;
int e;
struct {int type;char* res;}NT;
}

%token <n>idf <e>entier <n>reel <n>caract mc_if mc_elif mc_else mc_while mc_for in range mc_int mc_float mc_char supinf add sub mul divis eg infoueg supoueg diff or and saut espace
%token ':' '[' ']' '(' ')' '='
%left or and
%left eg infoueg supoueg diff
%left add sub
%left mul divis

%start S
%%
S : INST {printf(" \n programme syntaxiquement juste \n"); YYACCEPT;}
;
INST : AFFEC INST | EXP INST | COND INST | AFFEC | EXP | COND 
;
AFFEC : idf '=' idf | idf '=' entier | idf '=' EXP 
;
COND : mc_if '(' COMP ')' saut espace INST
	| mc_if '(' COMP ')' saut espace INST saut espace mc_elif '(' COMP ')' saut espace INST
;
COMP : idf CO idf 
	| idf CO entier
;
CO : eg | supinf | infoueg |supoueg | diff
;
EXP : idf OP idf | entier OP entier| idf OP entier | DIVI 
;
OP : add | sub | mul 
;
DIVI : idf divis entier  {if ($3==0) {printf("erreur a la ligne %d colonne %d : division par zero interdit\n", line,col);}} 	| entier divis entier {if ($3==0){ printf("erreur a la ligne %d colonne %d: division par zero interdit\n", line,col);}} 	| idf divis idf  
;
%%
int main()
{
yyin=fopen("test.txt","r");
yyparse();
fclose(yyin);
}
int yyerror(char* msg){

	printf("%s : ligne : %d , colonne : %d\n",msg,line,col);
	exit(EXIT_FAILURE);
}
