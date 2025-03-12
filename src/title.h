#ifndef TITLE_H
#define TITLE_H

#include "main.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
typedef struct Title
{
	SDL_Renderer *renderer;
	SDL_Texture *image;
	SDL_Surface *text_surf;
	SDL_Surface *target_surf;
	TTF_Font *font;
	SDL_Rect rect;
	double pos_y;
	double target_y;
	double speed;
	bool show_intro;
	bool show_title;
} Title_T;

bool title_new(Title_T **title, SDL_Renderer *renderer);
void title_free(Title_T **title);
void title_reset(Title_T *t);
void title_update(Title_T *t, double dt);
void title_draw(Title_T *t);
void title_disable(Title_T *t);
#endif
