#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SDL_FLAGS SDL_INIT_EVERYTHING
#define MIXER_FLAGS MIX_INIT_OGG
#define IMAGE_FLAGS IMG_INIT_PNG
#define WINDOW_TITLE "Don't Eat the Yellow Snow"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_ICON "images/yellow.png"
#define FONT_SIZE 23
#define TARGET_FPS 60
#define GAME_RESET_EVENT SDL_USEREVENT
#define GAME_RESET_TIME 5000

#endif
