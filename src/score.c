#include "score.h"

bool score_new(Score_T **score, SDL_Renderer *renderer)
{
	*score = calloc(1, sizeof(Score_T));
	if (*score == NULL)
	{
		fprintf(stderr, "Error in calloc of new score.\n");
		return true;
	}
	Score_T *s = *score;
	s->renderer = renderer;
	s->color = (SDL_Color){255, 255, 255, 255};
	s->font = TTF_OpenFont("fonts/freesansbold.ttf", FONT_SIZE);
	if (!s->font)
	{
		fprintf(stderr, "Error opening font: %s\n", TTF_GetError());
		return true;
	}
	s->rect.x = 10;
	s->rect.y = 10;

	if (score_reset(s)) return true;
	return false;
}
void score_free(Score_T **score)
{
	if (*score)
	{
		Score_T *s = *score;
		TTF_CloseFont(s->font);
		s->font = NULL;
		SDL_DestroyTexture(s->image);
		s->image = NULL;
		s->renderer = NULL;
		free(s);
		s = NULL;
		*score = NULL;
	}
}
bool score_reset(Score_T *s)
{
	s->score = 0;
	if (score_update(s)) return true;
	return false;
}
bool score_update(Score_T *s)
{
	if (s->image)
	{
		SDL_DestroyTexture(s->image);
		s->image = NULL;
	}
	int length = snprintf(NULL, 0, "Score: %d\n", s->score);
	char score_str[length];
	snprintf(score_str, (size_t)length, "Score: %d\n", s->score);

	SDL_Surface *surface = TTF_RenderText_Blended(s->font, score_str, s->color);
	if (!surface)
	{
		fprintf(stderr, "Error creatig surface: %s\n", TTF_GetError());
		return true;
	}
	s->rect.w = surface->w;
	s->rect.h = surface->h;

	s->image = SDL_CreateTextureFromSurface(s->renderer, surface);
	SDL_FreeSurface(surface); // free surface
	if (!s->image)
	{
		fprintf(stderr, "Error creatig Texture from surface: %s\n", SDL_GetError());
		return true;
	}

	return false;
}
void score_draw(Score_T *s)
{
	SDL_RenderCopy(s->renderer, s->image, NULL, &s->rect);
}
bool score_increment(Score_T *s)
{
	s->score++;
	if (score_update(s)) return true;
	return false;
}
