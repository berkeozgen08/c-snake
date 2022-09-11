#ifndef _GFX_H
#define _GFX_H

#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"
#include "snake.h"

SDL_Window *gfx_create_window(int, int);
void gfx_start(Game *, SDL_Window *, int);

#endif
