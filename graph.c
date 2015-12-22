#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/time.h>
#include "erreurs.h"
#include "lliste.h"
#include "lgraphe.h"


int predecesseur[50];
int visited[50];
int somD = 0, somA = 0, pDs = 0, Msom = 0;
int Matrice [50][50];



/* la fonction de permet de lire et re-inserer dans la matrice les donnees*/
int  retrieve(char nomFichier[])
{

	FILE * fichier;
		char line[512];
		char ori[20];
		char root[] = "Graphe/";
		char c;
		int x=0, y=0, z=0, taille=0;
		char *pathAndFile = malloc(sizeof(char) * 20);
	   	pathAndFile[0] = '\0';
	    strcat(pathAndFile,root);
	    strcat(pathAndFile, nomFichier);
		fichier = fopen(pathAndFile, "r");
		
		int nbrLine = 0;
		if(fichier != NULL){
			
		  while(EOF != (c = fgetc(fichier))){
				
				if(nbrLine == 24)
				{
					fscanf(fichier," %s %d", line, &taille);
					Msom = taille;
					printf("le nombre max de sommet est: %d\n", taille);
					
				}
				else{
						if(nbrLine > 34 && nbrLine < 36)
						{
								fscanf(fichier, "%s", ori);
						}
						
							if(nbrLine > 55)
							{	
										if(c == '\n' && c != '#' && c != ' ' && c != ','){
											fscanf(fichier,"%d %s", &x, line);
											somD = x;
											printf("le sommet de depart est: %d\n", somD);
										}
							}	
							
							if(c == '('){
								fscanf(fichier,"%d", &y);
								somA = y;
								printf("le sommet d'arrive est: %d\n", somA);
									
							}
							if(c == '/'){
								fscanf(fichier,"%d", &z);
								pDs = z;
								printf("le poids est: %d\n", pDs);
								
								/*Remplissage de la matrix*/
								 Matrice[somD][somA] = pDs;  
							}
						
				}
				
				nbrLine++;
		  }
		 
		}
		
		fclose(fichier);
		free(pathAndFile);
		
		/*int d,k;
		for(d=1; d <= Msom ; d++){
						for(k=1; k <= Msom ; k++){
							printf("%d\t", Matrice[d][k]);
						}
						printf("\n");
					}*/
					
	int source;
	int puit;
	int maxflow;
				
	if((*ori) == 'o'){	
	do{
			printf("Veuillez saisir la source:\n");
			scanf("%d",&source);
			printf("Veuillez saisir le puit:\n");
			scanf("%d",&puit);
		  }while((source<1||source>Msom)&&(puit<1||puit>Msom));
		  
		struct timeval tim;
		gettimeofday(&tim, NULL);
        double t1=tim.tv_sec+(tim.tv_usec/1000000.0);	
		
            
		maxflow = fordFulkerson(Matrice, source, puit, Msom);
		
		gettimeofday(&tim, NULL);
        double t2=tim.tv_sec+(tim.tv_usec/1000000.0);	
		//end.tv_sec;
        //res = end.tv_sec - start.tv_sec;
        //res = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;


        printf("le temps d'execution recursif est: %f sec \n", t2-t1);
        
		printf("\n______________________________________\n");
		printf("---------Le Flow maximum -------------\n");
		printf("	Flow max = %d\n", maxflow);
		printf("______________________________________\n");
		printf("______________________________________\n");
	}
	else {
		printf("\n______________________________________\n");
		printf("---------Le Flow maximum -------------\n");
		printf("	Le graphe n'est pas orienté!\n");
		printf("______________________________________\n");
		printf("______________________________________\n");
	}					
			
			
		return 0;
}

	
/* La fonction min permet de retourner le minimum*/
int min(int x, int y)
{
  return (x < y) ? x : y;
}

/*La fonction fordFulkerson permet de calculer le max flot d'apres l'algo de fordFulkerson
 * */
int fordFulkerson(int Matrix[50][50] , int source , int puit, int Max){
	 
	 int maxFlow = 0;
	 int pathFlow = 0;
	 int u, v;
	
	while(parcourEnLargeur(source ,puit, Matrix, Max)){
	
		pathFlow = INT_MAX;
		for (v = puit; v != source; v = predecesseur[v]){
                    u = predecesseur[v];
                    pathFlow =min(pathFlow, Matrix[u][v]);
         }
         for (v = puit; v != source; v = predecesseur[v]) {
                    u = predecesseur[v];
                    Matrix[u][v] -= pathFlow;
                    Matrix[v][u] += pathFlow;
         }
         maxFlow += pathFlow;
		 
	 }
	 int d,k;
	 printf("Voici la matrice residuelle: \n");
		for(d=1; d <= Msom ; d++){
						for(k=1; k <= Msom ; k++){
							printf("%d\t", Matrice[d][k]);
						}
						printf("\n");
					}
	 
	 
	 return maxFlow;
	 
 }

/* La fonction parcourEnLargeur permet de trouver un chemin en faisant un parcour en largeur du Matrice. 
 */ 
bool parcourEnLargeur(int source, int puit, int Matrix[50][50],int Max){
		
	int TableauSommetDepart[Max];
	bool pathFound = false;
	int SommetArrive, SommetDepart;
	int indice = 0;
	bool etatTableauSommetDepart = false;
	
	int vertex;
	int i;
	/* Inialisation TableauSommetDepart */
	for(i = 0; i < Max; i++){
		TableauSommetDepart[i]=0;
	}
	/* Inialisation Visited & predecesseur */
	for(vertex = 1; vertex <= Max; vertex++)
	{
			predecesseur[vertex] = -1;
			visited[vertex] = false;
			
	}
	
	TableauSommetDepart[0] = source;
	predecesseur[source] = -1;
	visited[source] = true;
	
	do{
		int i;
		for(i=0; i < Max; i++){
			if(TableauSommetDepart[i] != 0){SommetDepart = TableauSommetDepart[i]; TableauSommetDepart[i]=0;break;}
		}
		
		SommetArrive = 1;
		 while (SommetArrive <= Max) {
			
			if (Matrix[SommetDepart][SommetArrive] > 0 &&  !visited[SommetArrive]) {
				
				/*Recuperation du premier élément non nul dans TableauSommetDepart */
				for(i=0; i < Max; i++){
					if(TableauSommetDepart[i] != 0) { indice = i;}
					
				}
				
				
				predecesseur[SommetArrive] = SommetDepart;
				TableauSommetDepart[indice+1] = SommetArrive;
				visited[SommetArrive] = true;
			}
			SommetArrive++;
		}
		for(i=0; i < Max; i++){
			if(TableauSommetDepart[i] != 0){etatTableauSommetDepart = true; break;}
			else etatTableauSommetDepart = false;
		}
		
	}while(etatTableauSommetDepart);
	
	if(visited[puit]){
       pathFound = true;
    }
	return pathFound;
	
}

/*
	 * La fonction creation prend en paramètres le nombre de sommet que peut contennir le graphe.
	 * Crée un graphe vide et le renvoie.
	 * Fonction : creation
	 */
TypGraphe* creation(int nbrMaxSommets) {
	
	TypGraphe* graphe; 
	int iterator;
	
	graphe = malloc(sizeof(TypGraphe));
	graphe->nbrMaxSommets = nbrMaxSommets;
	graphe->listesAdjacences = ( TypVoisins** ) malloc( nbrMaxSommets * sizeof( TypVoisins* ) );
		
	for ( iterator = 0; iterator < nbrMaxSommets; iterator++) {
		graphe->listesAdjacences[iterator] = NULL;
	} 

	return graphe;
}


	/*
	 * La fonction insertionSomment prend en paramètres le graphe et le numéro du Sommet a insérer.
	 * Elle insère un sommet dans le graphe, elle Renvoie 0 si l'insertion est un succé sinon renvoie un code d'érreur.
	 */
	 
int insertionSommet ( TypGraphe *graphe, int numeroDuSommet ) {
	
	if ( graphe->listesAdjacences == NULL ) {
		
		return NonExistentGraph;
	}
	
	if( (numeroDuSommet > 0 ) && ( numeroDuSommet <= graphe->nbrMaxSommets ) ) {
		
		if ( graphe->listesAdjacences[numeroDuSommet-1] == NULL ) {
			
            graphe->listesAdjacences[numeroDuSommet-1] = initialisationListe();
            
			return 0;
        }
		else
		
			return ExistentVertex;
	}
	else {
		
		return InvalideVertex;
	}
}


	/*
	 * La fonction sommetExistant prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé et int numSommet, le numéro du sommet à rechercher
	 * Elle verifie si le sommet existe déja dans le graphe, retourne int, 0 si le sommet est trouvé sinon renvoie un code d'erreur.
	 * Fonction : sommetExistant
	 */
	 
int sommetExistant ( TypGraphe * graphe, int numeroDuSommet ) {

	if ( graphe->listesAdjacences == NULL ) {
		
		return NonExistentGraph;
	} 
	else {
		
		if ( numeroDuSommet > graphe->nbrMaxSommets ) {
			
			return InvalideVertex;
			
		}
	}

	if ( graphe->listesAdjacences[ numeroDuSommet-1 ] != NULL ) {
		
		return 0;
		
	} 
	else {
		
		return NonExistentVertex;
		
	}

}


	/*
	 * La fonction areteExistante prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé,
	 * int depart, le sommet de départ de l'arête et int arrivee, le sommet sur lequel pointe l'arête.
	 * Elle verifie Si l'arête existe déjà dans le graphe, retourne int, renvoie 0 si l'arête est trouvée,
	 * sinon renvoie un code d'erreur.
	 */
	 
	 
int areteExistante (TypGraphe *graphe, int sommetDedepart, int sommetDarrivee) {
	
	if (graphe->listesAdjacences == NULL)
	
		return NonExistentGraph;
		
	else {
		
		if (sommetExistant(graphe,sommetDedepart) == 0 && sommetExistant(graphe,sommetDarrivee) == 0) {
			
			if (checkExistanceOfVoisin(&(graphe->listesAdjacences[sommetDedepart-1]),sommetDarrivee) == true)
			
				return 0;
			else
			
				return NonExistentRidge;
		}
		else
		
			return NonExistentVertex;
	}
}


	/*
	 * La fonction suppressionSommet prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé et 
	 * int sommet, le numéro du sommet à supprimer. Elle supprime un sommet du grahe et retourne un int,
	 *  renvoie 0 si le sommet est supprimé sinon, renvoie un code d'erreur.
	 */
	 
int suppressionSommet ( TypGraphe* graphe, int numeroDuSommet ) {
	
	int i; 
  
	if (graphe->listesAdjacences == NULL)
	
		return NonExistentGraph;
		
	else {
		
		if (sommetExistant(graphe,numeroDuSommet) == 0) {
			
			deleteListeMemory(&(graphe->listesAdjacences[numeroDuSommet-1]));
			
			for (i = 0; i < graphe->nbrMaxSommets; i++) {
				
				if (graphe->listesAdjacences[i] != NULL)
				
					deleteVoisinFromListe(&(graphe->listesAdjacences[i]),numeroDuSommet);
					
			}
			return 0;
		}
		else
		
			return NonExistentVertex;
	}
}


	/*
	 * La fonction insertionAreteOriente prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé,
	 * int depart, le sommet de depart de l'arête, int arrivee, le sommet sur lequel pointe l'arête et int poids, le poids de l'arête.
	 * Elle Ajoute une arête orienté dans le graphe en verfiant aussi que l'arrête existe déja ou pas.
	 * Elle retourne un int, renvoie 0 si l'arête est insérée sinon renvoie un code d'erreur.
	 */
	 
int insertionAreteOriente ( TypGraphe* graphe, int sommetDedepart, int sommetDarrivee, int weightSommet ) {
	
	if (graphe->listesAdjacences == NULL)
	
		return NonExistentGraph;
		
	else if (areteExistante(graphe,sommetDedepart,sommetDarrivee) == 0)
	
		return ExistentRidge;
		
	else {
		
		if (sommetExistant(graphe,sommetDedepart) == 0 && sommetExistant(graphe,sommetDarrivee) == 0) {
			
			addVoisinListe(&(graphe->listesAdjacences[sommetDedepart-1]),sommetDarrivee,weightSommet);
			
			return 0;
		}
		else
		
			return NonExistentVertex;
	}
}


	/*
	 * La fonction insertionAreteNonOriente prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé,
	 * int depart, un sommet du graphe , int arrivee, un sommet du graphe et int poids, le poids de l'arête.
	 * Elle insère une arête non orienté dan sle graphe en vérifiants si l'arête existe déjà.
	 * Elle retourne un int, renvoie 0 si l'arête est insérée sinon renvoie un code d'erreur.
	 */
	 
int insertionAreteNonOriente ( TypGraphe* graphe, int sommetDedepart, int sommetDarrivee, int weightSommet ) {
	
	if (graphe->listesAdjacences == NULL)
	
		return NonExistentGraph;
		
	else if (areteExistante(graphe,sommetDedepart,sommetDarrivee) == 0 || areteExistante(graphe,sommetDarrivee,sommetDedepart) == 0)
	
		return ExistentRidge;
		
	else {
		
		if (sommetExistant(graphe,sommetDedepart) == 0 && sommetExistant(graphe,sommetDarrivee) == 0) {
			
			addVoisinListe(&(graphe->listesAdjacences[sommetDedepart-1]),sommetDarrivee,weightSommet);
			
			addVoisinListe(&(graphe->listesAdjacences[sommetDarrivee-1]),sommetDedepart,weightSommet);
			
			return 0;
		}
		else
		
			return NonExistentVertex;
	}
}

	/*
	 * La fonction suppressionArete prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé,
	 * int depart, le sommet de départ de l'arête, int arrivee, le sommet sur lequel pointe l'arête et
	 * char orientation, 'o' si l'arête est orientée, sinon 'n'. 
	 * Elle supprime une arête dans le graphe, et retourne un int, renvoie 0 si l'arête est supprimée
	 * sinon renvoie un code d'erreure  dans le graphe
	 */
	 
int suppressionArete ( TypGraphe* graphe, int sommetDedepart, int sommetDarrivee, char orientation ) {
	
	if (graphe->listesAdjacences == NULL)
	
		return NonExistentGraph;
		
	else {
		
		if (sommetExistant(graphe,sommetDedepart) == 0 && sommetExistant(graphe,sommetDarrivee) == 0) {
			
			if (orientation == 'o') {
				
				if (areteExistante(graphe,sommetDedepart,sommetDarrivee) == 0) {
					
					deleteVoisinFromListe(&(graphe->listesAdjacences[sommetDedepart-1]),sommetDarrivee);
					
					return 0;
				}
				else
				
				return NonExistentRidge;
			}
			
			else {
				
				if (areteExistante(graphe,sommetDedepart,sommetDarrivee) == 0 && areteExistante(graphe,sommetDarrivee,sommetDedepart) == 0) {
					
					deleteVoisinFromListe(&(graphe->listesAdjacences[sommetDedepart-1]),sommetDarrivee);
					
					deleteVoisinFromListe(&(graphe->listesAdjacences[sommetDarrivee-1]),sommetDedepart);
					
					return 0;
				}
				else
				
					return NonExistentRidge;
			}
		}
		else
		
			return NonExistentVertex;
	}
}


/*
 * La fonction affichage prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé
 * et un char oriente qui indique si le graphe est oriente ou pas.
 * Elle affiche le graphe.
 */
 
 
void affichage ( TypGraphe* graphe, char orient) {
	int i;         /* Permet le parcours des listes du graphe */
	char* chaine;  /* Chaîne où seront stockées les représentations des listes*/
	
	printf ( "# nombre maximum de sommets\n" );
	printf ( "%d \n",graphe->nbrMaxSommets );
	printf ( "# Oriente \n" );
	printf ( "%c\n", orient);
	printf ( "# sommets : voisins\n" );
	
	for ( i=0; i< graphe->nbrMaxSommets; i++ ) {
		
		if (sommetExistant(graphe,i+1) == 0) {
			
			printf ( "%d : ", i+1 );
			
		    if ( graphe->listesAdjacences[i] != NULL ) {
				
				chaine = convertToString(&(graphe->listesAdjacences[i]));
				
				if (chaine != NULL) {
					
					printf("%s",chaine);
					
					free(chaine);
				}
		    }
		    printf( "\n" );
		}
	}
}


/*
 * La fonction sauvegarde prend en paramètres TypGraphe * graphe :un pointeur sur TypGraphe et
 * FILE *fichier: un pointeur sur FILE.
 * Elle sauvegarde le graphe dans un fichier.
 */
 
void sauvegarde (TypGraphe* Graphe, FILE *file, char orien){

	int i ;  
	
	if ( Graphe == NULL ) {  	
		
		fprintf( stderr, "graphe n'existe pas \n" );
	}
	
	fprintf( file, "# nombre maximum de sommets\n%d\n# oriente\n%c\n# sommets : voisins\n", Graphe->nbrMaxSommets,orien );
	
	for ( i = 0; i < Graphe->nbrMaxSommets ; i++ ) {
		
		if (sommetExistant(Graphe,i+1) == 0) {
			
			fprintf( file, "%d : ", i+1 );
		    
		    if ( Graphe->listesAdjacences[ i ] != NULL ) {
				
				displayListFile( Graphe->listesAdjacences[ i ], file );
		    }
		    
		    fprintf(file,"\n");	
		}
	}
}
 

	/*
	 * La fonction deletegraphe prend en parmètres TypGraphe *graphe, pointeur sur un graphe déjà créé.
	 * Elle Supprime le graphe passé en paramètre. Toute la mémoire qui lui avait été allouée est libérée.
	 */
	 
void deleteGraphe ( TypGraphe* Graph ) {
	int i;  
	
	for (i = 0; i < Graph->nbrMaxSommets; i++)
		suppressionSommet(Graph,i+1);
		
	free(Graph->listesAdjacences);
	
	free(Graph);
}


/*
 * La fonction lecture prend en paramètres TypGraphe** graphe, le graphe à créer depuis le chargement du fichier
 * et char nomFichier[80] : est un tableau de caractére représentant le nom du fichier.
 * Elle lit le graphe depuis un fichier .
 * Elle retourne 0 si tout se passe bien, sinon un code d'erreur.
 */
 
int lecture (char nomFichier[]) {
	
    FILE * fichier;
		char line[512];
		char root[] = "Graphe/";
		char *pathAndFile = malloc(sizeof(char) * 20);
	   	pathAndFile[0] = '\0';
	    strcat(pathAndFile,root);
	    strcat(pathAndFile, nomFichier);
		fichier = fopen(pathAndFile, "r");
		int nbrLine = 0;
		if(fichier != NULL){
			
		  while(fgets(line, 512, fichier) != NULL){
			printf("\t %s", line);
			nbrLine++;
		  }
		 
		 printf("\n\n");
		}
		
		fclose(fichier);
		free(pathAndFile);
		return 0;
}



/* Fonction d'affichage des graphes sauvegardes dans le dossier "Graphe"
 * 
 * */
void showSavedGraph(){
	
		DIR *rep = NULL;
		rep = opendir("Graphe/");
		struct dirent* fichierLu = NULL;
		int i;
		char *fichierAlire = malloc(sizeof(char) * 15);
		if(rep != NULL){
			printf("--LISTE DES GRAPHES SAUVEGARDES---\n");
			i = 0;
			while((fichierLu = readdir(rep)) != NULL){
				
					if ( !strcmp(fichierLu->d_name, ".") || !strcmp(fichierLu->d_name, "..") )
					{}
					else{
						
						
						fichierAlire = strdup(fichierLu->d_name);
						printf("%d. %s\n\n", ++i, fichierAlire);
					
					}
					
			}
			
		}
		closedir(rep);
	}



	/*
	 * La fonction degreSommet prend en paramètres TypGraphe *graphe, pointeur sur un graphe déjà créé
	 * et int sommet, le numéro d'un sommet du graphe.
	 * Elle Renvoie le degré du sommet passé en paramètre. Renvoie 0 si le sommet n'existe pas ou n'a pas d'arêtes adjacentes.
	 * Elle retourne int , le degré du sommet.
	 */
	 
int degreSommet(TypGraphe* graphe, int sommet) {
	
	if (sommetExistant(graphe,sommet) == 0)
	
		return sizeofListe(&(graphe->listesAdjacences[sommet-1]));
		
	else
	
		return 0;
}

