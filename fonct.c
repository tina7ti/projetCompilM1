#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "fonct.h"
// un compteur global pour la table de symbole
int CpTabSym=0;
//une fonctione recherche: pour chercher est ce que l'entité existe ou non déjà dans la table de symbole.
// i: l'entite existe dejà dans la table de symbole, et sa position est i, -1: l'entité n'existe pas dans la table de symbole.

int recherche(char entite[])
{
int i=0;
while(i<CpTabSym)
{
if (strcmp(entite,ts[i].NomEntite)==0) return i;
i++;
}
return -1;
}

//une fontion qui va insérer les entités de programme dans la table de symbole
void inserer(char entite[])
{

if ( recherche(entite)==-1)
{
strcpy(ts[CpTabSym].NomEntite,entite); 
CpTabSym++;
}
}

//une fonction pour afficher la table de symbole
void afficher ()
{
printf("\n/------- AFFICHE LES IDFs --------/\n");
printf("_____________\n");
printf("| NomEntite |\n");
printf("____________\n");
int i=0;
while(i<CpTabSym)
{

printf("|%10s |\n",ts[i].NomEntite);

i++;
}
}

// fonction qui verifier le nbr de tab avec niveau d'indexation
void indext(int indx,int esp)
{
	if(indx == esp) 
		{
			printf("error de if \n");
			exit(-1);
		}
}

//fonction qui retourne la taille du tableau des entites
int taille()
{
	return CpTabSym;
}

