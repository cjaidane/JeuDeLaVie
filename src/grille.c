/**
 * \file : grille.c
 * \author Chaïma JAIDANE
 * \brief alloue, libere, initialise et copie une grille
 */


#include "../include/grille.h"
#include "../include/jeu.h"


/**
 *\fn void alloue_grille(int l, int c, grille *g)
 *\brief Cette fonction alloue une grille et met les cellues à morte
 * Elle prend en parametre une grille de type grille et deux entiers l qui correspond au nombre de ligne et c qui correspond au nombre de colonne:
 *      \param l, un eniter qui correspond à une ligne
 *      \param c, un entier qui correspond à une colonne
 *      \param g, une grille de type grille
 * la grille est de taille l*c
 */

void alloue_grille(int l, int c, grille *g){
    g->nbl=l;
    g->nbc=c;
    g->cellules=(int **)malloc(sizeof(int*)*l);
    for(int i=0; i<l; i++){
        g->cellules[i]=(int*)malloc(c*sizeof(int));// pour chaque ligne alloue de la mémoire
        for(int j=0; j<c; j++){
            set_morte(i,j,*g);//pour chaque colonne du coup va mettre des cellules mortes+ code deja definie
        }
            
    }
}

/**
 *\fn void libere_grille (grille* g)
 *\brief Cette fonction libère une grille
 * Elle prend donc en paramètre une grille:
 *      \param g, une grille de type grille
*/
void libere_grille (grille* g){
    int x= g->nbl;
    for(int i=0; i<x; i++){
        free(g->cellules[i]);
    }
    free(g->cellules);
}

/**
 *\fn void init_grille_from_file (char * filename, grille* g)
 *\brief Cette fonction  alloue et initalise la grille g à partir d'un fichier
 * Elle prend en argument une grille g de type grille et filename de type char:
 *      \param g, une grille g de type grille
 *      \param filename, de type char
 * Elle utilise la fonction alloue_grille pour allouer de l'espace
 */
void init_grille_from_file (char * filename, grille* g){
    FILE * pfile = NULL;
    pfile = fopen(filename, "r");
    assert (pfile != NULL);
    
    int i,j,n,l,c,vivantes,p=0;
    fscanf(pfile, "%d", & l);
    fscanf(pfile, "%d", & c);
    
    alloue_grille(l,c,g);
    
    fscanf(pfile, "%d", & vivantes);
    for (n=0; n< vivantes; ++n){
        fscanf(pfile, "%d", & i);
        fscanf(pfile, "%d", & j);
        set_vivante(i,j,*g);
    }
    int non_viable=0;
    fscanf(pfile, "%d", &non_viable);// des que j'enleve ca ca marche mais apres j'ai plus de X
	for (p=0; p < non_viable; ++p){
	fscanf(pfile, "%d", &i);
	fscanf(pfile, "%d", &j);
	set_non_viable(i,j,*g);
    }
	fclose (pfile);
	return;
}


/**
 *\fn void copie_grille (grille gs, grille gd)
 * \brief Cette fonction permet de copier une grille dans une autre grille
 * Elle prend en parametre 2 grilles gs et gd de type grille:
 *       \param gs, une grille de type grille
 *       \param gd, une grille de type grille
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

/**
 *\fn int test_grille_oscillation(grille g, grille gc)
 * \brief Cette fonction permet de comparer deux grilles
 * Elle prend en parametre 2 grilles g et gc de type grille:
 *       \param g, une grille de type grille
 *       \param gc, une grille de type grille
 */

 
int test_grille_oscillation(grille g, grille gc){
    for(int i=0; i<g.nbl; i++){
        for(int j=0; j<g.nbc; j++){
            if(est_vivante(i,j,g) != est_vivante(i,j,gc)){
                return 0;
            }
        }
    }
    return 1;
}

/**
 *\fn int grille_vide(grille g)
 * \brief Cette fonction permet de tester si une grille est vide
 * Elle prend en parametre 1 grille g
 *       \param g, une grille de type grille
 */
int grille_vide(grille g){
    for(int i=0; i<g.nbl; i++){
        for(int j=0; j<g.nbc; j++){
            if(est_vivante(i,j,g)){
                return 0;
            }
        }
    }
    return 1;
}

/**
 *\fn int oscillation(grille g)
 * \brief Cette fonction permet de tester l'oscillation d'une grille
 * Elle prend en parametre 1 grille g
 *       \param g, une grille de type grille
 */
int oscillation(grille g){
    grille g1, g2;
    int tmp_oscill=1;

    alloue_grille(g.nbl,g.nbc,&g1);
    copie_grille(g,g1);

    alloue_grille(g1.nbl,g1.nbc,&g2);
    copie_grille(g1,g2);
    int max_iteration=1000;
    for(int i=0 ; i<max_iteration; i++){
            evolue(&g1,&g2);//1000 itérations
            if(test_grille_oscillation(g1,g)){
                break;
            }
            else if(grille_vide(g1)){
                break;
                
            }
            else{
                //evolue(&g1,&g2);
                tmp_oscill++;
            }

    }
    
    int vide = grille_vide(g1);
        if(vide){
            tmp_oscill = 0;
        }
    if(tmp_oscill>max_iteration){
        libere_grille(&g1);
        libere_grille(&g2);
        return tmp_oscill=0;
    }
    libere_grille(&g1);
    libere_grille(&g2);
    return tmp_oscill;
}
