#ifndef JEU_H

	#define JEU_H

	void jeu_en_cours(perso_t *pers, SDL_Renderer *rendu, int *continuer, int *etat);
	int clock_depasse(unsigned int *clock);

#endif