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
printf("\n/***************Table des symboles ******************/\n");
printf("_______________\n");
printf("\t| NomEntite |\n");
printf("______________\n");
int i=0;
while(i<CpTabSym)
{

printf("\t|%10s |\n",ts[i].NomEntite);

i++;
}
}
