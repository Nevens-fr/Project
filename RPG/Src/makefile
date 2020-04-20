## variables
^ = main.o initialisation_sdl_fonctions.o clavier.o map.o jeu.o affichages.o joueur.o
@ = ../Bin/RPG
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o
SDL = `sdl2-config --cflags --libs`


## preprocessing, compiling, assembling, linking
$@ : $^
	gcc -g -Wall $^ $(SDL) $(LIBS) $@

%o : %c
	gcc $*c -c



## Cleaning temps
clean :
	rm *.o && clear

##launch a test

test :
	./../Bin/RPG
