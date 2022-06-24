#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace game
{
    struct Vector2
    {
        float x, y;

        SDL_Point toSDL_Point();
    };

} // namespace game
std::ostream &operator<<(std::ostream &os, const game::Vector2 &vec2);
