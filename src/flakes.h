#ifndef FLAKES_H
#define FLAKES_H
#include "main.h"

typedef struct Flake
{
	struct Flake *next;
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Rect rect;
} Flake_T;
bool flake_new(Flake_T **flake, SDL_Renderer *renderer, SDL_Texture *image);
void flakes_free(Flake_T **flakes);
void flakes_update(Flake_T *f);
void flakes_draw(Flake_T *f);
#endif
