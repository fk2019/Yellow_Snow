#include "flakes.h"

bool flake_new(Flake_T **flake, SDL_Renderer *renderer, SDL_Texture *image)
{
	Flake_T *new_flake = calloc(1, sizeof(Flake_T));
	if (!new_flake)
	{
		fprintf(stderr, "Error in calloc of new flake.\n");
		return true;
	}
	new_flake->renderer = renderer;
	new_flake->image = image;
	if (SDL_QueryTexture(new_flake->image, NULL, NULL, &new_flake->rect.w, &new_flake->rect.h))
	{
		fprintf(stderr, "Error querying flake texture: %s\n", SDL_GetError());
		return true;
	}
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
	}
	*flakes = NULL;
}

void flakes_update(Flake_T *f)
{
	while (f)
	{
		f->rect.y += 5;
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
