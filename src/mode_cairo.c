/**
 * \file : io.c
 * \define N 500
 * \author Chaïma JAIDANE
 * \brief l'affichage des grilles et du debut du jeu
 */
#include <string.h>
#include <string.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>
#include "mode_cairo.h"
#include "jeu.h"
#include "grille.h"
#include "io.h"

#define SIZEX 600
#define SIZEY 600
#define TAILLE 400

#define SIZE_ESPACE_ENTRE_C 5
#define HAUTEUR 30
#define LARGEUR 30
/**
 * \file : mode_cairo.c
 * \define N 500
 * \author Chaïma JAIDANE
 * \brief l'affichage des grilles et du debut du jeu de l'affichqge graphique
 */

int temps=0;
int *temps_evol;
int oscil=0;


/**
 *\fn  void paint(cairo_surface_t *surface, grille g)
 * Cette fonction prend en argument 
 *       \param *surface, de type cairo_surface_t
 *		 \param g, une grille de type grille
 * \brief Elle permet d'afficher l'intégralité du jeu 
 */ 
void paint(cairo_surface_t *surface, grille g)
{
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.8, 0.4, 0.5);
	cairo_paint(cr);
	
	//Afficher la grille
    for (int i=0 ,x=70;  i<g.nbc ; i++, x+=35){
		for (int j=0,y=200; j<g.nbl; j++, y+=35){
			
 			cairo_set_source_rgb(cr,0.0,0.7,1);
            cairo_rectangle(cr,x , y , HAUTEUR, LARGEUR);
			//cairo_fill(cr);
			if(vieillissement==1){ 
				float couleur=(g.cellules[j][i])/10.0;
				if(g.cellules[j][i]==1){
					cairo_set_source_rgb(cr,1,0.75,0);
				}
				else if(g.cellules[j][i]>=1){
					cairo_set_source_rgb(cr,1,0.8-couleur,0.1);
				}else if (g.cellules[j][i]==-1){
					cairo_set_source_rgb(cr,0,0,0);
				}else{
					cairo_set_source_rgb(cr,1,1,1);
				}
				cairo_fill(cr);

			}else{
				if(g.cellules[j][i]==1){
				cairo_set_source_rgb(cr,1,0.75,0);
			}
			else if(g.cellules[j][i]>=1){
				cairo_set_source_rgb(cr,1,0.8,0.1);
			}else if (g.cellules[j][i]==-1){
					cairo_set_source_rgb(cr,0,0,0);
			}else{
				cairo_set_source_rgb(cr,1,1,1);
			}
			cairo_fill(cr);
			}
        }
    }
	//Affiche titre
	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 40);
	cairo_move_to(cr,150,35);
	cairo_set_source_rgb(cr,1,0.8,0.1);
	cairo_show_text(cr,"JEU DE LA VIE");

	//Affiche le temps d'evolution:
	cairo_select_font_face(cr,"Arial",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr,20);
	char temps_evol[5];
	sprintf(temps_evol, "%d",temps);
	cairo_move_to(cr,10,105);
	cairo_set_source_rgb(cr,1,1,1);
	cairo_show_text(cr,"Le temps d'évolution est: ");
	cairo_show_text(cr,temps_evol);


	//Afficher le texte du vieillissement 
	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 20);
	cairo_move_to(cr,10,130);
	cairo_show_text(cr,"Le viellissement est: ");
	cairo_set_source_rgb(cr,1,1,1);
	(vieillissement==0) ? cairo_show_text(cr,"DÉSACTIVÉ") : cairo_show_text(cr,"ACTIVÉ");

	
	//Afficher texte du cyclique
	cairo_select_font_face(cr,"Arial",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr,20.0);
	cairo_move_to(cr,10,155);
	cairo_show_text(cr,"Le système est: ");
	cairo_set_source_rgb(cr,1,1,1);
	(cyclique==0)? cairo_show_text(cr, " NON CYCLIQUE ") : cairo_show_text(cr, "CYCLIQUE");
	

	cairo_destroy(cr); // destroy cairo mask
}

/**
 *\fn  void grille_cairo_oscillante(grille g, cairo_surface_t *surface)
 * Cette fonction prend en argument 
 *       \param *surface, de type cairo_surface_t
 *		 \param g, une grille de type grille
 * \brief Elle permet d'afficher le texte d'oscillation si la grille est oscillante
 */ 
void grille_cairo_oscillante(grille g, cairo_surface_t *surface){
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	//Afficher l'oscillation
	cairo_select_font_face(cr,"Arial",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr,20);
	char temps_oscillation[5];
	int oscil = oscillation(g);
	sprintf(temps_oscillation, "%d",oscil);
	cairo_move_to(cr,10,180);
	cairo_set_source_rgb(cr,1,1,1);
	cairo_show_text(cr,"La période est de : ");
	cairo_show_text(cr,temps_oscillation);
	
}