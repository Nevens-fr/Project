/**
* \file main.c
* \date 30/01/2020
* \author {Tudoret Aurélien}
* \version 0.1
* \brief Le projet de deuxième année de licence, un roguelike/rpg
*/

#include "../Include/constantes.h"
#include "../Include/initialisation_sdl_fonctions.h"
#include "../Include/jeu.h"
#include "../Include/joueur.h"


int main(int argc, char* args[]){

//************************* DECLARATION VARIABLES************************************************************
	SDL_Window *window;
	SDL_Renderer *rendu;

	srand(time(NULL));

	int continuer = TRUE, etat = jeu;

	int result = 0;
	int flags = MIX_INIT_MP3;

	perso_t pers;

//************************* INITIALISATION SDL + TTF ********************************************************

	if(initialisation_sdl(&window, &rendu)){
		printf("Erreur création fenetre ou rendu\n");
	}
	else{

		if(init_or_quit_ttf(1)){//initialise TTF (permet s d'écrire sur l'écran)
			printf("Erreur init TTF\n");
		}
		else{

			if((IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG){
				printf("Erreur init sdl_image\n");
			}
			else{

				init_joueur(&pers, rendu);

//************************* BOUCLE DE JEU ********************************************************************
				while(continuer){

					if(etat == mainMenu){

					}
					else if (etat == jeu){

						jeu_en_cours(&pers, rendu, &continuer, &etat);
					}
				}
			}
		}
	}
//************************* FERMETURES ***********************************************************************

	IMG_Quit();

	init_or_quit_ttf(0);//quitte TTF

	quit_sdl(&rendu, &window);
	SDL_Quit();

	printf("Tout est fermé\n");//affiche dans la console

	return 0;
}