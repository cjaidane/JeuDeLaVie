/**
 \file jeu.h
 \author Chaïma JAIDANE
 \define  __IO_H
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 \fn void affiche_trait (int c)
 \brief affichage d'un trait horizontal
 \param c, un entier
*/
 void affiche_trait (int c);

/**
 \fn void affiche_ligne (int c, int* ligne)
 \brief affichage d'une ligne de la grille
 \param c, un entier
 \param ligne, un tableau d'entier
*/
void affiche_ligne (int c, int* ligne);


/**
 \fn void affiche_grille (grille g)
 \brief affichage d'une grille
 \param g, une grille de type grille
*/
void affiche_grille (grille g);

/**
 \fn void efface_grille (grille g)
 \brief effacement d'une grille
 \param g, une grille de type grille
*/
void efface_grille (grille g);

/**
 \fn void debut_jeu(grille *g, grille *gc)
 \brief debute le jeu
 \param g, une grille de type grille
 \param gc, une grille de type grille
*/void debut_jeu(grille *g, grille *gc);


extern int cyclique;
extern int periode;
#endif
