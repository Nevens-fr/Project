#ifndef JOUEUR_H

	#define JOUEUR_H

	void init_joueur(perso_t *pers, SDL_Renderer *rendu);
	void charge_sprite_joueur(perso_t *pers, SDL_Renderer *rendu);
	void affiche_joueur(perso_t pers, SDL_Renderer *rendu);
	void deplacement_joueur(perso_t *pers, touches_t clavier, map_t *map);
	int collision_trouvee(perso_t pers, SDL_Rect tab[], int taille, int x, int y);
	void update_coordonnees_sprite_joueur(perso_t *pers);

#endif