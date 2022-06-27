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
    void Vector2::add(const Vector2 &v)
    {
        x += v.x;
        y += v.y;
    }
    Vector2 Vector2::operator+(const Vector2 &v) const
    {
        Vector2 vec;
        vec.x = this->x + v.x;
        vec.y = this->y + v.y;
        return vec;
    }
    void Vector2::sub(const Vector2 &v)
    {
        x -= v.x;
        y -= v.y;
    }
    Vector2 Vector2::operator-(const Vector2 &v) const
    {
        Vector2 vec;
        vec.x = this->x - v.x;
        vec.y = this->y - v.y;
        return vec;
    }
    void Vector2::mult(const float &n)
    {
        x *= n;
        y *= n;
    }
    Vector2 Vector2::operator*(const float &n) const
    {
        Vector2 vec;
        vec.x = this->x * n;
        vec.y = this->y * n;
        return vec;
    }
    void Vector2::div(const float &n)
    {
        x /= n;
        y /= n;
    }
    Vector2 Vector2::operator/(const float &n) const
    {
        Vector2 vec;
        vec.x = this->x / n;
        vec.y = this->y / n;
        return vec;
    }
    float Vector2::mag()
    {
        return std::sqrt(x * x + y * y);
    }
    void Vector2::normalize()
    {
        float m = mag();
        if (m == 0)
            return;
        div(m);
    }
    void Vector2::limit(const float &l)
    {
        float m = mag();
        if (m > l)
        {
            normalize();
            mult(l);
        }
    }
} // namespace game

std::ostream &operator<<(std::ostream &os, const game::Vector2 &vec2)
{
    os << vec2.x << ", " << vec2.y;
    return os;
}
