/**
*\file map.c
*\author Tudoret Aurélien

*\brief charge la map et ses textures

*/

#include "../Include/constantes.h"
#include "../Include/initialisation_sdl_fonctions.h"
#include "../Include/map.h"



/**
*\fn void charge_map(map_t *map, SDL_Renderer *rendu)

*\param *map, la structure contenant la map;
*\param *rendu, le renderer sur lequel on dessine

*\brief Permet de charger les données de la map ainsi que ses textures depuis les fichiers
*/
void charge_map(map_t *map, SDL_Renderer *rendu){

	FILE *fl1;

//***** PREMIERE COUCHE ********

	fl1 = fopen(LAYER_1, "r");

	charge_layer_dans_tableau(map->layer1, fl1);

	fclose(fl1);

//***** DEUXIEME COUCHE ********

	fl1 = fopen(LAYER_2, "r");

	charge_layer_dans_tableau(map->layer2, fl1);

	fclose(fl1);

//***** TEXTURES PNG ***********

	charge_image(TILESET_PATH, &map->texture, rendu);

	map->texture.a_dessiner.w = TAILLE_TILE_TERRAIN;
	map->texture.a_dessiner.h = TAILLE_TILE_TERRAIN;
	map->texture.rectangle.w = TAILLE_TILE_TERRAIN;
	map->texture.rectangle.h = TAILLE_TILE_TERRAIN;

	map->x = 0;
	map->y = 0;

	init_places(map);
}



/**
*\fn void charge_layer_dans_tableau(int tab[], FILE *f)

*\param tab[], tableau stockant les indices correspondant aux textures du tileset
*\param *f, fichier contenant les indices de la map.

*\brief Permet de charger les indices de la map qui correspondnet aux textures du tileset
*/
void charge_layer_dans_tableau(int tab[][TAILLE_MAP], FILE *f){

	int x , y;

	if(f == NULL){
		printf("Erreur chargement layer\n");
	}
	else{

		while(!feof(f)){

			for(y = 0; y < 100; y++){
				for(x = 0; x < 100; x++){
					fscanf(f, "%d,", &tab[x][y]);
				}
			}
		}
	}
}



/**
*\fn void init_places(map_t * map)

*\param *map, la structure contenant la map

*\brief Initialise le tableau des positions des textures dans le tileset
*/
void init_places(map_t * map){

	int i, x = 0, y = 0;

	for(i = chemin1; i <= maison_1_12; i++){

		if(i <= grave2 && i != chemin1){
			x += TAILLE_TILE_TERRAIN;
		}
		else if(i == 1+ grave2 || i == maison_1_4 + 1 || i == maison_1_8 + 1){
			y += TAILLE_TILE_TERRAIN;
			x = 0;
		}
		else if((i <= maison_1_4 || i <= maison_1_8 || i <= maison_1_12) && i != chemin1)
			x += TAILLE_TILE_TERRAIN;

		map->place[i].x = x;
		map->place[i].y = y;
	}
}





/**
*\fn void affiche_map(SDL_Renderer * rendu, map_t *map)

*\param *map, la structure contenant la map à afficher
*\param *rendu, le renderer sur lequel on dessine

*\brief Permet d'afficher une map ainsi que ses layers
*/
void affiche_map(SDL_Renderer * rendu, map_t *map){

	int x, y;

	map->texture.rectangle.y = 0;
	map->texture.rectangle.x = 0;//on définit où on commence à dessiner sur la fenetre
	map->texture.a_dessiner.y = 0;

	for(y = map->y; map->texture.rectangle.y < WIN_HEIGHT; map->texture.rectangle.y += TAILLE_TILE_TERRAIN, y++){

		for(x = map->x, map->texture.rectangle.x = 0; map->texture.rectangle.x < WIN_WIDTH; map->texture.rectangle.x += TAILLE_TILE_TERRAIN, x++){

			if(map->layer1[x][y] <= herbe1 && map->layer1[x][y] >= chemin1 && !hors_tableau(x, y)){ ////// PREMIERE COUCHE

				map->texture.a_dessiner.x = map->place[map->layer1[x][y]].x;	//choisit quelle tile afficher
				map->texture.a_dessiner.y = map->place[map->layer1[x][y]].y;

				SDL_RenderCopy(rendu, map->texture.img, &map->texture.a_dessiner, &map->texture.rectangle);

				if(	map->layer2[x][y] > 0 && map->layer2[x][y] <= maison_1_12){ ///// DEUXIEME COUCHE

					map->texture.a_dessiner.x = map->place[map->layer2[x][y]].x;	//choisit quelle tile afficher
					map->texture.a_dessiner.y = map->place[map->layer2[x][y]].y;

					SDL_RenderCopy(rendu, map->texture.img, &map->texture.a_dessiner, &map->texture.rectangle);
				}
			}
		}
	}
}



/**
*\fn int hors_tableau(int x, int y)

*\param x, la position en ordonée dans le tableau de la map 
*\param y, la position en abcisse dans le tableau de la map

*\return 1 si on est hors tableau, 0 sinon

*\brief Permet de ne pas afficher la map si une partie de l'écran est hors tableau
*/
int hors_tableau(int x, int y){

	return(x < 0 || x >= TAILLE_MAP || y < 0 || y >= TAILLE_MAP);
}




/**
*\fn void rempli_tab_collision_map(map_t *map)

*\param *map, la structure contenant la map à afficher

*\brief Permet de remplir le tableau de collision des éléments actuellement présent à l'écran
*/
void rempli_tab_collision_map(map_t *map){

	int x, y, i = 4;

	creer_bordure_map(map);

	map->texture.rectangle.y = 0;
	map->texture.rectangle.x = 0;//on définit où on commence à dessiner sur la fenetre
	map->texture.a_dessiner.w = TAILLE_TILE_TERRAIN;
	map->texture.a_dessiner.h = TAILLE_TILE_TERRAIN;

	for(y = map->y; map->texture.rectangle.y < WIN_HEIGHT; map->texture.rectangle.y += TAILLE_TILE_TERRAIN, y++){

		for(x = map->x, map->texture.rectangle.x = 0; map->texture.rectangle.x < WIN_WIDTH; map->texture.rectangle.x += TAILLE_TILE_TERRAIN, x++){

			if(map->layer2[x][y] <= maison_1_12 && map->layer2[x][y] > herbe1 && !hors_tableau(x, y)){

				map->collisions[i++] = map->texture.rectangle;
			}
		}
	}

	map->nb_coll = i + 4; //4 symbolise les 4 rectangles placés au début du tableau et étant là pour bloquer le joueur
	//s'il tente de sortir des limites de la map
}



/**
*\fn void rempli_tab_collision_map(map_t *map)

*\param *map, la structure contenant la map à modifier

*\brief Permet de remplir le tableau de collision en y ajoutant 4 rectangles, aux 4 extremités, afin que le joueur ne sorte pas de la map
*/
void creer_bordure_map(map_t *map){

	int i = 0;

	map->collisions[i].x = map->x;
	map->collisions[i].y = map->y;
	map->collisions[i].h = 1;
	map->collisions[i++].w = WIN_WIDTH +1;// Au-dessus de la map

	map->collisions[i].x = map->x;
	map->collisions[i].y = map->y;
	map->collisions[i].h = WIN_HEIGHT +1;
	map->collisions[i++].w = 1; // A gauche de la map

	map->collisions[i].x = map->x;
	map->collisions[i].y = map->y + WIN_HEIGHT;
	map->collisions[i].h = 1;
	map->collisions[i++].w = WIN_WIDTH + 1; // En dessous la map

	map->collisions[i].x = WIN_WIDTH + map->x;
	map->collisions[i].y = map->y;
	map->collisions[i].h = WIN_HEIGHT + 1;
	map->collisions[i++].w = 1; // A droite la map
}