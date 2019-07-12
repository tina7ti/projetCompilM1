%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
#include "fonct.c"
#include "quad.c"
int yylex();
int yyerror(char * msg);
extern int line;
extern int col;
extern int esp;
int esp1 = 0,ielse,ielif,iBR=0;
int tabBR[20];
char* sauvComp="";
int ntemp=1; char tempC[12]=""; 
%}

%union
{
char* n;
int e;
struct {int type;char* val;}NT;
}

%token <n>idf <n>entier <n>reel <n>caract mc_if mc_elif mc_else mc_while mc_for in range mc_int mc_float mc_char add sub mul divis <n>eg <n>infoueg <n>supoueg <n>sup <n>inf <n>diff <n>or <n>and <n>tab <n>saut 
%token ':' '[' ']' '(' ')' '='
%left or and
%left eg infoueg supoueg sup inf diff
%left add sub
%left mul divis
%type<n> EXP 
%type<n> CO
%type<NT> COMP


%start S
%%
S : INST {printf(" \n programme syntaxiquement juste \n");YYACCEPT;}
;
INST : AFFEC INST | EXP INST | COND INST | AFFEC | EXP | COND | saut INST | saut
;
AFFEC : idf '=' idf saut { inserer($1); inserer($3); create("=",$3," ",$1);} 
	| idf '=' entier saut { inserer($1); create("=",$3," ",$1);} 
	| idf '=' EXP saut {inserer($1); create("=",$3," ",$1);} 
;
COND : mc_if '(' COMP ')' ':' saut INST { esp1++; quadFinIF(); esp1--;}
	| mc_if '(' COMP ')' ':' saut INST mc_else ':' saut {create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielse = ind; quadFinIF_else(ielse);} INST {  } 
	| mc_if '(' COMP ')' ':' saut INST mc_elif { create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielif = ind; quadFinIF_else(ielif);} '(' COMP ')' ':' saut INST mc_else ':' saut {create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielse = ind; quadFinIF_else(ielse);} INST {  }
;
COMP : idf CO idf {  quadComp(sauvComp,$1,$3); }
	| idf CO entier {  quadComp(sauvComp,$1,$3);}
	| entier CO idf {   quadComp(sauvComp,$1,$3);}
	| entier CO entier {   quadComp(sauvComp,$1,$3);}
;
CO : eg { sauvComp = "=="; }
	| infoueg { sauvComp = "<=";}
	| supoueg { sauvComp = ">=";}
	| diff { sauvComp = "!=";}
	| sup { sauvComp = ">";}
	| inf { sauvComp = "<";}
;
EXP : EXP add EXP {$1=strdup($$);sprintf($$, "t%d", ntemp); create("+",$1,$3,$$); ntemp++;}
	| EXP sub EXP {$1=strdup($$);sprintf($$, "t%d", ntemp); create("-",$1,$3,$$); ntemp++;}
	| EXP mul EXP {$1=strdup($$);sprintf($$, "t%d", ntemp); create("*",$1,$3,$$); ntemp++;}
	| EXP divis EXP {$1=strdup($$);sprintf($$, "t%d", ntemp); create("/",$1,$3,$$); ntemp++;}
	| idf { sprintf($$,"%s",$1); }
	| entier { sprintf($$,"%s",$1); }
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
afficher();
printf("\n \n");
printf("------------- AFFICHER LES QUAD (avant opti)----------------------- ");
printf("\n\n");
afficherQuad();
printf("\n\n");
int t = taille();
assembler(t);

}




