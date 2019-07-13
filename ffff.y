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
extern int nbtab;
int nvind = 0,nbinst=0,ielse,ielif,iBR=0,inif=0;
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

%token <n>idf <n>entier <n>reel <n>caract mc_if mc_elif mc_else mc_while mc_for in range mc_int mc_float mc_char add sub mul divis <n>eg <n>infoueg <n>supoueg <n>sup <n>inf <n>diff <n>or <n>and <n>saut <n>comment <n>tab
%token ':' '[' ']' '(' ')' '=' ','
%left or and
%left eg infoueg supoueg sup inf diff
%left add sub
%left mul divis
%type<n> EXP MEMdr
%type<n> CO 
%type<NT> COMP


%start S
%%
S : INST {printf(" \n programme syntaxiquement juste \n");YYACCEPT;}
;
INST : DEC INST | AFFEC INST | EXP INST | COND INST | DEC | AFFEC | EXP | COND | saut INST | saut | COMMENTS 
	| COMMENTS INST | TABU DEC INST | TABU DEC | TABU AFFEC INST | TABU AFFEC | TABU COND INST | TABU COND
;
TABU : tab { if(nbinst==0 && nbtab==0 && nvind !=0) printf("erroorrr"); }
;
DEC : mc_int VARS saut 
;
VARS : idf { inserer($1); }
	| VARS ',' idf { inserer($3); }
	| idf '=' MEMdr { inserer($1); create("=",$3," ",$1); }
	| VARS ',' idf '=' MEMdr { inserer($3); create("=",$5," ",$3); }
;
MEMdr : idf {inserer($1);} | entier | EXP 
;
COMMENTS : comment saut | comment | comment COMMENTS
;
AFFEC : idf '=' idf saut { inserer($1); inserer($3); create("=",$3," ",$1); }
	| idf '=' idf { inserer($1); inserer($3); create("=",$3," ",$1); } 
	| idf '=' entier saut { inserer($1); create("=",$3," ",$1); } 
	| idf '=' EXP saut { inserer($1); create("=",$3," ",$1);} 
;
COND : IF_SEUL | IF_ELSE | IF_ELIF
; 
IF_SEUL : mc_if '(' COMP ')' ':' saut INST {nvind--;}
;
IF_ELSE : mc_if '(' COMP ')' ':' saut INST mc_else ':' saut {create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielse = ind; quadFinIF_else(ielse);} INST {  } 
;
IF_ELIF : mc_if '(' COMP ')' ':' saut INST mc_elif { create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielif = ind; quadFinIF_else(ielif);} '(' COMP ')' ':' saut INST mc_else ':' saut {create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielse = ind; quadFinIF_else(ielse);} INST {  }
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




