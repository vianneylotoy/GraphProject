
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "lgraphe.h"
#include "lliste.h"
#include "erreurs.h"


TypGraphe* Graph;

char orient='x';

int Max = 0;

int maxflow = 0;

int Matrix [50][50];
int source;
int puit;

static void menu();
static void displayGraphe();
static void insertVertex();
static void insertRidge();
static void deleteVertex();
static void deleteRidge();
static void saveGraphe();
static void loadGraphe();
static void leave();
static void ClearString(const char *chaine);
static void waitCharEntry();
static void	ShowFordFulkerson();
//static void ShowRetrieveData();
static void	ShowFordFulkersonAutomatic();




	/*
	* La Fonction mainMenu affiche le menu d'accueil au progromme 
	*en proposant à l'utilisateur des diférentes options 
	* 
	*/
void mainMenu (){
	 
	int option; 

	int numberOfVertex;   
	     
	char line[201];   
	int cpt;        
	char filename[201];
	
	printf(  "_____________________________________________________\n");
	
	printf(  "|                      ACCUEIL GRAPHE               |\n");
	
	printf(  "|___________________________________________________|\n");
	
	printf(  "|	Tapez 1 : Pour créer un nouveau graphe......|\n");
	
	printf(  "|	Tapez 2 : Pour charger le graphe............|\n");
	
	printf(  "|	Tapez 3 : Calcul automatique du flow max....|\n");
	
	printf(  "|	Tapez 4 : Pour quitter......................|\n");
	
	printf(  "|___________________________________________________|\n");
	
	do {
		printf("Choisir une option: ");
		
		fgets(line,2,stdin);
		
		ClearString(line);
		
		             cpt = sscanf(line,"%d",&option);
		
	} while (cpt != 1 || option < 1 || option > 4);
	
	switch (option){
		
		case 1 :
		
			do {
				printf("Veuillez saisir le nombre maximum des sommets \n : ");
				fgets(line,10,stdin);
				
				ClearString(line);
				
				cpt = sscanf(line,"%d",&numberOfVertex);
				Max = numberOfVertex;
				
				/*Initialisation de la matrix*/
					int i,j;
					for(i=0; i <10 ; i++){
						for(j=0; j <10 ; j++){
							Matrix[i][j] = 0;
						}
					}
				
			} while (cpt != 1 || numberOfVertex <= 0);
			
			Graph = creation(numberOfVertex);
			
			printf("\nGraphe créé avec succès !\n");
			
			menu();
			
			break;
		case 2 : 
            
            showSavedGraph();
			printf("Veuillez saisir le nom du fichier [fichier.txt]: ");
			
			fgets(line,200,stdin);
			sscanf(line,"%s",filename);
			
			if (lecture(filename) == ErrorFile) {
				
				printf("Erreur d'ouverture du fichier \n");
				waitCharEntry();
				
				mainMenu(); }
			
			else
			{
				mainMenu();
			}
			break;
			
		case 3:
		    //ShowRetrieveData();
		    ShowFordFulkersonAutomatic();
		    break;
		
		case 4:
		    printf("Au revoir et a bientot!...\n");
			exit(0);
			break;
	}
}


/*
 * La fonction menu affiche les diverses operations de traitement du graphe.
 */
static void menu(){
	
	char line[3]; 
	
	int option;     
	
	int cpt;     
	
	printf("\n\n\n");
	printf(  "________________________________________________\n" );
	
    printf(  "|                   MENU GRAPHE                |\n" );
    
    printf(  "|______________________________________________|\n" );
    
	printf(  "|	Tapez 1 : Pour afficher le graphe......|\n");
	
	printf(  "|	Tapez 2 : Pour inserer un sommet.......|\n");
	
	printf(  "|	Tapez 3 : Pour inserer une arête.......|\n");
	printf(	 "|	Tapez 4 : Pour supprimer un sommet.....|\n");
	
	printf(	 "|	Tapez 5 : Pour supprimer une arête.....|\n");
	printf(	 "|	Tapez 6 : Pour sauvegarder le graphe...|\n");
	
	printf(	 "|	Tapez 7 : Pour charger le graphe.......|\n");
	printf(  "|	Tapez 8 : Pour calculer le flowMax.....|\n");
	printf(  "|	Tapez 9 : Pour recuperer les donnees du graphe...|\n");
	printf(  "|	Tapez 0: Pour quitter.................|\n" );
	printf(  "|______________________________________________|\n" );
	
	do {
		printf("Veuillez choisir un numéro pour l'opération du graphe: ");
		
		fgets(line,2,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%d",&option);
		
	} while (cpt != 1 || option < 0 || option > 9);
	
	switch (option){
		
	case 1 :
		displayGraphe();
		
		break;
		
	case 2 :
	
		insertVertex();
		
		break;
		
	case 3 :
	
		insertRidge();
		
		break;
		
	case 4 :
	
		deleteVertex();
		
        break;
        
	case 5 :
	
		deleteRidge();
		
        break;
        
	case 6 :
	
		saveGraphe();
		
        break;
        
    case 7 :
    
		loadGraphe();
		
		break;
		
	case 8 :
		
		ShowFordFulkerson();
		
		break;
		
	
	case 9 :
	
	     //ShowRetrieveData();
	     ShowFordFulkersonAutomatic();
	     break;
	
	case 0 :
		
		leave();
		
		break;
	}
	
	menu();
}

/*
static void ShowRetrieveData()
{
	char filename[201]; 
	
	char line[201]; 
	
	int codeLecture;
	
    do {
			showSavedGraph();
			
			printf("Veuillez saisir le nom du fichier [fichier.txt] : ");
			
			fgets(line,200,stdin);
			
			sscanf(line,"%s",filename);
			
			codeLecture = retrieve(filename);
			
			
			if (codeLecture == ErrorFile) {
				
				printf("Erreur d'ouverture du fichier \n");
				
			}
		}
		while (codeLecture == ErrorFile);
	
}*/

/* 
 * La Fonction fait un remplissage automatique de la matrice ainsi que
 * le calcul du flot maximum du graphe sauvegarde dans un fichier txt
 * */
static void	ShowFordFulkersonAutomatic(){
	
	char filename[201]; 
	
	char line[201]; 
	
	int  codeLecture;
			  
		do {
			showSavedGraph();
			
			printf("Veuillez saisir le nom du fichier [fichier.txt] : ");
			
			fgets(line,200,stdin);
			
			sscanf(line,"%s",filename);
			
			codeLecture = retrieve(filename);
			    	
			if (codeLecture == ErrorFile) {
				
				printf("Erreur d'ouverture du fichier \n");
				
			}
		}
		while (codeLecture == ErrorFile);
	
}

/*
	* La fonction ShowFordFulkerson permet d'afficher le flow max du graphe créé
	*/
static void	ShowFordFulkerson(){
	
	if (orient == 'o'){
	do{
			printf("Veuillez saisir la source:\n");
			scanf("%d",&source);
			printf("Veuillez saisir le puit:\n");
			scanf("%d",&puit);
		  }while((source<1||source>Max)&&(puit<1||puit>Max));
		  
		maxflow = fordFulkerson(Matrix, source, puit, Max);
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
}

	/*
	* La fonction displayGraphe permet d'afficher le graphe créé
	*/
	
static void displayGraphe() {
	
	printf("\n  Structure du graphe  \n\n");
	
	affichage(Graph,orient);
	
	waitCharEntry();
}


	/*
	* La fonction insertVertex permet d'insérer un sommet dans le graphe créé.
	*/
	
static void insertVertex() {
	
	int cpt; 
	
	int numberOfVertex;  
	
	char line[11];  
	
	printf("\n===Insérer un sommet ===\n\n");
	
	do {
		printf("Saisissez le numéro du sommet : ");
		
		fgets(line,10,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%d",&numberOfVertex);
		
	} while (cpt != 1);
	
	
	switch(insertionSommet(Graph,numberOfVertex)) {
		case ExistentVertex :
		
			printf("Erreur : le sommet %d existe déjà dans le graphe\n",numberOfVertex);
			
			waitCharEntry();
			break;
			
		case InvalideVertex :
		
			printf("Erreur : le sommet doit être compris entre 1 et %d\n",Graph->nbrMaxSommets);
			
			waitCharEntry();
			break;
		case 0 :
		
			printf("Le sommet %d a bien été inséré dans le graphe.\n",numberOfVertex);
			
			waitCharEntry();
			break;
	}
}


	/*
	* La fonction insertRidge permet d'insérer une arête dans le graphe créé.
	*
	*/
static void insertRidge() {
	
	int ridgeWeight;  
	
	int vertexDepart;  
	
	int vertexArrivee; 
	
	char line[11]; 
	   
	int cpt; 
	
	char orientedRidge;   

	printf("\n   Insérer une arête  \n\n");
	
	do {
		printf( "Est-ce une arête orientée ? (o/n) " );
		
		fgets(line,2,stdin);
		ClearString(line);
		cpt = sscanf(line,"%c",&orientedRidge);
		
		orient = orientedRidge;
		
	} while (cpt != 1 || (orientedRidge != 'o' && orientedRidge != 'n'));
	
	do {
		printf("Veuillez saisir le sommet de départ : ");
		
		fgets(line,10,stdin);
		ClearString(line);
		
		cpt = sscanf(line,"%d",&vertexDepart);
		
	} while (cpt != 1);
	
	do {
		printf("Veuillez saisir le sommet d'arrivée : ");
		
		fgets(line,10,stdin);
		ClearString(line);
		
		cpt = sscanf(line,"%d",&vertexArrivee);
		
	} while (cpt != 1);
	
	do {
		printf("Veuillez saisir le poids de l'arête : ");
		
		fgets(line,10,stdin);
		ClearString(line);
		
		cpt = sscanf(line,"%d",&ridgeWeight);
		
	} while (cpt != 1);
	
	if (orientedRidge == 'o') {
		
		/*Remplissage de la matrix*/
		
			Matrix[vertexDepart][vertexArrivee] = ridgeWeight;
		/*Affichage de la matrix*/
			int i,j;
				printf("voici la matrice obtenu après l'insertion:\n");
					for(i=1; i <= Max ; i++){
						for(j=1; j <= Max ; j++){
							printf("%d\t",Matrix[i][j]);
						} printf("\n");
					}
				
		switch (insertionAreteOriente(Graph,vertexDepart,vertexArrivee,ridgeWeight)) {
			
			case NonExistentVertex  :
			
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				
				waitCharEntry();
				break;
				
			case ExistentRidge :
			
				printf("Erreur : l'arête demandée existe déjà dans le graphe\n");
				
				waitCharEntry();
				break;
				
			case 0 :
				printf("L'arête (%d,%d) a bien été insérée dans le graphe\n",vertexDepart,vertexArrivee);
				
				waitCharEntry();
				break;
		}
	}
	else {
		switch (insertionAreteNonOriente(Graph,vertexDepart,vertexArrivee,ridgeWeight)) {
			
			case NonExistentVertex :
			
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				waitCharEntry();
			
				break;
			
			case ExistentRidge :
			
				printf("Erreur : l'arête demandée existe déjà dans le graphe\n");
				waitCharEntry();
			
				break;
			
			case 0 :
				printf("L'arête non orientée (%d,%d) a bien été insérée dans le graphe\n",vertexDepart,vertexArrivee);
				
				waitCharEntry();
				
				break;
		}
	}
}


	/*
	* La fonction deleteVertex permet de supprimer un sommet du graphe.
	*/
	
static void deleteVertex() {
	
	int numberOfVertex;   
	char line[11];  
	int cpt;     

	printf("\n  Suppression sommet   \n\n");
	
	do {
		printf("Veuillez saisir le sommet à supprimer : ");
		
		fgets(line,10,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%d",&numberOfVertex);
		
	} while (cpt != 1);
	
	switch (suppressionSommet(Graph,numberOfVertex)) {
		
		case NonExistentVertex :
		
			printf("Erreur : le sommet %d n'existe pas dans le graphe\n",numberOfVertex);
			
			waitCharEntry();
			break;
			
		case 0 :
		
			printf("Le sommet %d a bien été supprimé du graphe\n",numberOfVertex);
			
			waitCharEntry();
			break;
	}
}


	/*
	* La fonction deleteRidge permet de supprimer une arête du graphe créé.
	*/
	
static void deleteRidge() {
	
	char orientedRidge;  
	
	int Sommet1; 
	   
	int Sommet2;   
	
	char line[11];    
	 
	int cpt;     

	printf("\n   Supprimer une arête   \n\n");
	
	do {
		printf( "Est-ce une arête orientée ? (o/n) " );
		
		fgets(line,2,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%c",&orientedRidge);
		
	} while (cpt != 1 || (orientedRidge != 'o' && orientedRidge != 'n'));
	
	do {
		printf("Saisissez le sommet de départ : ");
		
		fgets(line,10,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%d",&Sommet1);
		
	} while (cpt != 1);
	
	do {
		printf("Saisissez le sommet d'arrivée : ");
		
		fgets(line,10,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%d",&Sommet2);
		
	} while (cpt != 1);
	
	if (orientedRidge == 'o') {
		
		switch (suppressionArete(Graph,Sommet1,Sommet2,'o')) {
			
			case NonExistentVertex :
			
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				waitCharEntry();
				
				break;
				
			case NonExistentRidge :
			
				printf("Erreur : l'arête demandée n'existe pas dans le graphe\n");
				waitCharEntry();
				
				break;
				
			case 0 :
			
				printf("L'arête (%d,%d) a bien été supprimée du graphe\n", Sommet1, Sommet2);
				waitCharEntry();
				
				break;
		}
	}
	else {
		switch (suppressionArete(Graph,Sommet1,Sommet2,'n')) {
			
			case NonExistentVertex :
			
				printf("Erreur : un des sommets entrés n'existe pas dans le graphe\n");
				waitCharEntry();
				
				break;
				
			case NonExistentRidge :
			
				printf("Erreur : l'arête demandée n'existe pas dans le graphe\n");
				waitCharEntry();
				
				break;
				
			case 0 :
			
				printf("L'arête non orientée (%d,%d) a bien été supprimée du graphe\n",Sommet1,Sommet2);
				waitCharEntry();
				
				break;
		}
	}
}


	/*
	* La fonction saveGraphe permet de sauvegarder le graphe créé dans un fichier.
	*/
	
static void saveGraphe() {
		

	char path[201];  
	
	char pathToSave[250] = "Graphe/";
	  
	char line[201];
	
	FILE* fichier;

	printf("\n  Sauvegarde du graphe  \n\n");

	printf("Veuillez saisir le nom du fichier [fichier.txt] : ");
	
	fgets(line,200,stdin);
	
	sscanf(line,"%s",path);
	
	strcat(pathToSave,path);
	
	fichier = fopen(pathToSave,"a");
	
	if (fichier != NULL) {
		
		sauvegarde(Graph, fichier,orient);
		
		if (fclose(fichier) != EOF) {
			
			printf("Le graphe a été sauvegardé avec succès.\n");
			waitCharEntry();
		}
		
		else {
			
			printf("Erreur lors de la fermeture du fichier.\n");
			waitCharEntry();
		}
	}
	else {
		
		printf("Erreur lors de l'ouverture du fichier.\n");
		waitCharEntry();
		
	}
}


/*
* La fonction loadGraphe permet de charger le graphe sauvegardé
* 
*/
static void loadGraphe() {
	char filename[201]; 
	
	char line[201]; 
	
	int codeLecture; 
	int cpt;        
	 
	char continuer;   
	
	printf("\n Chargement du graphe   \n\n");
	
	printf("\b Attention, le graphe en cours sera supprimé \n");
	
	do {
		printf("Etes-vous sûr de vouloir charger un autre graphe ? (o/n) ");
		
		fgets(line,2,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%c",&continuer);
		
	} while (cpt != 1 || (continuer != 'o' && continuer != 'n'));
	
	if (continuer == 'o') {
		
		deleteGraphe(Graph);
		
		do {
			showSavedGraph();
			printf("Veuillez saisir le nom du fichier [fichier.txt] : ");
			
			fgets(line,200,stdin);
			
			sscanf(line,"%s",filename);
			
			codeLecture = lecture(filename);
			
			
			if (codeLecture == ErrorFile) {
				
				printf("Erreur d'ouverture du fichier \n");
				
			}
		}
		while (codeLecture == ErrorFile);
	}
}


	/*
	* La fonction leave permet de quitter totalement le programme et de supprimer le graphe
	* 
	*/
static void leave() {
	
	char line[3];   
	 
	int cpt;
	char continuer;       

	printf("\b Attention, le graphe en cours sera supprimé \n");
	do {
		printf("Etes-vous sûr de vouloir quitter ? (o/n) ");
		fgets(line,2,stdin);
		
		ClearString(line);
		
		cpt = sscanf(line,"%c",&continuer);
		
	} while (cpt != 1 || (continuer != 'o' && continuer != 'n'));
	
	if (continuer == 'o') {
		
		deleteGraphe(Graph);
		
		printf ( "\nAu revoir et a bientot!...\n\n" );
		exit(0);
	}
}


	/*
	* La fonction ClearString permet de supprimer une occurence de saisie au clavier
	* 
	*/
static void ClearString (const char *chaine) {
	char *aff;
	int c;

	aff = strchr(chaine,'\n');
	
    if (aff) {  aff = NULL;  }
    
    else {  while ((c = getchar()) != '\n' && c != EOF);  }
}


	/*
	* La fonction : waitCharEntry permet attendre une occurence de l'utilisateur
	* 
	*/
static void waitCharEntry() {
	int c;
	
	printf("\n Veuillez taper [Entrer] pour continuer...\n");
	
	while ((c = getchar()) != '\n' && c != EOF);
}
