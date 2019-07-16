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

// maj des brachements vides
void quad_fin()
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

//optimisation 

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


int isBranchement(char *opr){
        
        if(strcmp(opr,"BR")==0 ||strcmp(opr,"BLE")==0 || strcmp(opr,"BL")==0 || strcmp(opr,"BG")==0 || strcmp(opr,"BGE")==0 || strcmp(opr,"BE")==0 || strcmp(opr,"BNE")==0 ) 
        return 1;
 
        else return 0;

}

// sup toutes affectation non utilisée
int suppAffNutil(){
 int i,j,used,fini,p;
 char *temp;
 int booleen=0,indicateur; // tant qu il ya des changement boucler
 

 for(i=0;i<ind;i++){
	
		indicateur =0;
		 if(strcmp(qu[i].opr,"=")==0){
			 j=i+1;
			  //j permet de voir si on va utiliser le resultat de la'affectation dans les prochains quadruplets
			 temp = strdup(qu[i].res);
			 used=utiliser(i,j,temp);
			 if( used == 0 ){ //si le resultat n'a pas été utilisé donc on supprime le quad
				 fini=0; indicateur=1;int nbrDecalages;
				 //p permet de revenir en arriere pour ecraser les quads non utils
				 p=i;
				 while( (p>0) && (fini==0) ){
					 if( (strcmp(qu[p-1].opr,"+")==0) || (strcmp(qu[p-1].opr,"-")==0) || (strcmp(qu[p-1].opr,"*")==0)|| 							(strcmp(qu[p-1].opr,"/")==0)){
						 p--;
					 }
					 else{
					 	fini=1;
					 }
				 }
				 nbrDecalages=i-p+1;
				 for(j=p;j<ind-nbrDecalages+1;j++) qu[j]=qu[j+nbrDecalages];
                                                               
                                ind-=nbrDecalages;
                                // MAJ des réferences de branchements
                                for(j=0;j<ind;j++){
                                        if(isBranchement(qu[j].opr)){ // si ce quad est un branchement , il faut màj l'indice auquel ilfait brancher
                                                if(atoi(qu[j].op1)>=p){
                                                        char newBranchement[10]; sprintf(newBranchement,"%d",(atoi(qu[j].op1)-nbrDecalages));
                                                        strcpy(qu[j].op1,newBranchement);

                                                }                                         
                                        }
                                }
                                //for(int k=qc;k<qc+nbrDecalages;k++) vider(k);
                                i-=nbrDecalages;
				 //ind=ind-(i-p)-1;
			 }
		
 		}
	
    }
    if(indicateur == 0) return 0;
    return 1;
}

void appelSuppAffNutil(){
	int a=1;
	a = suppAffNutil();
	while(a==1){
		a=suppAffNutil();
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


void inserer_quad(int j,int debut,int cpt,char* var){

int indx=ind-1;int i,l;
  //***********************decalage de n position avec n=cpt
while(indx>=j)
{  i=indx+cpt;
   qu[i].opr=strdup(qu[indx].opr);
   qu[i].op1=strdup(qu[indx].op1);
   qu[i].op2=strdup(qu[indx].op2);
   qu[i].res=strdup(qu[indx].res);
   indx--;
}
//*********************insertion de n quad(n=cpt) à la position j//

for(l=0;l<cpt;l++)
{
   qu[j].opr=strdup(qu[debut].opr);
   qu[j].op1=strdup(qu[debut].op1);
   qu[j].op2=strdup(qu[debut].op2);
   qu[j].res=strdup(qu[debut].res);
   j++;debut++;
}
//***********************mise a jour sur le quad de l'aff ayant la//
if(strcmp(qu[j].op1,var)==0)
    {
       qu[j].op1=strdup(qu[j-1].res);
	}
if(strcmp(qu[j].op2,var)==0)
    {
		qu[j].op2=strdup(qu[j-1].res);
	}
//***********************mise ajour ind =nbr quad//


ind=ind+cpt;


}



int f_numeric(char* a)
{
 if(a[0]=='0' || a[0]=='1'|| a[0]=='2' || a[0]=='3'|| a[0]=='4' || a[0]=='5' || a[0]=='6' ||a[0]=='7' || a[0]=='8'||a[0]=='9')
       { return 1;}

    return 0;

}


void mise_ajour_adr(int i,int cpt)
{

 int j,x;
    for(j=0;j<ind;j++){
        if(qu[j].opr[0]=='B'){
                x=atoi(qu[j].op1);
            if(x >i){

             x=x+cpt;
             sprintf(qu[j].op1,"%d",x);
            }
        }
    }


  }


void optimisation2_propagation_expression()
{
int i=0; int cpt;int debut,boolean;char* var;int j;
  int m; int k;
for(m=0;m<ind;m++)
{ boolean=0;cpt=0;

   i=m;
  if(qu[i].opr[0]=='+' ||  qu[i].opr[0]=='*'  ||  qu[i].opr[0]=='/'  || qu[i].opr[0]=='-' )
   {
	    if (f_numeric(qu[i].op1)==1  && f_numeric(qu[i].op2)==1)
        {
            while( i<ind && qu[i].opr[0]!='=' && (qu[i].opr[0]=='+' ||  qu[i].opr[0]=='*'
                                                    ||  qu[i].opr[0]=='/'  || qu[i].opr[0]=='-' )
             && (f_numeric(qu[i].op1)==1 || qu[i].op1[0]=='T' ) &&
	         (f_numeric(qu[i].op2)==1 ||  qu[i].op2[0]=='T'  ))
                    {  if(boolean==0){debut=i;boolean=1;}

                         cpt++;i++;
	                }
			m=i;

			if(qu[i].opr[0]=='=')
            {
                var=strdup(qu[i].res);

                j=i+1;


      while((j<ind)&&(strcmp(qu[j].res,var)!=0))
	  {


			  if(strcmp(qu[j].op1,var)==0 || strcmp(qu[j].op2,var)==0 )
                  {
					  inserer_quad(j,debut,cpt,var);
					  mise_ajour_adr(j,cpt);


				  }

         j++;
	  }
    }

}
   }


}
}


void optimiser(){
	suppAffNutil();
	//SuppressionCodeInutile();
	optimisation_propagation_copie();
	optimisation2_propagation_expression();
	afficherQuad();
}
