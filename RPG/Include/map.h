#ifndef CHARGE_MAP_H

	#define CHARGE_MAP_H

	void charge_map(map_t *map, SDL_Renderer *rendu);
	void affiche_map(SDL_Renderer * rendu, map_t *map);
	void init_places(map_t * map);
	void charge_layer_dans_tableau(int tab[][TAILLE_MAP], FILE *f);
	int hors_tableau(int x, int y);
	void rempli_tab_collision_map(map_t *map);
	void creer_bordure_map(map_t *map);

#endif