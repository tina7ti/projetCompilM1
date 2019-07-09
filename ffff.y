%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
#include "fonct.h"
#include "quad.c"
int yylex();
int yyerror(char * msg);
extern int line;
extern int col;
extern int esp;
int esp1 = 0;
char* sauvComp="";
int ntemp=1; char tempC[12]=""; 
%}

%union
{
char* n;
int e;
struct {int type;char* val;}NT;
}

%token <n>idf <e>entier <n>reel <n>caract mc_if mc_elif mc_else mc_while mc_for in range mc_int mc_float mc_char add sub mul divis <n>eg <n>infoueg <n>supoueg <n>sup <n>inf <n>diff <n>or <n>and 
%token ':' '[' ']' '(' ')' '='
%left or and
%left eg infoueg supoueg sup inf diff
%left add sub
%left mul divis
%type<NT> EXP 
%type<n> OP CO
%type<NT> COMP DIVI


%start S
%%
S : INST {printf(" \n programme syntaxiquement juste \n");YYACCEPT;}
;
INST : AFFEC INST | EXP INST | COND INST | AFFEC | EXP | COND 
;
AFFEC : idf '=' idf {create("=",$3," ",$1);}
	| idf '=' entier {create("=",convert($3)," ",$1);}
	| idf '=' EXP {create("=",$3.val," ",$1);}
;
COND : mc_if '(' COMP ')' INST { esp1++; if(esp1 != esp) printf("error de if"); quadFinIF();}
	| mc_if '(' COMP ')' INST mc_elif '(' COMP ')' INST
;
COMP : idf CO idf { create(sauvComp,$1,$3,""); quadComp(sauvComp); }
	| idf CO entier { create(sauvComp,$1,convert($3),""); quadComp(sauvComp);}
	| entier CO idf {  create(sauvComp,convert($1),$3,""); quadComp(sauvComp);}
;
CO : eg { sauvComp = "=="; }
	| infoueg { sauvComp = "<=";}
	| supoueg { sauvComp = ">=";}
	| diff { sauvComp = "!=";}
	| sup { sauvComp = ">";}
	| inf { sauvComp = "<";}
;
EXP : idf OP idf 
	| entier OP entier
	| idf OP entier 
	| DIVI 
;
OP : add 
	| sub 
	| mul 
;
DIVI : idf divis entier  {if ($3==0) {printf("erreur a la ligne %d colonne %d : division par zero interdit\n", line,col);}else{create("/",$1,convert($3),$$.val);}} 	
	| entier divis entier {if ($3==0){ printf("erreur a la ligne %d colonne %d: division par zero interdit\n", line,col);}else{create("/",convert($1),convert($3),$$.val);}} 	
	| idf divis idf {if ($3==0){ printf("erreur a la ligne %d colonne %d: division par zero interdit\n", line,col);}else{create("/",$1,$3,$$.val);}} 
;
%%
int yyerror(char* msg){

	printf("%s : ligne : %d , colonne : %d\n",msg,line,col);
	exit(EXIT_FAILURE);
}
int main()
{
init();
yyin=fopen("test.txt","r");
yyparse();
fclose(yyin);
printf("\n\n");
printf("-----------------AFFICHER LES QUAD------------------------------ ");
printf("\n\n");
afficherQuad();
}




