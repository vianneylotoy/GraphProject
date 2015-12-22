
#ifndef LLISTE_H
#define LLISTE_H

#include <stdbool.h>

typedef struct TypVoisins {
	int voisin;
	int poidsVoisin;
	struct TypVoisins* voisinSuivant;
	struct TypVoisins* voisinPrecedent;
} TypVoisins;

TypVoisins* initialisationListe();
void deleteListeMemory(TypVoisins**);
void addVoisinListe(TypVoisins**,int,int);
void deleteVoisinFromListe(TypVoisins**,int);
int numberOfActualVoisin(TypVoisins**);
int weightOfActualVoisin(TypVoisins**);
TypVoisins* nextVoisin(TypVoisins**);
TypVoisins* previousvoisin(TypVoisins**);
int sizeofListe(TypVoisins**);
bool checkExistanceOfVoisin(TypVoisins**,int);
char* convertToString(TypVoisins**);
void displayListFile(TypVoisins*, FILE *);

#endif
