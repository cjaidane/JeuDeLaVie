/**
 * \file : jeu.c
 * \author Chaïma JAIDANE
 * \brief possède la fonction qui affiche l'évolution de la grille et les fonctions qui détermine le mode cyclique ou on
 */

#include "jeu.h"
#include "grille.h"


/**
 *\fn int compte_voisins_vivants_cyclique (int i, int j, grille g)
 * Cette fonction prend en parametre deux entier i et j de type entier et une grille g de type grille:
 *       \param i, un entier
 *       \param j, un entier
 *       \param g, une grille de type grille
 * \brief Elle compte le nombre de voisin vivant en mode cyclique (quand il est activé)
 * Elle traite 8 cas pour le nombre de voisin q'une cellule peut avoir
 * \return Elle retourne v, un \b entier qui possède le nombre de voisin vivant
 */ 

int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
  
    v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
    v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
    v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
    v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
    v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
    v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
    v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
    v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
  
	return v; 
}

/**
 *\fn int compte_voisins_vivants_non_cyclique(int i, int j,grille g)
 * Cette fonction prend en parametre deux entier i et j de type entier et une grille g de type grille
 *      \param i, un entier
 *      \param j, un entier
 *      \param g, une grille de type grille
 * \brief Elle compte le nombre de voisin vivant en mode non  cyclique (quand il est activé)
 * Elle traite 8 cas pour le nombre de voisin q'une cellule peut avoir
 * \return Elle retourne w, un \b entier  qui possède le nombre de voisin vivant
 */
int compte_voisins_vivants_non_cyclique(int i, int j,grille g){
    int w=0;
    
    if(i<(g.nbl-1) && j<(g.nbc-1)){
        w+=est_vivante((i+1),(j+1),g);
    }
    if(i<(g.nbl-1)){
        w+=est_vivante((i+1),j,g);
    }
    if(i<(g.nbl-1) && j>0){
        w+=est_vivante((i+1),(j-1),g);
    }
    if(j<(g.nbc-1)){
        w+=est_vivante(i,(j+1),g);
    }
    if(i>0 && j>0){
        w+=est_vivante((i-1),(j-1),g);
    }
    if (i>0){
        w+=est_vivante((i-1),j,g);
    }
    if (i>0 && j<(g.nbc-1)){
        w+=est_vivante((i-1),(j+1),g);
    }
    if(j>0){
        w+=est_vivante(i,(j-1),g);
    }
   
    return w;
    }

/**
 *\fn void evolue (grille *g, grille *gc)
 * Cette fonction prend en paramètre deux grilles, g et gc de type grilles:
 *      \param g, un pointeur sur grille
 *      \param gc, un pointeur sur grille
 * \brief Elle permet de voir l'évolution du tableau à chaque entrée de clavier
 * Un pointeur de fonction est utilisé
 * \return la valeur de retour est un entier 
 */

int (*compte_voisins_vivants)(int, int, grille)=compte_voisins_vivants_cyclique;
int viellissement=0;
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
    
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
            if(g->cellules[i][j]!=-1)
            {
     
            v =(*compte_voisins_vivants)(i, j, *gc);
                if (est_vivante(i,j,*g)) 
                {
			    // evolution d'une cellule vivante
                    if( v!=2 && v!= 3 ){
                        set_morte(i,j,*g);
                    } 
                    else if(viellissement==0){
                        g->cellules[i][j]+=1; 
                    }else{
                        (g->cellules[i][j]=1);
            
                    }
                    if(vieillissement==1){
                        if (g->cellules[i][j]>8) set_morte(i,j,*g); 
                    }
                                          
                
                }
            else 
			    { // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			    }
            }
        
	    }

    }
	return;
}