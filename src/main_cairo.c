#include <stdio.h>
#include <stdlib.h>
#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>

#include "mode_cairo.h"
#include "grille.h"
#include "jeu.h"

#define SIZEX 600
#define SIZEY 600
#define N 200
/**
 * \file : main_cairo.c
 * \author Chaïma JAIDANE
 */


/**
 *\fn void jeu_cairo(grille *g , grille *gc)
 * Cette fonction prend en parametre deux grille g et gc de grille:
 *       \param g, une grille
 *       \param gc, une grille
 *  
 * \brief elle permet de controler tous les entrées clavier,le clic droit et gauche 
 */ 

void jeu_cairo(grille *g , grille *gc){

	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Jeu de la vie - Chaima JAIDANE");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);



	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs,*g);

		}
		if(e.type==ButtonPress && e.xkey.keycode==1){
				temps++;
				evolue(g,gc);
				paint(cs,*g);
				
			} 
		if(e.type==ButtonPress && e.xbutton.button==3) {
				break;
			}

		if(e.type==KeyPress){
		 	if(e.xkey.keycode==(XKeysymToKeycode(dpy,'n'))){
				libere_grille(g);
				libere_grille(gc);
				char tab[N];
				printf("Donner une nouvelle grille:\n");
				scanf("%s", tab);
				temps=0;
                printf("\n");
				init_grille_from_file(tab,g);
				alloue_grille(g->nbl, g->nbc, gc);
				paint(cs,*g);

			}
		
			if(e.xkey.keycode==(XKeysymToKeycode(dpy,'v'))){
                (vieillissement==0) ? (vieillissement=1) : ( vieillissement=0);
            }
			
			if(e.xkey.keycode==(XKeysymToKeycode(dpy,'c'))){
			

				if(cyclique==0){
                    compte_voisins_vivants=&compte_voisins_vivants_cyclique;
                    cyclique =1;
                   
                }else{
                    compte_voisins_vivants=&compte_voisins_vivants_non_cyclique;
                    cyclique=0;
                }
                
			}

			if(e.xkey.keycode==(XKeysymToKeycode(dpy,'o'))){
               grille_cairo_oscillante(*g,cs);
            }
	
		}
	}
	
	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display

}


int main (int argc, char **argv){

	if(argc != 2){
		printf("l'usage de : main_cairo <fichier grilles> \n");
		return 1;
	}
	// X11 display

	//initialise une grille
	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille(g.nbl, g.nbc, &gc);
	
	jeu_cairo(&g , &gc);

	libere_grille(&g);
	libere_grille(&gc);

    return 0;
}
