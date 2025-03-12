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
	//load yellow flake
	g->yellow_image =  IMG_LoadTexture(g->renderer, "images/yellow.png");
	if (!g->yellow_image)
	{
		fprintf(stderr, "Error loading yellow flake texture: %s\n", IMG_GetError());
		return true;
	}
	// load white flake
	g->white_image =  IMG_LoadTexture(g->renderer, "images/white.png");
	if (!g->white_image)
	{
		fprintf(stderr, "Error loading white flake texture: %s\n", IMG_GetError());
		return true;
	}
	//load audio
	g->hit_sound = Mix_LoadWAV("sounds/hit.ogg");
	if (!g->hit_sound)
	{
		fprintf(stderr, "Error loading hit sound Chunk: %s\n", Mix_GetError());
		return true;
	}
	g->collect_sound = Mix_LoadWAV("sounds/collect.ogg");
	if (!g->collect_sound)
	{
		fprintf(stderr, "Error loading collect sound Chunk: %s\n", Mix_GetError());
		return true;
	}
	//load music
	g->music = Mix_LoadMUS("music/winter_loop.ogg");
	if (!g->music)
	{
		fprintf(stderr, "Error loading music: %s\n", Mix_GetError());
		return true;
	}

	return false;
}
