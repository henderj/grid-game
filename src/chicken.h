#pragma once

#include <SDL2/SDL.h>
#include "sprites.h"
#include "tileData.h"
#include "vector2.h"

namespace game
{

    class Chicken
    {
    private:
        Vector2 _position;
        int _timeSinceLastMove;
        TileData _grassTile;

        const int _moveDelay = 500;
        const int _viewDistance = 5;

        TileData *FindGrass();

    public:
        Chicken(Vector2 position) : _position(position), _grassTile(TileData()){};
        ~Chicken();

        SpriteTypes GetSpriteType() const;
        Vector2 GetPosition() const;
        void Tick(int deltaTime);
    };

} // namespace game