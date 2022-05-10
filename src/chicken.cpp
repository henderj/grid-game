#include "chicken.h"

#include "sprites.h"
#include <SDL2/SDL.h>

Chicken::Chicken(SDL_Point position)
{
    _position = position;
}

Chicken::~Chicken()
{
}

SpriteTypes Chicken::GetSpriteType()
{
    return CHICKEN;
}

SDL_Point Chicken::GetPosition()
{
    return _position;
}

void Chicken::Tick(int deltaTime)
{
    _timeSinceLastMove += deltaTime;
    if (_timeSinceLastMove >= _moveDelay)
    {
        _position.x += 1;
        _timeSinceLastMove = 0;
    }
}