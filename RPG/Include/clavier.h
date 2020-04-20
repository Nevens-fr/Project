#ifndef CLAVIER_H

	#define CLAVIER_H

	void event_clavier(touches_t *clavier, SDL_Event event);
	void init_tab_clavier(int tab[]);
	int clavier_vide(touches_t clavier);
	void lire_clavier(touches_t *clavier);
#endif