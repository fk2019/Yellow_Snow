#ifndef SCORE_H
#define SCORE_H
#include "main.h"

typedef struct Score
{
	SDL_Renderer *renderer;
	SDL_Texture *image;
	TTF_Font *font;
	SDL_Color color;
	SDL_Rect rect;
	Uint32 score;
} Score_T;

bool score_new(Score_T **score, SDL_Renderer *renderer);
void score_free(Score_T **score);
bool score_reset(Score_T *s);
bool score_update(Score_T *s);
void score_draw(Score_T *s);
bool score_increment(Score_T *s);
#endif
