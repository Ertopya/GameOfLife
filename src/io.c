#include <string.h>
#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g, int tempsEvolution){
	int i, l=g.nbl, c=g.nbc;
	printf("Temps d'évolution : %d", tempsEvolution);
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int tempsEvolution = 1;
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {

			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution);
				tempsEvolution++;
				break;
			}

			case 'n' :
			{ // touche 'n' pour charger dynamiquement une nouvelle grille
				libere_grille(g);
				libere_grille(gc);

				char numeroGrille[19];
				printf("Entrez ->  grilles/grille<numero de la grille>.txt : ");
				scanf("%256s", numeroGrille);
				init_grille_from_file(numeroGrille, g);
				alloue_grille (g->nbl, g->nbc, gc);
				tempsEvolution = 0;
				printf("\n");
				affiche_grille(*g, tempsEvolution);
				printf("\n\e[2A");
				printf("\n");
				break;
			}

			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
