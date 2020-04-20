/**
*\file constantes.h
*\author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
*\date 30/01/2020
*\version 0.1

*\brief Constantes et structures du projet Roguelike
*/

#ifndef CONSTANTES_H

#define CONSTANTES_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <string.h>
#include "SDL2/SDL_mixer.h"


#define WIN_HEIGHT 900 //--> 28 tiles en hauteur
#define WIN_WIDTH 1200 //--> 37 tiles en largeur

#define FONT_PATH "../Font/BebasNeue.ttf"

#define JOUEUR_PATH "../Images/perso.png"

#define TILESET_PATH "../Images/tileset.png"
#define TILESET2_PATH "../Images/tileset2.png"

#define LAYER_1 "../Map/Layer1.txt"
#define LAYER_2 "../Map/Layer2.txt"

#define TRUE 1
#define FALSE 0

#define NB_TOUCHES_UTILISEES 6

#define TAILLE_TILE_TERRAIN 32

#define TAILLE_MAP 100 // fois 100

#define NB_TEXTURES 17

#define DELAI_ACTUALISATION 5


#define PV_DEPART_JOUEUR 50
#define EMPLACEMENT_DEPART_JOUEUR_X 50
#define EMPLACEMENT_DEPART_JOUEUR_Y 50
#define VITESSE_JOUEUR 1

/**
*\enum t_etat

*\brief les états que peut prendre le jeu afin de naviguer entre les menus
*/

typedef enum{mainMenu = 0, jeu}t_etat;


/**
*\enum t_touches_clavier

*\brief Les différents types de touches utilisées
*/
typedef enum{up, down, right, left, entree, escape}t_touches_clavier;

/**
*\enum t_direction

*\brief Les différents types de touches utilisées
*/
typedef enum{haut, droite, bas, gauche}t_direction;


/**
*\enum t_place_textures

*\brief Définit l'indice des textures sur les feuilles de sprites
*/
typedef enum{

  chemin1 = 1, herbe1, grave1, grave2, 
  maison_1_1, maison_1_2, maison_1_3, maison_1_4, 
  maison_1_5, maison_1_6, maison_1_7, maison_1_8, 
  maison_1_9,  maison_1_10, maison_1_11, maison_1_12
}t_place_textures;



/**
*\struct animation_t

*\brief permet de gèrer les animations du personnage
*/
typedef struct{

  int actuel, gap_w, gap_h;

  unsigned int last_use;

}animation_t;


/**
*\struct touchs_t

*\brief permet de gèrer les touches utilisées
*/
typedef struct{

  int tab[NB_TOUCHES_UTILISEES];
}touches_t;

/**
*\struct t_image

*\brief contient les éléments necéssaires au stockage d'une image et de son affichage partiel ou total
*/
typedef struct{

	SDL_Texture *img;
	SDL_Rect rectangle;
  SDL_Rect a_dessiner;
}image_t;




/**
*\struct perso_t
*\Permet de définir un personnage
*/
typedef struct perso_s {
  int pv;/**Point de vie d'un personnage*/
  int pv_old;
  int x;/**Placement sur l'axe des abscisses d'un personnage*/
  int y;/**Placement sur l'axe des ordonnés d'un personnage*/
  int pv_max;

  image_t sprites;

} perso_t;


/**
*\struct place_t
*\Permet de récupèrer la postion des textures sur la feuille de sprite
*/
typedef struct place_s{

  int x, y;
}place_t;


/**
*\struct map_t
*\Permet de définir une map
*/
typedef struct map_s{
  
  int layer1[TAILLE_MAP][TAILLE_MAP], layer2[TAILLE_MAP][TAILLE_MAP];

  SDL_Rect collisions[200];

  image_t texture;

  int nb_coll, x , y;

  place_t place[NB_TEXTURES];
}map_t;



#endif