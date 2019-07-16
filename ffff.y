%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE* yyin;
#include "fonct.c"
#include "quad.c"
int yylex();
int yyerror(char * msg);
void if_error(int nvind,int nbtab,int aumoins1);
void majIND(int* nvind,int nbtab,int* aumoins1,int intab);
extern int line;
extern int col;
extern int nbtab;
extern int nvind;
extern int majVide;
extern int nbelse;
int nbinst=0,ielse,ielif,iBR=0,inif=0;
int tabBR[20];
char* sauvComp="";
int ntemp=1; char tempC[12]=""; 
int aumoins1=0;
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
INST : DEC sa INST | AFFEC sa INST | COND INST | DEC | AFFEC | COND | sa INST | sa | COMMENTS 
	| COMMENTS INST | TABU DEC INST | TABU DEC | TABU AFFEC INST | TABU AFFEC | TABU COND INST | TABU COND
;
sa : saut { nbtab=0;}
;
TABU : tab { if(aumoins1==0 && nvind ==0) { yyerror("Tabulation inattendu "); }else
{if(nvind != nbtab && aumoins1==0 && nvind >0){ yyerror("Tabulation attendu apres les ':' ");}else { if(nvind !=0 && aumoins1==0 && nbtab==nvind)aumoins1=1;} }
majIND(&nvind,nbtab,&aumoins1,1); }
;
DEC : mc_int VARS {  if_error(nvind,nbtab,aumoins1); majIND(&nvind,nbtab,&aumoins1,0);}
;
VARS : idf { inserer($1); }
	| VARS ',' idf { inserer($3); }
	| idf '=' MEMdr { inserer($1); create("=",$3," ",$1); }
	| VARS ',' idf '=' MEMdr { inserer($3); create("=",$5," ",$3); }
;
MEMdr : idf {inserer($1);} | entier | EXP 
;
COMMENTS : comment sa | comment | comment COMMENTS
;
AFFEC : idf '=' idf {  if_error(nvind,nbtab,aumoins1); majIND(&nvind,nbtab,&aumoins1,0); inserer($1); inserer($3); create("=",$3," ",$1); } 
	| idf '=' entier { if_error(nvind,nbtab,aumoins1); majIND(&nvind,nbtab,&aumoins1,0); inserer($1); create("=",$3," ",$1); } 
	| idf '=' EXP { if_error(nvind,nbtab,aumoins1); majIND(&nvind,nbtab,&aumoins1,0); inserer($1); create("=",$3," ",$1);} 
;
COND : IF_SEUL | IF_ELSE | IF_ELIF
; 
IF_SEUL : mc_if '(' COMP ')' ':' sa INST { }
;
IF_ELSE : mc_if '(' COMP ')' ':' sa INST mc_else ':' sa {create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielse = ind; quadFinIF_else(ielse);} INST {  } 
;
IF_ELIF : mc_if '(' COMP ')' ':' sa INST mc_elif { create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielif = ind; quadFinIF_else(ielif);} '(' COMP ')' ':' sa INST mc_else ':' sa {create("BR","","",""); tabBR[iBR]=ind-1; iBR++; ielse = ind; quadFinIF_else(ielse);} INST {  }
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
void if_error(int nvind,int nbtab,int aumoins1)
{
	if(nvind != nbtab && aumoins1==0)
		{ yyerror("Tabulation attendu apres les ':' ");
	}
}
void majIND(int* nvind,int nbtab,int* aumoins1,int intab)
{
	if (intab==1)
	{
		if( nbtab < *nvind && aumoins1 != 0)	
			{ /*printf(" %d ",nbtab);*/
			 *nvind--; *aumoins1=0;  }
	}else
	{
	if( nbtab ==0 && nvind != 0 && aumoins1 != 0 && majVide==0)	
			{
	*nvind = 0;
	*aumoins1=0;
	majBR_vide();
	majVide =1;
	}
	}
	
}
int main()
{
init();
yyin=fopen("test.txt","r");
yyparse();
fclose(yyin);
printf("\n\n");
afficher();
quad_fin();
printf("\n \n");
printf("------------- AFFICHER LES QUAD (avant opti)----------------------- ");
printf("\n\n");
afficherQuad();
printf("\n\n");
printf("------------- AFFICHER LES QUAD (apres opti)----------------------- ");
printf("\n\n");
optimiser();
int t = taille();
assembler(t);

}




