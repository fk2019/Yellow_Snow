#ifndef GAME_H
#define GAME_H
#include "main.h"
#include "player.h"
#include "flakes.h"
#include "score.h"
typedef struct Game
{
	SDL_Event event;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *background_image;
	SDL_Rect background_rect;
	SDL_Texture *player_image;
	SDL_Texture *yellow_image;
	SDL_Texture *white_image;
	Mix_Chunk *collect_sound;
	Mix_Chunk *hit_sound;
	bool playing;
	Player_T *player;
	Flake_T *flakes;
	Score_T *score;
} Game_T;
bool game_new(Game_T **g);
void game_free(Game_T **g);
bool game_run(Game_T *g);

#endif
