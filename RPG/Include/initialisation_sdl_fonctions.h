#ifndef INIT_SDL_H

	#define INIT_SDL_H

	int initialisation_sdl(SDL_Window **window, SDL_Renderer **rendu);
	void quit_sdl(SDL_Renderer **rendu, SDL_Window **window);
	int init_or_quit_ttf(int action);

	extern void get_text_and_rect_color(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, SDL_Color textColor);
	extern void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);

	int charge_image(char *path_img, image_t *struct_image, SDL_Renderer *rendu);

	void libere_texture(SDL_Texture **texture);

#endif