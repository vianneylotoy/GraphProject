#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lliste.h"

	
	/*
	 * La fonction createTypVoisins prend en paramètres int voisin, le numéro du voisin à créer,
	 * int poids, le poids du voisin à créer, TypVoisins** vS, le voisin qui suivra dans la liste le voisin créé
	 * et TypVoisins** vP, le voisin qui précédera dans la liste le voisin créé.
	 * Elle Crée et renvoie un nouveau voisin dont les données (numéro et poids) sont passées en paramètres,
	 * et lie ce voisin aux deux voisins passés en paramètres.
	 */
	 
static TypVoisins* createTypVoisins(int voisin, int weight, TypVoisins** voisinS, TypVoisins** voisinP) {
	
	TypVoisins *newVoisin;	
	
	newVoisin = malloc(sizeof(TypVoisins));
	
	newVoisin->voisin = voisin;
	
	newVoisin->poidsVoisin = weight;
	
	newVoisin->voisinSuivant = *voisinS;
	
	newVoisin->voisinPrecedent = *voisinP;
	
	return newVoisin;
}


	/*
	 * La fonction initialisationListe  Crée une nouvelle liste et renvoie un pointeur pointant au début de celle-ci.
	 * La sentinelle y est insérée et a pour numéro et poids -1.
	 * Elle retourne TypVoisins*, pointeur sur le début de la liste nouvellement créée.
	 */
	 
TypVoisins* initialisationListe() {
	
	TypVoisins *sentinel;	
	
	
	
	sentinel = createTypVoisins(-1,-1,&sentinel,&sentinel);
	
	sentinel->voisinSuivant = sentinel;
	
	sentinel->voisinPrecedent = sentinel;
	
	return sentinel;
}


	/*
	 * La fonction deleteListeMemory prend en paramètres TypVoisins** liste, le début de la liste à supprimer.
	 * Elle Supprime tous les voisins de la liste passée en paramètre et désalloue la mémoire de celle-ci.
	 */
	 
void deleteListeMemory(TypVoisins** liste){
	
	TypVoisins *voisinC;		
	
	voisinC = nextVoisin(liste);
	
	while (voisinC != *liste) {
		
		deleteVoisinFromListe(liste,numberOfActualVoisin(&voisinC));
		
		voisinC = nextVoisin(liste);
	}
	free(*liste);
	
	*liste = NULL;
}


	/*
	 * la fonction addVoisinListe prend en paramètres TypVoisins** liste, le début de la liste à laquelle on veut ajouter un nouveau voisin,
	 * int voisin, le numéro du nouveau voisin à insérer et int poids, le poids du nouveau voisin à insérer.
	 * Elle Ajoute un nouveau voisin à la fin de la liste passée en paramètre.
	 */
	 
void addVoisinListe(TypVoisins** liste, int newVoisin, int weight) {
	
	TypVoisins *voisinS;		
	
	TypVoisins *voisinP;		
	
	TypVoisins *voisinC;		
	
	voisinS = *liste;
	
	voisinP = voisinS->voisinPrecedent;
	
	voisinC = createTypVoisins(newVoisin,weight,&voisinS,&voisinP);
	
	voisinP->voisinSuivant = voisinC;
	
	voisinS->voisinPrecedent = voisinC;
}


	/*
	 * La fonction deleteVoisinFromListeprend en paramètres TypVoisins** liste, pointeur sur le début d'une liste,
	 * int voisinASupprimer, le numéro du voisin à supprimer.
	 * Elle Supprime le voisin demandé dans la liste passée en paramètre. Ne fait rien s'il ne s'y trouve pas.
	 */
	 
void deleteVoisinFromListe(TypVoisins** liste, int voisinToDelete) {
	
	if (voisinToDelete != -1)
	{
		TypVoisins *voisinC;    
		
		TypVoisins *voisinP;    
		
		TypVoisins *voisinS;    
		
		bool 	   trouve; 
		
		
		voisinC = nextVoisin(liste);
		
		trouve = false;
		
		while (!trouve && voisinC != *liste) {
			
			if (numberOfActualVoisin(&voisinC) == voisinToDelete)
			
				trouve = true;
				
			else
			
				voisinC = nextVoisin(&voisinC);
		}
		
			
		if (trouve == true) {
			
			voisinP = previousvoisin(&voisinC);
			
			voisinS = nextVoisin(&voisinC);
			
			voisinP->voisinSuivant = voisinS;
			
			voisinS->voisinPrecedent = voisinP;
			
			free(voisinC);
		}
	}
}


	/*
	 * La fonction numberOfActualVoisin prend en paramètre TypVoisins** voisin, un élément d'une liste.
	 * Elle Renvoie le numéro du voisin passé en paramètre.
	 * Elle retourne int, le numéro du voisin passé en paramètre.
	 */
	 
int numberOfActualVoisin(TypVoisins** newVoisin) {
	
	return (*newVoisin)->voisin;
}


	/*
	 * La fonction weightOfActualVoisin prend en paramètres TypVoisins** voisin, un élément d'une liste.
	 * Elle Renvoie le poids du voisin passé en paramètre et retourne int, le poids du voisin passé en paramètre.
	 */
	 
int weightOfActualVoisin(TypVoisins** newVoisin) {
	
	return (*newVoisin)->poidsVoisin;
}


	/*
	 * La fonction nextVoisin prend en paramètres TypVoisins** voisin, un élément d'une liste.
	 * Elle Renvoie un pointeur sur le voisin suivant dans la liste de l'élément passé en paramètre.
	 * Elle retourne TypVoisins*, pointeur sur le voisin suivant de l'élément passé en paramètre.
	 */
	 
TypVoisins* nextVoisin(TypVoisins** newVoisin){
	
	return (*newVoisin)->voisinSuivant;
}


	/*
	 * La fonction previousvoisin prend en paramètres TypVoisins** voisin, un élément d'une liste.
	 * Elle Renvoie un pointeur sur le voisin précédent dans la liste de l'élément passé en paramètre.
	 * Elle retourne TypVoisins*, pointeur sur le voisin précédent de l'élément passé en paramètre.
	 */
	 
TypVoisins* previousvoisin(TypVoisins** newVoisin) {
	
	return (*newVoisin)->voisinPrecedent;
}


	/*
	 * La fonction sizeofListe prend en paramètres TypVoisins** liste, pointeur sur le début d'une liste.
	 * Elle Renvoie la taille de la liste passée en paramètre.
	 * Elle retourne int, la taille de la liste passée en paramètre.
	 */
	 
int sizeofListe(TypVoisins** liste) {
	
	TypVoisins *voisinC;		
	
	int        res;		
	
	voisinC = nextVoisin(liste);
	
	res = 0;
	
	while (voisinC != *liste) {
		
		res++;
		
		voisinC = nextVoisin(&voisinC);
	}
	
	return res;
}


	/*
	 * La fonction checkExistanceOfVoisin prend en paramètres TypVoisins** liste, le début d'une liste,
	 * int voisin, numéro du voisin dont on veut connaître l'existence dans la liste.
	 * Elle Vérifie si le voisin demandé existe dans la liste passée en paramètre.
	 * Elle retourne bool, true si le voisin existe dans la liste, sinon false.
	 */
	 
bool checkExistanceOfVoisin(TypVoisins** lliste, int newVoisin) {
	
	TypVoisins *voisinC;  
	  
	bool       trouve;
	
	voisinC = nextVoisin(lliste);
	
	trouve = false;
	
	while (!trouve && voisinC != *lliste) {
		
		if (numberOfActualVoisin(&voisinC) == newVoisin)
		
			trouve = true;
			
		voisinC = nextVoisin(&voisinC);
	}
	
	return trouve;
}


	/*
	 * La fonction convertToString pren dparamètres TypVoisins** liste, le début d'une liste.
	 * Elle Renvoie la représentation de la liste passée en paramètre sous la forme "(2,3), (4,6)" pour une liste comportant deux 
	 * voisins numérotés 2 et 4 et ayant pour poids 3 et 6. Renvoie NULL si la liste est vide.
	 * Elle retourne char*, une chaîne représentant le contenu de la liste (mémoire allouée dans la fonction).
	 */
	 
char* convertToString(TypVoisins** lliste) {
	
	char       *res; 
	
	char       *tmp; 
	
	TypVoisins *voisinC;  
	
	voisinC = nextVoisin(lliste);
	
	if (voisinC == *lliste)
		return NULL;
	
	res = malloc(500);
	
	tmp = malloc(25);
	
	sprintf(res,"(%d/%d)",numberOfActualVoisin(&voisinC),weightOfActualVoisin(&voisinC));
	voisinC = nextVoisin(&voisinC);
	
	while (voisinC != *lliste) {
		
		sprintf(tmp,", (%d/%d)",numberOfActualVoisin(&voisinC),weightOfActualVoisin(&voisinC));
		
		strcat(res,tmp);
		
		voisinC = nextVoisin(&voisinC);
	}
	
	free(tmp);
	
	tmp = realloc(res,strlen(res)+1);
	
	res = tmp;
	
	return res;
}

/*
 * La fonction displayListFile prend en paramètres TypVoisins* listeSommets	:est un pointeur sur TypVoisins
 * FILE *fichier: est un pointeur sur FILE.
 * Elle affiche la liste d'un fichier.
 */
 
void displayListFile(TypVoisins* listeSommets, FILE *fichier){
	
	char *chaine;  
	
	chaine = convertToString(&listeSommets);
	
	if (chaine != NULL) {
		
		fprintf(fichier,"%s",chaine);
		
		free(chaine);
	}
}
