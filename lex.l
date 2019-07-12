%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ffff.tab.h"
#include "fonct.h"
#include "quad.h"
extern YYSTYPE yylval;
int line=1,col=1;
int esp=0;
char* p1;
char ss[50]={ 0 };
%}

lettre [a-zA-Z]
chiffre [0-9]
idf [A-Z]({lettre}|{chiffre})*
entier ((0|[1-9]{chiffre}*)|"("[+-](0|[1-9]{chiffre}*)")")
reel ((0|[1-9]{chiffre}*)"."{chiffre}+|"("[+-](0|[1-9]{chiffre}*)"."{chiffre}+")")
caract  '.'
comment "#"(.)*
espace (" ")+
tab ("\t")
saut ("\n")+

%%
if {  col+=yyleng; return mc_if;}
elif {col+=yyleng; return mc_elif; }
else {col+=yyleng; return mc_else;}
while {col+=yyleng; return mc_while;}
for {col+=yyleng; return mc_for;}
in {col+=yyleng; return in;}
range {col+=yyleng; return range;}
int {col+=yyleng; return mc_int;}
float {col+=yyleng; return mc_float;}
char {col+=yyleng; return mc_char;}
{idf} {if(yyleng > 8) {printf("erreur lexicale : \" %s \" \n ligne : %d colonne : %d\n l'identificateur ne doit pas depasser 8 caracteres ! \n",yytext,line,col); yyterminate();} 
      else{col+=yyleng; yylval.n=strdup(yytext); return idf; } }
{entier} { if (yytext[0]=='('){ p1 = yytext; strncpy(ss,p1+1,yyleng-2);} else{strcpy(ss,yytext);}
		 if((atoi(ss)<32767) && (atoi(ss)>-32768 )){col+=yyleng; yylval.n=strdup(ss); return entier;}else {printf("erreur lexicale : \" %s \" \n ligne : %d colonne : %d\n l'entier doit etre entre -32768 et 32767 ! \n",ss,line,col); yyterminate();} }
{reel} {col+=yyleng; yylval.n=strdup(yytext); return reel;}
{caract} {col+=yyleng; yylval.n=strdup(yytext); return caract;}
[:[\]()=] {col+=yyleng; return yytext[0];}
"+" {return add;}
"-" {return sub;}
"*" {return mul;}
"/" {return divis;}
"==" {return eg;}
"<=" {return infoueg;}
">=" {return supoueg;}
">" {return sup;}
"<" {return inf;}
"!=" {return diff;}
or {return or;}
and {return and;}
{comment}
{espace} {col+=yyleng;}
{tab} {col+=yyleng; esp++; yylval.n=strdup(yytext); return tab;}
{saut} {col=1; line+=yyleng; if(esp>0) esp--; yylval.n=strdup(yytext); return saut; }

. {printf("erreur lexicale : \" %s \" \n ligne : %d colonne : %d \n",yytext,line,col); yyterminate();}
%%
int yywrap() {return 1;}
