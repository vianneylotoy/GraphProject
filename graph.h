
#ifndef LGRAPHE_H
#define LGRAPHE_H
#include <sys/time.h>
#include "lliste.h"

typedef struct TypGraphe{

	    int nbrMaxSommets; 
	    struct TypVoisins** listesAdjacences; 
	        
} TypGraphe;

TypGraphe* creation(int);
int insertionSommet(TypGraphe *graphe, int idSommet );
int insertionAreteOriente(TypGraphe*, int, int, int);
int insertionAreteNonOriente(TypGraphe*, int, int, int);
int suppressionSommet(TypGraphe*, int);
int suppressionArete(TypGraphe*, int, int, char);
int sommetExistant(TypGraphe*,int);
int areteExistante(TypGraphe*,int,int);
void affichage(TypGraphe*, char);
void deleteGraphe(TypGraphe*);
int degreSommet(TypGraphe*, int);
void sauvegarde(TypGraphe*,FILE *,char);
int lecture(char[]);
void showSavedGraph();

int fordFulkerson(int Matrix[][50] , int source , int puit, int Max);
bool parcourEnLargeur(int source, int puit, int Matrix[][50],int Max);
int  retrieve(char[]);

#endif
