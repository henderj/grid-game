#pragma once

#include <SDL2/SDL.h>
#include "sprites.h"

class Chicken
{
private:
    SDL_Point _position;
    int _timeSinceLastMove;
    const int _moveDelay = 500;

public:
    Chicken(SDL_Point position);
    ~Chicken();

    SpriteTypes GetSpriteType();
    SDL_Point GetPosition();
    void Tick(int deltaTime);
};
