
/**
 * \file : io.c
 * \define N 500
 * \author Chaïma JAIDANE
 * \brief l'affichage des grilles et du debut du jeu
 */

#include <stdio.h>
#include <stdlib.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>


#define SIZEX 600
#define SIZEY 600

#define SIZE_CARRE 30
#define SIZE_ESPACE_ENTRE_C 5
#define HAUTEUR 30
#define LARGEUR 30
#include "io.h"

#define N 500
static int temps_evol=0;
int vieillissement=0;
int cyclique=1; //cyclique est activé
int periode=1;//periode oscillation activée
/**
 *\fn  void affiche_trait (int c)
 * Cette fonction prend en argument un entier c, qui correspond au colonne:
 *       \param c, un entier correspond au colonne
 * \brief Elle permet d'afficher les traits de la grille.
 */ 
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}


/**
 *\fn void affiche_ligne (int c, int* ligne)
 *Cette fonction prend en argument deux  entiers c(colonne) et  ligne:
 *      \param c, un entier qui correspond au colonne
 *      \param ligne, un tableau d'entier correspond au ligne
 *\brief Elle permet d'afficher les lignes de la grille quand le vieillissement est activé ou non
 */ 
 
void affiche_ligne (int c, int* ligne){
    int i;
    if(vieillissement==0){
        for (i=0; i<c; ++i)
            if (ligne[i] == 0 ) printf ("|   "); 
            else if(ligne[i]==-1) printf ("| X ");
            else printf ("| O ");printf("|\n");
        
    }else{
        for(i=0; i<c; ++i)
            if (ligne[i]==0) printf("|   "); 
            else if (ligne[i]==-1) printf("| X ");
            else printf("| %d ",ligne[i]); printf("|\n");
            }
    
	return;
}

/**
 * \fn void affiche_grille (grille g)
 * Cette fonction prend en argument une grille g de type grille:
 *      \param g type grille, grille sur laquelle utilisateur à décider de travailler
 * \brief Elle affiche la grille complète en utilisant les deux fonctions précedente affiche_trait et affiche_ligne
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	//printf("\n");
    printf("Le temps d'évolution est de :%d\n", temps_evol);
    printf("\n");
	affiche_trait(c);
    
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n");
	return;
}

/**
 *\fn void efface_grille (grille g)
 * Cette fonction prend en argument une grille g  de type grille:
 *      \param g de type grille,  grille sur laquelle utilisateur à décider de travailler
 * \brief Elle permet d'effacer la grille.
 */ 
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 *\fn void debut_jeu(grille *g, grille *gc)
 *Cette fonction prend en parametre  deux grilles g et gc de types grilles:
 *      \param g , une grille de type grille
 *      \param gc, une autre grille de type grille
 *\brief Elle permet de :
 *  changer de grille et d'afficher l'évolution de la grille
 *  d'afficher la grille en mode cyclique ou non cyclique à l'aide d'un pointeur de fonction
 *  activer/ désactiver le vieillisement de la grille à l'aide d'un pointeur de fonction
 */
void debut_jeu(grille *g, grille *gc){
   
   
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{
        // touche "entree" pour évoluer
                system("clear");
                temps_evol++;
                evolue(g,gc);
                efface_grille(*g);
                affiche_grille(*g);
                printf("Le système est: %s\n",(cyclique==1) ? "Cyclique" : "Non cyclique");
                printf("Le vieillissement est: %s\n",(vieillissement==1) ?  "activé" : "désactivé");
                if(periode==0){
                    if(oscillation(*g)==0){
                        printf("La grille n'oscille pas\n");
                    }else{
                        printf("La grille oscille et sa période est de %d\n",oscillation(*g));
                    }
                }
                break;
            }
        
			case'n':{
        //touche pour changer de grilles
				libere_grille(g);
				libere_grille(gc);
				char tab[N];
				printf("Donner une nouvelle grille\n");
				scanf("%s", tab);
                temps_evol=0;
                printf("\n");
				init_grille_from_file(tab,g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g);
                break;
			}
                
            case 'c':{
        //touche pour mettre une grille en mode cyclique ou non
                
                if(cyclique==0){
                    compte_voisins_vivants=&compte_voisins_vivants_cyclique;
                    cyclique =1;
                   
                }else{
                    compte_voisins_vivants=&compte_voisins_vivants_non_cyclique;
                    cyclique=0;
                }
                
                break;
            }
                
            case 'v':{
        //touche pour activer/desactiver le vieillissement et afficher age de la cellule
               
                if (vieillissement==0)
                {
                    vieillissement=1;
                    
                }else{
                    vieillissement=0;
                    
                }
                efface_grille(*g);
                affiche_grille(*g);
                break;
            }
            
            case 'o':{
                getchar();
                if(periode==1){
                    periode=0;
                }else{
                    periode=1;
                    oscillation(*g);
                }
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
