#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace game
{
    struct Vector2
    {
        float x, y;

        Vector2() : x(0), y(0) {}
        Vector2(float x, float y) : x(x), y(y) {}

        SDL_Point toSDL_Point();
    };

} // namespace game
std::ostream &operator<<(std::ostream &os, const game::Vector2 &vec2);
