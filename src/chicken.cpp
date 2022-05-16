#include "chicken.h"

#include "sprites.h"
#include "tileData.h"
#include "world.h"
#include <SDL2/SDL.h>

Chicken::~Chicken()
{
}

SpriteTypes Chicken::GetSpriteType() const
{
    return CHICKEN;
}

SDL_Point Chicken::GetPosition() const
{
    return _position;
}

void CheckArea(Chicken &chicken)
{
    auto pos = chicken.GetPosition();
    SDL_Rect searchRect;
    // searchRect.x = pos.x - chicken._viewDistance;
}

TileData *Chicken::FindGrass()
{
    SDL_Rect searchRect;
    searchRect.x = _position.x - _viewDistance - 1;
    searchRect.y = _position.y - _viewDistance - 1;
    searchRect.w = _viewDistance * 2 + 1;
    searchRect.h = _viewDistance * 2 + 1;

    // TileData tiles[_viewDistance * _viewDistance];
    // int index = 0;

    for (auto x = searchRect.x; x < searchRect.x + searchRect.w; x++)
    {
        for (auto y = searchRect.y; y < searchRect.y + searchRect.h; y++)
        {
            auto tile = World::GetDataAtPos(x, y);
            if (tile->type == GRASS_LONG)
            {
                return tile;
            }

            // index++;
        }
    }
    return nullptr;
}

void Chicken::Tick(int deltaTime)
{

    // if (_grassTile)
    // {
    //     _grassTile = FindGrass();
    //     if (!_grassTile)
    //     {
    //         _grassTile = World::GetDataAtPos(_position.x + 1, _position.y);
    //     }
    // }

    _timeSinceLastMove += deltaTime;
    if (_timeSinceLastMove >= _moveDelay)
    {
        if (_position.x < _grassTile.x)
        {
            _position.x += 1;
        }
        else if (_position.x > _grassTile.x)
        {
            _position.x -= 1;
        }

        if (_position.y < _grassTile.y)
        {
            _position.y += 1;
        }
        else if (_position.y > _grassTile.y)
        {
            _position.y -= 1;
        }

        if (_position.x == _grassTile.x && _position.y == _grassTile.y)
        {
            auto *_grassTilePtr = FindGrass();
            if (_grassTilePtr == nullptr)
            {
                _grassTilePtr = World::GetDataAtPos(_position.x + 1, _position.y);
            }
            _grassTile = *_grassTilePtr;
        }

        _timeSinceLastMove = 0;
    }
}