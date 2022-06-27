#pragma once

#include "rect.h"
#include "vector2.h"

namespace game
{
    Rect GetSpriteRectFromSheet(const Vector2 &pos);
    Rect GetSpriteRectFromSheet(const SpriteTypes type);
    SDL_Surface *CreateBlankSurface(int w, int h);
} // namespace game