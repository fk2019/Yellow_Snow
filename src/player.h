#ifndef PLAYER_H
#define PLAYER_H
#include "main.h"

typedef struct Player
{
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Rect rect;
	const Uint8 *keystate;
	SDL_RendererFlip flip;
} Player_T;
bool player_new(Player_T **player, SDL_Renderer *renderer, SDL_Texture *image);
void player_free(Player_T **player);
void player_update(Player_T *p);
void player_draw(Player_T *p);

#endif
