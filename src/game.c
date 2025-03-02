#include "game.h"
#include "initialize.h"
#include "load_media.h"
#include "player.h"
#include "score.h"

bool check_collision(Game_T *g);
bool handle_collision(Game_T *g, Flake_T *f);
bool game_reset(Game_T *g);

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
		if (flake_new(&g->flakes, g->renderer, g->yellow_image, false))
		{
			return true;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (flake_new(&g->flakes, g->renderer, g->white_image, true))
		{
			return true;
		}
	}

	if (score_new(&g->score, g->renderer)) return true;
	g->playing = true;
	return false;
}

void game_free(Game_T **game)
{
	if (*game)
	{
		Game_T *g = *game;
		score_free(&g->score);
		flakes_free(&g->flakes);
		player_free(&g->player);


		Mix_FreeChunk(g->collect_sound);
		g->collect_sound = NULL;
		Mix_FreeChunk(g->hit_sound);
		g->hit_sound = NULL;
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

		Mix_CloseAudio();

		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();

		free(g);
		g = NULL;
		*game = NULL;
		printf("All Clean!\n");
	}
}

bool game_reset(Game_T *g)
{
	//call player and flake reset functions
	flakes_reset(g->flakes);
	player_reset(g->player);
	g->playing = true;
	if (score_reset(g->score)) return true;
	return false;
}

bool handle_collision(Game_T *g, Flake_T *f)
{
	(void)g;
	if (f->is_white)
	{
		Mix_PlayChannel(-1, g->collect_sound, 0);
		flake_reset(f, false);
		score_increment(g->score);
	} else {
		Mix_PlayChannel(-1, g->hit_sound, 0);
		g->playing = false;
	}
	return false;
}
bool check_collision(Game_T *g)
{
	Flake_T *f = g->flakes;
	int p_top  = player_top(g->player);
	int p_left = player_left(g->player);
	int p_right = player_right(g->player);

	while (f)
	{
		if (flake_bottom(f) > p_top)
		{
			if (flake_right(f) > p_left)
			{
				if (flake_left(f) < p_right)
				{
					if (handle_collision(g, f))
					{
						return true;
					}
				}
			}
		}
		f = f->next;
	}
	return false;
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
					if (!g->playing)
					{
						if (game_reset(g))
						{
							return true;
						}
					}
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		if (g->playing)
		{
			player_update(g->player);
			flakes_update(g->flakes);
			score_update(g->score);
			if (check_collision(g))
			{
				return true;
			}
		}
		SDL_RenderClear(g->renderer);
		SDL_RenderCopy(g->renderer, g->background_image, NULL, &g->background_rect); //display texture
		player_draw(g->player);
		flakes_draw(g->flakes);
		score_draw(g->score);
		SDL_RenderPresent(g->renderer);
		SDL_Delay(16);
	}
	return false;
}
