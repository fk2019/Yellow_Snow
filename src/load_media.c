#include "load_media.h"

bool game_load_media(Game_T *g)
{
	//load background texture/image
	g->background_image =  IMG_LoadTexture(g->renderer, "images/background.png");
	if (!g->background_image)
	{
		fprintf(stderr, "Error loading background texture: %s\n", IMG_GetError());
		return true;
	}
	// Query texture attributes
	if (SDL_QueryTexture(g->background_image, NULL, NULL, &g->background_rect.w, &g->background_rect.h))
	{
		fprintf(stderr, "Error querying background texture: %s\n", SDL_GetError());
		return true;

	}
	// load player image
	g->player_image =  IMG_LoadTexture(g->renderer, "images/player.png");
	if (!g->player_image)
	{
		fprintf(stderr, "Error loading player texture: %s\n", IMG_GetError());
		return true;
	}

	return false;
}
