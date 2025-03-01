#include "game.h"
#include "initialize.h"
#include "load_media.h"
#include "player.h"

bool game_new(Game_T **game)
{
	*game = calloc(1, sizeof(Game_T));
	if (*game == NULL)
	{
		fprintf(stderr, "Error in calloc of new game.\n");
		return true;
	}
	Game_T *g = *game;

	if (game_initialize(g))
	{
		return true;
	}
	if (game_load_media(g))
	{
		return true;
	}
	if (player_new(&g->player, g->renderer, g->player_image))
	{
		return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (flake_new(&g->flakes, g->renderer, g->yellow_image))
		{
			return true;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (flake_new(&g->flakes, g->renderer, g->white_image))
		{
			return true;
		}
	}
	return false;
}

void game_free(Game_T **game)
{
	if (*game)
	{
		Game_T *g = *game;
		flakes_free(&g->flakes);
		player_free(&g->player);

		SDL_DestroyTexture(g->yellow_image);
		g->yellow_image = NULL;
		SDL_DestroyTexture(g->white_image);
		g->white_image = NULL;
		SDL_DestroyTexture(g->player_image);
		g->player_image = NULL;
		SDL_DestroyTexture(g->background_image);
		g->background_image = NULL;
		SDL_DestroyRenderer(g->renderer);
		g->renderer = NULL;
		SDL_DestroyWindow(g->window);
		g->window = NULL;
		SDL_Quit();

		free(g);
		g = NULL;
		*game = NULL;
		printf("All Clean!\n");
	}
}

bool game_run(Game_T *g)
{
	while (1)
	{
		while (SDL_PollEvent(&g->event))
		{
			switch (g->event.type)
			{
			case SDL_QUIT:
				return false;
				break;
			case SDL_KEYDOWN:
				switch (g->event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					return false;
					break;
				case SDL_SCANCODE_SPACE:
					flakes_reset(g->flakes);
					player_reset(g->player);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		player_update(g->player);
		flakes_update(g->flakes);
		SDL_RenderClear(g->renderer);
		SDL_RenderCopy(g->renderer, g->background_image, NULL, &g->background_rect); //display texture
		player_draw(g->player);
		flakes_draw(g->flakes);
		SDL_RenderPresent(g->renderer);
		SDL_Delay(16);
	}
	return false;
}
