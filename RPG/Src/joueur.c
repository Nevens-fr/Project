/**
*\file joueur.c
*\author Tudoret Aurélien

*\brief Contient les fonctions liées au joueur, initialisation, chargement...

*/

#include "../Include/constantes.h"
#include "../Include/initialisation_sdl_fonctions.h"
#include "../Include/joueur.h"
#include "../Include/map.h"


/**
*\fn void init_joueur(perso_t *pers, SDL_Renderer *rendu)

*\param *pers, structure du joueur
*\param *rendu, le renderer sur lequel on dessine

*\brief Initialise les valeurs de bases du joueur et charge ses sprites
*/
void init_joueur(perso_t *pers, SDL_Renderer *rendu){

	pers->pv = PV_DEPART_JOUEUR;
	pers->pv_old = PV_DEPART_JOUEUR;
	pers->pv_max = PV_DEPART_JOUEUR;

	pers->x = EMPLACEMENT_DEPART_JOUEUR_X;
	pers->y = EMPLACEMENT_DEPART_JOUEUR_Y;

	charge_sprite_joueur(pers, rendu);

	pers->sprites.a_dessiner.w = 32;
	pers->sprites.a_dessiner.h = 55;
	pers->sprites.a_dessiner.x = 0;
	pers->sprites.a_dessiner.y = 0;
}


/**
*\fn void charge_sprite_joueur(perso_t *pers, SDL_Renderer *rendu)

*\param *pers, structure du joueur
*\param *rendu, le renderer sur lequel on dessine

*\brief Charge les sprites du joueur
*/
void charge_sprite_joueur(perso_t *pers, SDL_Renderer *rendu){

	charge_image(JOUEUR_PATH, &pers->sprites, rendu);
}



/**
*\fn void affiche_joueur(perso_t pers, SDL_Renderer *rendu)

*\param pers, structure du joueur
*\param *rendu, le renderer sur lequel on dessine

*\brief Affiche le sprite courant du joueur à l'écran
*/
void affiche_joueur(perso_t pers, SDL_Renderer *rendu){

	update_coordonnees_sprite_joueur(&pers);

	SDL_RenderCopy(rendu, pers.sprites.img, &pers.sprites.a_dessiner, &pers.sprites.rectangle);
}



/**
*\fn void update_coordonnees_sprite_joueur(perso_t *pers)

*\param *pers, structure du joueur

*\brief Actualise les coordonnées du sprite du joueur à l'écran
*/
void update_coordonnees_sprite_joueur(perso_t *pers){

	pers->sprites.rectangle.x = pers->x;
	pers->sprites.rectangle.y = pers->y;
}




/**
*\fn int collision_trouvee(perso_t pers, SDL_Rect tab[], int taille, int x, int y)

*\param pers, structure du joueur
*\param tab[], tableau des collisions de la map
*\param taille, taille du tableau de collisions
*\param x, position x du joueur en cas de déplacement
*\param y, position y du joueur en cas de déplacement

*\return TRUE si une collision est détectée

*\brief Actualise les coordonnées du sprite du joueur à l'écran
*/
int collision_trouvee(perso_t pers, SDL_Rect tab[], int taille, int x, int y){

	pers.x = x;
	pers.y = y;

	update_coordonnees_sprite_joueur(&pers);

	for(int i = 0; i < taille; i++){

		if(SDL_HasIntersection(&pers.sprites.rectangle, &tab[i]))
			return TRUE;
	}

	return FALSE;
}


/**
*\fn void deplacement_joueur(perso_t *pers, touches_t clavier, map_t map)

*\param *pers, structure du joueur
*\param clavier, structure contenant les touches du clavier utilisées par le jeu
*\param map, structure contenant la map

*\brief Actualise les coordonnées du sprite du joueur à l'écran
*/
void deplacement_joueur(perso_t *pers, touches_t clavier, map_t *map){

	if(clavier.tab[down] == TRUE){

		if(!collision_trouvee(*pers, map->collisions, map->nb_coll, pers->x, pers->y + VITESSE_JOUEUR*2) && !hors_tableau(map->x, map->y)){

			pers->y += VITESSE_JOUEUR;
			map->y += VITESSE_JOUEUR;
		}
	}
	else if(clavier.tab[up] == TRUE){

		if(!collision_trouvee(*pers, map->collisions, map->nb_coll, pers->x, pers->y - VITESSE_JOUEUR*2) && !hors_tableau(map->x, map->y)){

			pers->y -= VITESSE_JOUEUR;
			map->y -= VITESSE_JOUEUR;
		}
	}
	else if(clavier.tab[right] == TRUE){

		if(!collision_trouvee(*pers, map->collisions, map->nb_coll, pers->x + VITESSE_JOUEUR*2, pers->y) && !hors_tableau(map->x, map->y)){

			pers->x += VITESSE_JOUEUR;
			map->x += VITESSE_JOUEUR;
		}
	}
	else if(clavier.tab[left] == TRUE){

		if(!collision_trouvee(*pers, map->collisions, map->nb_coll, pers->x - VITESSE_JOUEUR*2, pers->y) && !hors_tableau(map->x, map->y)){

			pers->x -= VITESSE_JOUEUR;
			map->x -= VITESSE_JOUEUR;
		}
	}
}