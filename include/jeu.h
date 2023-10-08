/**
 *\file grille.h
 *\author Chaïma JAIDANE
 *\define __JEU_H
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 *\fn int modulo(int i, int m)
 *\brief  modulo modifié pour traiter correctement les bords i=0 et j=0
 *\brief dans le calcul des voisins avec bords cycliques
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 *\fn compte_voisins_vivants_cyclique (int i, int j, grille g)
 *\brief compte le nombre de voisins vivants de la cellule (i,j)
 *\brief les bords sont cycliques.
*/
int compte_voisins_vivants_cyclique (int i, int j, grille g);

/**
 *\fn int compte_voisins_vivants_non_cyclique (int i, int j, grille g)
 *\brief compte le nombre de voisins vivants de la cellule(i,j)
 *\brief les bords sont non cycliques
*/
int compte_voisins_vivants_non_cyclique (int i, int j, grille g);

/**
 \fn int (*compte_voisins_vivants) (int , int , grille)
 \brief pointeur sur une fonction avec les arguments int int grille
 */
int (*compte_voisins_vivants) (int , int , grille);

/**
 *\fn void evolue (grille *g, grille *gc)
 *\brief fait évoluer la grille g d'un pas de temps
*/
void evolue (grille *g, grille *gc);

extern int cyclique;


#endif
