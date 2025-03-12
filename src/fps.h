#ifndef FPS_H
#define FPS_H
#include "main.h"

typedef struct Fps
{
	Uint32 last_time;
	double target_delay;
	double cap_delay;
	double carry_delay;
	double delta_time;
	Uint32 fps_last_time;
	Uint32 fps_counter;
	bool fps_display;
} Fps_T;

bool fps_new(Fps_T **fps);
void fps_free(Fps_T **fps);
void fps_toggle_display(Fps_T *f);
double fps_update(Fps_T *f);
#endif
