#include <string.h>
#include <stdio.h>
#include <stdlib.h>
struct quadr {
	char* opr;
	char* op1;
	char* op2;
	char* res;
};

struct quadr qu[100];


int ind = 0,indBR;

void init()
{
	int i;
	for(i=0;i<100;i++)
	{
		struct quadr q = {NULL};
		qu[i] = q;
	}
}

void create(char* opr,char* op1,char* op2,char* res)
{
	qu[ind].opr = strdup(opr);
	qu[ind].op1 = strdup(op1);
	qu[ind].op2 = strdup(op2);
	qu[ind].res = strdup(res);
	ind++;
}

// convertir int en chaine
char* convert(int i){
	char s[15];
	sprintf(s,"%d",i);
	return strdup(s);
}

//quad pour les comparaisons
void quadComp(char* opr)
{
	//create(opr,op1,op2,"");
	
	if( strcmp(opr,"==")==0)
	{
		create("BNZ","","","");
	}else
	{
		if( strcmp(opr,"!=")==0)
	{
		create("BZ","","","");
	}else
	{
		if( strcmp(opr,">")==0)
	{
		create("BLE","","","");
	}else
	{
		if( strcmp(opr,"<")==0)
	{
		create("BGE","","","");
	}else
	{
		if( strcmp(opr,">=")==0)
	{
		create("BL","","","");
	}else
	{
		if( strcmp(opr,"<=")==0)
	{
		create("BG","","","");
	}	}	}	}	}	}	
	
	indBR = ind-1;
}
// quad de la fin d If
void quadFinIF()
{
	strcpy(qu[indBR].op1,convert(ind));
}




void afficherQuad()
{
    printf("*********************Quadruplet***********************\n");
    int i;
    for(i=0;i<ind;i++)
		{
            printf("\n %d - ( %s  ,  %s  ,  %s  ,  %s )",i,qu[i].opr,qu[i].op1,qu[i].op2,qu[i].res);
            printf("\n---------------------------------------------------\n");
        }
    printf("*********************FIN Quadruplet***********************\n");
}