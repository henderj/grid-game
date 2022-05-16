#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "sprites.h"
#include "tileData.h"

class Chicken
{
private:
    SDL_Point _position;
    int _timeSinceLastMove;
    TileData _grassTile;
    // std::vector<SpriteTypes> _area;

    const int _moveDelay = 500;
    const int _viewDistance = 5;

    TileData *FindGrass();

public:
    Chicken(SDL_Point position) : _position(position), _grassTile(TileData()){};
    ~Chicken();

    SpriteTypes GetSpriteType() const;
    SDL_Point GetPosition() const;
    void Tick(int deltaTime);
};
