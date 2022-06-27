#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace game
{
    struct Rect
    {
        float x, y, w, h;

        Rect() : x(0), y(0), w(0), h(0) {}
        Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

        SDL_Rect toSDL_Rect();
    };
} // namespace game

std::ostream &operator<<(std::ostream &os, const game::Rect &rect);
