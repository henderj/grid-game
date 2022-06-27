#include "rect.h"

#include <iostream>
#include <SDL2/SDL.h>

namespace game
{
    SDL_Rect Rect::toSDL_Rect()
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        return rect;
    }
}

std::ostream &operator<<(std::ostream &os, const game::Rect &rect)
{
    os << rect.x << ", " << rect.y << " : " << rect.w << ", " << rect.h;
    return os;
}