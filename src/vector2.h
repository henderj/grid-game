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

        void add(const Vector2 &v);
        Vector2 operator+(const Vector2 &v) const;
        void sub(const Vector2 &v);
        Vector2 operator-(const Vector2 &v) const;
        void mult(const float &n);
        Vector2 operator*(const float &n) const;
        void div(const float &n);
        Vector2 operator/(const float &n) const;
        float mag();
        void normalize();
        void limit(const float &l);
    };

} // namespace game
std::ostream &operator<<(std::ostream &os, const game::Vector2 &vec2);
