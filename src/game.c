#include "game.h"
#include "initialize.h"

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
	return false;
}

void game_free(Game_T **game)
{
	Game_T *g = *game;
	if (g)
	{
		SDL_DestroyRenderer(g->renderer);
		g->renderer = NULL;
		SDL_DestroyWindow(g->window);
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
				default:
					break;
				}
			default:
				break;
			}
		}
		SDL_RenderClear(g->renderer);
		SDL_RenderPresent(g->renderer);
		SDL_Delay(16);
	}
	return false;
}
