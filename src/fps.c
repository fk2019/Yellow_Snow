#include "fps.h"
Uint32 fps_time_since(Uint32 last_time, Uint32 *new_last_time);
Uint32 fps_time_since(Uint32 last_time, Uint32 *new_last_time)
{
	Uint32 current_time = SDL_GetTicks();
	Uint32 elapsed_time = 0;

	elapsed_time = current_time - last_time;
	if (new_last_time)
	{
		*new_last_time = current_time;
	}
	return elapsed_time;

}

bool fps_new(Fps_T **fps)
{
	*fps = calloc(1, sizeof(Fps_T));
	if (*fps == NULL)
	{
		fprintf(stderr, "Error in calloc of new fps: %s\n", SDL_GetError());
		return true;
	}
	Fps_T *f = *fps;
	f->target_delay = 1000.0 / TARGET_FPS;
	f->cap_delay = 16;
	f->last_time = SDL_GetTicks();
	f->carry_delay = 0;

	return false;
}
void fps_free(Fps_T **fps)
{
	if (*fps)
	{
		free(*fps);
		*fps = NULL;
	}
}
void fps_toggle_display(Fps_T *f)
{
	if (f->fps_display)
	{
		f->fps_display = false;
	} else {
		f->fps_last_time = SDL_GetTicks(); //ticks passed since game started
		f->fps_counter = 0;
		f->fps_display = true;
	}
}
double fps_update(Fps_T *f)
{
	Uint32 elapsed_time = fps_time_since(f->last_time, NULL); //elapsed time since last frame
	double delay = f->target_delay + f->carry_delay;
	if (delay > elapsed_time)
	{
		Uint32 current_delay = (Uint32)delay - elapsed_time;
		SDL_Delay(current_delay);
	}
	elapsed_time = fps_time_since(f->last_time, &f->last_time);
	f->carry_delay = delay - elapsed_time;
	if (f->carry_delay > f->cap_delay)
	{
		f->carry_delay = f->cap_delay;
	} else if (f->carry_delay < -f->cap_delay)
	{
		f->carry_delay = -f->cap_delay;
	}
	if (f->fps_display) //count frames
	{
		f->fps_counter++;
		if (fps_time_since(f->fps_last_time, NULL) > 1000)
		{
			printf("%i\n", f->fps_counter);
			f->fps_counter = 0;
			f->fps_last_time += 1000;
		}
	}
	return elapsed_time / 1000.0;
}
