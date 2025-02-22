#ifndef GAME_H
#define GAME_H
#include "main.h"

typedef struct Game
{
	SDL_Event event;
	SDL_Window *window;
	SDL_Renderer *renderer;
} Game_T;
bool game_new(Game_T **g);
void game_free(Game_T **g);
bool game_run(Game_T *g);

#endif
