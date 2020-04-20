/**
*\file affichages.c
*\author Tudoret Aurélien

*\brief Contient les fonctions d'affichages pour les différents écrans du jeu

*/


#include "../Include/constantes.h"
#include "../Include/initialisation_sdl_fonctions.h"
#include "../Include/map.h"
#include "../Include/affichages.h"
#include "../Include/joueur.h"


/**
*\fn

*\param *rendu, le renderer sur lequel on dessine
*\param *map, la structure contenant toutes les informations liées à la map

*\brief Permet d'afficher tous les éléments présents à l'écran pendant la phase de jeu
*/
void affichage_jeu(SDL_Renderer *rendu, perso_t pers, map_t *map){

	SDL_RenderClear(rendu);

	affiche_map(rendu, map);

	affiche_joueur(pers, rendu);
	
	SDL_RenderPresent(rendu);
}