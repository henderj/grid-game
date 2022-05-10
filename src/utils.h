#pragma once

SDL_Rect GetSpriteRectFromSheet(const SDL_Point *pos);
SDL_Rect GetSpriteRectFromSheet(const SpriteTypes type);
SDL_Surface *CreateBlankSurface(int w, int h);