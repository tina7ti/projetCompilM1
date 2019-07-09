#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
char NomEntite[20];
} TypeTS;

//initiation d'un tableau qui va contenir les elements de la table de symbole
TypeTS ts[100]; 




//une fonctione recherche: pour chercher est ce que l'entité existe ou non déjà dans la table de symbole.
// i: l'entite existe dejà dans la table de symbole, et sa position est i, -1: l'entité n'existe pas dans la table de symbole.

int recherche(char entite[]);
//une fontion qui va insérer les entités de programme dans la table de symbole
void inserer(char entite[]);

//une fonction pour afficher la table de symbole
void afficher ();
void indext(int indx,int esp);
int taille();

