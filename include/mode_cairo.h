#include <stdio.h>
#include <stdlib.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>


#include "jeu.h"
#include "grille.h"
#include "io.h"


extern int temps;
extern int *temps_evol;
extern int vieillissement;


/**
 \fn void paint(cairo_surface_t *surface, grille g)
 \brief affichage du jeu grâce à l'interface graphique
 \param *surface, de type cairo_surface_t
 \param g, une grille de type grille
*/
void paint(cairo_surface_t *surface, grille g);


/**
 \fn void grille_cairo_oscillante(grille g, cairo_surface_t *surface)
 \brief affiche texte si la grille est oscillante et donne la période
 \param *surface, de type cairo_surface_t
 \param g, une grille de type grille
*/
void grille_cairo_oscillante(grille g, cairo_surface_t *surface);
