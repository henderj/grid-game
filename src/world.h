#pragma once

#include <SDL2/SDL.h>
#include "camera.h"
#include "sprites.h"
#include "tileData.h"
#include "vector2.h"

namespace game
{
    namespace World
    {
        void Init(int w, int h);
        void Destroy();

        SDL_Surface *BuildWorld(SDL_Renderer *rend, SDL_Surface *sprites);
        void Render(SDL_Renderer *rend, Camera *cam, SDL_Texture *sprites);
        void Tick(int deltaTime);
        SpriteTypes GetSpriteTypeAtPos(const Vector2 &pos);
        SpriteTypes GetSpriteTypeAtPos(int x, int y);
        TileData *GetDataAtPos(const Vector2 &pos);
        TileData *GetDataAtPos(int x, int y);
    };
}