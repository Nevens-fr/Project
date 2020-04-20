/**
*\file clavier.c
*\author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
*\date 04/02/2020
*\version 0.1

*\brief Gère toute les évènements au clavier
*/



#include "../Include/constantes.h"
#include "../Include/clavier.h"


/**
*\fn void init_tab_clavier(int tab[])

*\param tab[], le tableau contenant les touches du clavier

*\brief initialise le tableau d'evenement
*/
void init_tab_clavier(int tab[]){

	for(int i = 0; i < NB_TOUCHES_UTILISEES; i++)
		tab[i] = FALSE;
}

/**
*\fn void event_clavier(touches_t *clavier, SDL_Event event)

*\param *clavier, la structure contenant les touches du clavier

*\param event, l'evenement lu au clavier

*\brief Range dans un tableau les evenements lus au clavier
*/
void event_clavier(touches_t *clavier, SDL_Event event){

	if(event.type == SDL_KEYDOWN){

		if(event.key.keysym.sym == SDLK_UP){
			clavier->tab[up] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_DOWN){
			clavier->tab[down] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_RETURN){
			clavier->tab[entree] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_LEFT){
			clavier->tab[left] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_RIGHT){
			clavier->tab[right] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE){
			clavier->tab[escape] = TRUE;
		}
	}

	if(event.type == SDL_KEYUP){

		if(event.key.keysym.sym == SDLK_UP){
			clavier->tab[up] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_DOWN){
			clavier->tab[down] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_RETURN){
			clavier->tab[entree] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_LEFT){
			clavier->tab[left] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_RIGHT){
			clavier->tab[right] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE){
			clavier->tab[escape] = FALSE;
		}
	}
}



/**
*\fn int clavier_vide(touches_t clavier)

*\param clavier, la structure contenant les touches utilisées dans le cadre du jeu

*\brief renvoie TRUE si auncune touche n'est actuellement utilisée
*/
int clavier_vide(touches_t clavier){

	for(int i = 0; i < NB_TOUCHES_UTILISEES; i++)
		if(clavier.tab[i] == TRUE)
			return FALSE;

	return TRUE;
}


/**
*\fn void lire_clavier(touches_t *clavier)

*\param *clavier, la structure contenant les touches utilisées dans le cadre du jeu

*\brief Regarde si une touche est enfoncée, si oui il fait suivre à la fonction qui l'entrera dans le tableau
*/
void lire_clavier(touches_t *clavier){

	SDL_Event event;

	while(SDL_PollEvent(&event))
		event_clavier(clavier, event);
}