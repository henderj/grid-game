#include "vector2.h"

#include <iostream>
#include <SDL2/SDL.h>

namespace game
{
    SDL_Point Vector2::toSDL_Point()
    {
        SDL_Point p;
        p.x = x;
        p.y = y;
        return p;
    }
} // namespace game

std::ostream &operator<<(std::ostream &os, const game::Vector2 &vec2)
{
    os << vec2.x << ", " << vec2.y;
    return os;
}
