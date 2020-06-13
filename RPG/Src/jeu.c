/**
*\file jeu.c
*\author Tudoret Aurélien

*\brief Contient les appels aux fonctions principales permettant de jouer

*/


#include "../Include/constantes.h"
#include "../Include/initialisation_sdl_fonctions.h"
#include "../Include/map.h"
#include "../Include/jeu.h"
#include "../Include/joueur.h"
#include "../Include/clavier.h"
#include "../Include/affichages.h"



/**
*\fn void jeu_en_cours(perso_t *pers, SDL_Renderer *rendu, int *continuer, int *etat)

*\param *pers, la structure du personnage
*\param *rendu, le renderer sur lequel on dessine
*\param *continuer, integer permettant de tester si l'on continue le jeu ou pas
*\param *etat, integer permettant de passer par différents écrans (menu, jeu...)

*\brief Permet de passer par toutes les fonctions nécessaires au jeu.
*/
void jeu_en_cours(perso_t *pers, SDL_Renderer *rendu, int *continuer, int *etat){

//******************************* DECLARATION VARIABLES *****************************************************//

	map_t map;

	unsigned int clock = SDL_GetTicks();

	touches_t clavier;

//******************************* CHARGEMENT / INIT *********************************************************//

	init_tab_clavier(clavier.tab);

	charge_map(&map, rendu);

	rempli_tab_collision_map(&map);

	affichage_jeu(rendu, *pers, &map);

//******************************* BOUCLE DE JEU *************************************************************//

	while(*continuer && *etat == jeu){


		if(!clavier_vide(clavier)){//on actualise pas si il n'y pas de mouvement ou que le temps entre deux actualisations 
		//n'est pas écoulé

			if(clock_depasse(&clock)){
				rempli_tab_collision_map(&map);

				affichage_jeu(rendu, *pers, &map);

				deplacement_joueur(pers, clavier, &map);
			
				lire_clavier(&clavier);
			}
		} 
		else if(clock_depasse(&clock))
			lire_clavier(&clavier);

		if(clavier.tab[escape] == TRUE)
			*continuer = FALSE;
		
	}

//******************************* LIBERATION MEMOIRE ********************************************************//

	libere_texture(&map.texture.img);
}



/**
*\fn

*\param *clock, la variable contenant le temps écoulé

*\bief regarde si l'addition du temps et de du délai prévu entre deux actualisations de la clock

*\return TRUE si le délai est dépassé
*/
int clock_depasse(unsigned int *clock){

	if(*clock + DELAI_ACTUALISATION < SDL_GetTicks()){
		*clock = SDL_GetTicks();
		return TRUE;
	}
	else
		return FALSE;
}