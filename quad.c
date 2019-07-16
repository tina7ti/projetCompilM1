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
void quadComp(char* opr,char* op1, char* op2)
{
	//create(opr,op1,op2,"");
	
	if( strcmp(opr,"==")==0)
	{
		create("BNE","",op1,op2);
	}else
	{
		if( strcmp(opr,"!=")==0)
	{
		create("BE","",op1,op2);
	}else
	{
		if( strcmp(opr,">")==0)
	{
		create("BLE","",op1,op2);
	}else
	{
		if( strcmp(opr,"<")==0)
	{
		create("BGE","",op1,op2);
	}else
	{
		if( strcmp(opr,">=")==0)
	{
		create("BL","",op1,op2);
	}else
	{
		if( strcmp(opr,"<=")==0)
	{
		create("BG","",op1,op2);
	}	}	}	}	}	}	
	
	indBR = ind-1;
}
// quad de la fin d If
void quadFinIF()
{
	strcpy(qu[indBR].op1,convert(ind));
}

void quadFinIF_else(int ielse)
{
	strcpy(qu[indBR].op1,convert(ielse));
}


void afficherQuad()
{
    printf("************* Quadruplet ***************\n\n");
    int i;
    for(i=0;i<ind;i++)
		{
            printf("  %d - ( %s  ,  %s  ,  %s  ,  %s )",i,qu[i].opr,qu[i].op1,qu[i].op2,qu[i].res);
            printf("\n----------------------------------------\n");
        }
    printf("\n*********** FIN Quadruplet *************\n");
}
// maj des brachements vides
void majBR_vide()
{
	int i;
    for(i=0;i<ind;i++)
		{
			if(qu[i].opr[0]=='B' && strcmp(qu[i].op1,"")==0)
			{
				strcpy(qu[i].op1,convert(ind));
			}
		}

}

// code : assembleur

void assembler(int CptabSym){

	FILE* f;
	f = fopen("Assembleur.asm","w");
	int i;
	fprintf(f,"DATA SEGMENt \n");
	for(i=0;i<CptabSym;i++){
		fprintf(f,"%s DD ?\n",ts[i].NomEntite);
	}
	fprintf(f,"DATA ENDS\n");
	fprintf(f,"CODE SEGEMENt\n");
	fprintf(f,"ASSUME CS:CODE, DS:DATA\n");
	fprintf(f,"MAIN :\n");
	fprintf(f,"MOV AX,DATA\n");
	fprintf(f,"MOV DS,AX\n");
	for(i=0;i<ind;i++){
		fprintf(f,"etiq%d : ",i);
		if(strcmp(qu[i].opr,"+")==0){
			if((qu[i].op1[0]=='t')&&(qu[i].op2[0]=='t')){
				fprintf(f,"ADD AX, BX\n");
			}
			else{
				if(qu[i].op1[0]=='t'){
					fprintf(f,"ADD AX, %s\n",qu[i].op2);
				}
				else
				{
					if(qu[i].op2[0]=='t'){
					fprintf(f,"ADD AX, %s\n",qu[i].op1);
					}
					else{
						fprintf(f,"MOV AX, %s\n",qu[i].op1);
						fprintf(f,"\t ADD AX, %s\n",qu[i].op2);
					}
				}
			}

		}
		if(strcmp(qu[i].opr,"-")==0){
			if((qu[i].op1[0]=='t')&&(qu[i].op2[0]=='t')){
				fprintf(f,"SUB AX, BX\n");
			}

			else{
				if(qu[i].op1[0]=='t'){
					fprintf(f,"SUB AX, %s\n",qu[i].op2);
				}else
				{
					if(qu[i].op2[0]=='t'){
					fprintf(f,"SUB AX, %s\n",qu[i].op1);
					}
					else{
						fprintf(f,"MOV AX, %s\n",qu[i].op1);
						fprintf(f,"\tSUB AX, %s\n",qu[i].op2);
					}
				}
				
			}

		}
	if(strcmp(qu[i].opr,"*")==0){
			if((qu[i].op1[0]=='t')&&(qu[i].op2[0]=='t')){
				fprintf(f,"MUL AX, BX\n");
			}
			else{
				if(qu[i].op1[0]=='t'){
					fprintf(f,"MUL AX, %s\n",qu[i].op2);
				}
				else
				{
					if(qu[i].op2[0]=='t'){
					fprintf(f,"MUL AX, %s\n",qu[i].op1);
					}
					else{
						fprintf(f,"MOV AX, %s\n",qu[i].op1);
						fprintf(f,"\t MUL AX, %s\n",qu[i].op2);
					}
				}
			}

	}
	if(strcmp(qu[i].opr,"/")==0){
			if((qu[i].op1[0]=='t')&&(qu[i].op2[0]=='t')){
				fprintf(f,"DIV AX, BX\n");
			}
			else{
				if(qu[i].op1[0]=='t'){
					fprintf(f,"DIV AX, %s\n",qu[i].op2);
				}
				else
				{
					if(qu[i].op2[0]=='t'){
					fprintf(f,"DIV AX, %s\n",qu[i].op1);
					}
					else{
						fprintf(f,"MOV AX, %s\n",qu[i].op1);
						fprintf(f,"\tDIV AX, %s\n",qu[i].op2);
					}
				}
			}

	}
	if(strcmp(qu[i].opr,"BR")==0){
		fprintf(f,"JMP etiq%s\n",qu[i].op1);
	}
	if(strcmp(qu[i].opr,"BG")==0){
		fprintf(f, "MOV AX, %s\n",qu[i].op2 );
		fprintf(f,"\tCMP AX, %s\n",qu[i].res);
		fprintf(f,"\tJG etiq%s\n",qu[i].op1);
	}
	if(strcmp(qu[i].opr,"BGE")==0){
		fprintf(f, "MOV AX, %s\n",qu[i].op2 );
		fprintf(f,"\tCMP AX, %s\n",qu[i].res);
		fprintf(f,"\tJGE etiq%s\n",qu[i].op1);
	}
	if(strcmp(qu[i].opr,"BL")==0){
		fprintf(f, "MOV AX, %s\n",qu[i].op2 );
		fprintf(f,"CMP AX, %s\n",qu[i].res);
		fprintf(f,"\tJL etiq%s\n",qu[i].op1);
	}
	if(strcmp(qu[i].opr,"BLE")==0){
		fprintf(f, "MOV AX, %s\n",qu[i].op2 );
		fprintf(f,"\tCMP AX, %s\n",qu[i].res);
		fprintf(f,"\tJLE etiq%s\n",qu[i].op1);
	}
	if(strcmp(qu[i].opr,"BE")==0){
		fprintf(f, "MOV AX, %s\n",qu[i].op2 );
		fprintf(f,"\tCMP AX, %s\n",qu[i].res);
		fprintf(f,"\tJE etiq%s\n",qu[i].op1);
	}
	if(strcmp(qu[i].opr,"BNE")==0){
		fprintf(f, "MOV AX, %s\n",qu[i].op2 );
		fprintf(f,"\tCMP AX, %s\n",qu[i].res);
		fprintf(f,"\tJNE etiq%s\n",qu[i].op1);
	}
	if(strcmp(qu[i].opr,"=")==0){
		if(qu[i].op1[0]=='t'){
			fprintf(f,"MOV %s, AX\n",qu[i].res);
		}
		else fprintf(f,"MOV %s, %s\n",qu[i].res,qu[i].op1);
	}
}
	fprintf(f,"FIN :\n");
	fprintf(f,"MOV AH,4CH\n");
	fprintf(f,"INt 21h\n");
	fprintf(f,"CODE ENDS\n");
	fprintf(f,"END MAIN\n");
}


void simplfyMulti(){
	int i;

	for(i=0;i<ind;i++){
			if(strcmp(qu[i].opr,"*")==0  ){
				if(strcmp(qu[i].op1,"2")==0){
					strcpy(qu[i].opr,"+");
					strcpy(qu[i].op1,qu[i].op2);
				}
				if(strcmp(qu[i].op2,"2")==0){
				    strcpy(qu[i].opr,"+");
					strcpy(qu[i].op2,qu[i].op1);
				}
			}
	}
}


int utiliser(int i,int j,char * temp){
	int besoin=0;
	while((j<ind)&&(besoin==0)){
			 if((strcmp(qu[j].op1,temp)==0) || (strcmp(qu[j].op2,temp)==0))
				 besoin=1;
			 if(((strcmp(qu[j].opr,"BR")==0)&&(atoi(qu[j].op1)<i)))
				 besoin=1;
			 if(((strcmp(qu[j].opr,"BZ")==0)&&(atoi(qu[j].op1)<i)))
				 besoin=1;
			 if(((strcmp(qu[j].opr,"BNZ")==0)&&(atoi(qu[j].op1)<i)))
				 besoin=1;
			 if(((strcmp(qu[j].opr,"BG")==0)&&(atoi(qu[j].op1)<i)))
				 besoin=1;
			 if(((strcmp(qu[j].opr,"BGE")==0)&&(atoi(qu[j].op1)<i)))
				 besoin=1;
			 if(((strcmp(qu[j].opr,"BL")==0)&&(atoi(qu[j].op1)<i)))
				 besoin=1;
			 if(((strcmp(qu[j].opr,"BLE")==0)&&(atoi(qu[j].op1)<i)))
				 besoin=1;
			 j++;
		 }
		 return besoin;
}

// sup toutes affectation non utilisée
void suppAffNutil(){
 int i,j,used,fini,p;
 char *temp;
 for(i=0;i<ind;i++){
		 if(strcmp(qu[i].opr,"=")==0){
			 j=i+1;
			  //j permet de voir si on va utiliser le resultat de la'affectation dans les prochains quadruplets
			 temp = strdup(qu[i].res);
			 used=utiliser(i,j,temp);
			 if( used == 0 ){ //si le resultat n'a pas été utilisé donc on supprime le quad
				 fini=0;
				 //p permet de revenir en arriere pour ecraser les quads non utils
				 p=i;
				 while( (p>0) && (fini==0) ){
					 if( (strcmp(qu[p-1].opr,"+")==0) || (strcmp(qu[p-1].opr,"-")==0) || (strcmp(qu[p-1].opr,"*")==0) || (strcmp(qu[p-1].opr,"/")==0)){
						 p--;
					 }
					 else{
					 	fini=1;
					 }
				 }
				 for(j=p;j<ind-1;j++){
					 qu[j]=qu[j+(i-p)+1];
				 }
				 ind=ind-(i-p)-1;
			 }
		 }
 }
}

void optimisation_propagation_copie(){
int i,k;
int j=0;

for(i=0;i<ind;i++) //***remplire la table pile copie avec les copies qui existent
{
  if((strcmp(qu[i].opr,"=")==0))
  {
	k=i+1;
    while((k<ind)&&((strcmp(qu[i].opr,"=")!=0)||(strcmp(qu[i].res,qu[k].res)!=0))){

       if(strcmp(qu[i].res,qu[k].op1)==0) // si var copie existe dans op1 je remplace
        { qu[k].op1=strdup(qu[i].op1);}

	   if(strcmp(qu[i].res,qu[k].op2)==0) // si var copie existe dans op2 je remplace
         {qu[k].op2=strdup(qu[i].op1);}
		 k++;
	}
  }
}
}