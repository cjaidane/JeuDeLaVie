/**
 *\file grille.h
 *\def __GRILLE_H
 *\author Chaïma JAIDANE
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 *\typedef typedef struct {int nbl; int nbc; int** cellules;} grille
 *\struct  structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
/**
 *\fn void alloue_grille (int l, int c, grille* g)
 *\brief alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 *
 */
void alloue_grille (int l, int c, grille* g);

/**
 *\fn void libere_grille (grille* g)
 *\brief libère une grille
 */
void libere_grille (grille* g);

/**
 *\fn void init_grille_from_file (char * filename, grille* g)
 *\brief alloue et initalise la grille g à partir d'un fichier
 */
void init_grille_from_file (char * filename, grille* g);

/**
 *\fn static inline void set_vivante(int i, int j, grille g)
 *\brief  rend vivante la cellule (i,j) de la grille g
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 \fn static inline void set_morte(int i, int j, grille g)
 \brief rend morte la cellule (i,j) de la grille g
*/
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
// teste si la cellule (i,j) de la grille g est vivante
/**
 \fn static inline void set_non_viable(int i, int j, grille g)
 \brief la cellule n'est pas vivante et est marqué par la valeur -1
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j]= -1;}


/**
 \fn static inline int est_vivante(int i, int j, grille g)
 \brief verifie si la cellule est vivante
*/
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] > 0;}

/**
 \fn void copie_grille (grille gs, grille gd)
 \brief recopie gs dans gd (sans allocation)
*/
void copie_grille (grille gs, grille gd);

/**
 \fn int test_grille_oscillation(grille g, grille gc)
 \brief compare si 2 grilles sont identiques ou non
*/
int test_grille_oscillation(grille g, grille gc);

/**
 \fn int oscillation(grille g)
 \brief test si une grille est oscillante ou non
*/
int oscillation(grille g);

/**
 \fn int grille_vide(grille g)
 \brief test si une grille est vide ou non
*/
int grille_vide(grille g);

extern int vieillissement;

#endif
