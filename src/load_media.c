#include "load_media.h"

bool game_load_media(Game_T *g)
{
	//load texture/image
	g->background_image =  IMG_LoadTexture(g->renderer, "images/background.png");
	if (!g->background_image)
	{
		fprintf(stderr, "Error loading texture: %s\n", IMG_GetError());
		return true;
	}
	// Query texture attributes
	if (SDL_QueryTexture(g->background_image, NULL, NULL, &g->background_rect.w, &g->background_rect.h))
	{
		fprintf(stderr, "Error querying texture: %s\n", SDL_GetError());
		return true;

	}
	return false;
}
