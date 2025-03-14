#include "player.h"

bool player_new(Player_T **player, SDL_Renderer *renderer, SDL_Texture *image)
{
	*player = calloc(1, sizeof(Player_T));
	if (*player == NULL)
	{
		fprintf(stderr, "Error in calloc of new player: %s\n", SDL_GetError());
		return true;
	}
	Player_T *p = *player;
	p->renderer = renderer;
	p->image = image;
	p->keystate = SDL_GetKeyboardState(NULL); // current state of keyboard
	p->speed = 300;
	p->top_offset = 10;
	p->left_offset = 47;
	p->right_offset = 43;
	if (SDL_QueryTexture(p->image, NULL, NULL, &p->rect.w, &p->rect.h))
	{
		fprintf(stderr, "Error in querying player texture: %s\n", SDL_GetError());
		return true;
	}
	p->flip = SDL_FLIP_NONE;
	player_reset(p);
	return false;
}
void player_free(Player_T **player)
{
	if (*player)
	{
		(*player)->image = NULL;
		(*player)->renderer = NULL;
		(*player)->keystate = NULL;
		free(*player);
		*player = NULL;
	}
}
void player_reset(Player_T *p)
{
	p->rect.x = (WINDOW_WIDTH - p->rect.w) / 2;
	p->rect.y = 377;
	p->pos_x = (double)p->rect.x;

}
int player_top(Player_T *p)
{
	return p->rect.y + p->top_offset;
}

int player_left(Player_T *p)
{
	return p->rect.x + p->left_offset;
}

int player_right(Player_T *p)
{
	return p->rect.x + p->rect.w - p->right_offset;
}

void player_update(Player_T *p, double dt)
{
	if (p->keystate[SDL_SCANCODE_LEFT] || p->keystate[SDL_SCANCODE_A])
	{
		p->pos_x -= p->speed * dt;
		if (p->pos_x + p->left_offset < 0) p->pos_x = -p->left_offset;
		p->flip = SDL_FLIP_HORIZONTAL;
	}
	if (p->keystate[SDL_SCANCODE_RIGHT] || p->keystate[SDL_SCANCODE_D])
	{
		p->pos_x += p->speed * dt;
		if (p->pos_x + p->rect.w - p->right_offset > WINDOW_WIDTH) p->pos_x = WINDOW_WIDTH - p->rect.w + p->right_offset;
		p->flip = SDL_FLIP_NONE;
	}
	p->rect.x = (int)p->pos_x;
}
void player_draw(Player_T *p)
{
	//rotate and flip texture
	SDL_RenderCopyEx(p->renderer, p->image, NULL, &p->rect, 0, NULL, p->flip);
}
