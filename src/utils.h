#pragma once

#include <SDL2/SDL.h>

SDL_Rect GetSpriteRectFromSheet(const SDL_Point *pos);
SDL_Surface *CreateBlankSurface(int w, int h);