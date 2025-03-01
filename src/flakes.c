#include "flakes.h"

bool flake_new(Flake_T **flake, SDL_Renderer *renderer, SDL_Texture *image, bool is_white)
{
	Flake_T *new_flake = calloc(1, sizeof(Flake_T));
	if (!new_flake)
	{
		fprintf(stderr, "Error in calloc of new flake.\n");
		return true;
	}
	new_flake->renderer = renderer;
	new_flake->image = image;
	new_flake->speed = 30;
	new_flake->ground = 514;
	new_flake->is_white = is_white;
	if (SDL_QueryTexture(new_flake->image, NULL, NULL, &new_flake->rect.w, &new_flake->rect.h))
	{
		fprintf(stderr, "Error querying flake texture: %s\n", SDL_GetError());
		return true;
	}

	flake_reset(new_flake, true); // reset new flakes
	new_flake->next = *flake;
	*flake = new_flake;
	return false;
}

void flakes_free(Flake_T **flakes)
{
	Flake_T *f = *flakes;
	while (f)
	{
		Flake_T *next = f->next;
		f->image = NULL;
		f->renderer = NULL;
		f->next = NULL;
		free(f);
		f = next;
		printf("Clean flake\n");
	}
	*flakes = NULL;
}

void flake_reset(Flake_T *f, bool full)
{
	//flakes reset above screen at random positions
	//full reset or partial reset
	int height = full ? WINDOW_HEIGHT * 2 : WINDOW_HEIGHT;
	f->rect.y = -((rand() % height) + f->rect.h);
	f->rect.x = rand() % (WINDOW_WIDTH - f->rect.w);
}
void flakes_reset(Flake_T *f)
{
	while (f)
	{
		flake_reset(f, true);
		f = f->next;
	}
}
int flake_left(Flake_T *f)
{
	return f->rect.x;
}
int flake_right(Flake_T *f)
{
	return f->rect.x + f->rect.w;
}
int flake_bottom(Flake_T *f)
{
	return f->rect.y + f->rect.h;
}
void flakes_update(Flake_T *f)
{
	while (f)
	{
		f->rect.y += f->speed;
		if (f->rect.y > f->ground)
		{
			flake_reset(f, false);
		}
		f = f->next;
	}
}

void flakes_draw(Flake_T *f)
{
	while (f)
	{
		SDL_RenderCopy(f->renderer, f->image, NULL, &f->rect); //draw head flake
		f = f->next;
	}
}
