#include "world.h"

#include "utils.h"
#include "config.h"
#include "camera.h"
#include "sprites.h"
#include <SDL2/SDL.h>
#include <random>
#include <cstdlib>
#include <ctime>

World::World(int w, int h)
{
    this->width = w;
    this->height = h;
}

World::~World()
{
    SDL_DestroyTexture(map);
}

SDL_Surface *World::BuildWorld(SDL_Renderer *rend, SDL_Surface *sprites)
{
    SDL_Surface *mapSurface = CreateBlankSurface(this->width * TILESIZE, this->height * TILESIZE);

    std::srand((unsigned)std::time(0));
    auto randomGroundType = [this]() -> SpriteTypes
    {
        auto num = std::rand() % 100;
        for (auto i = 0; i < sizeof(groundTypes); i++)
        {
            if (num < groundTypesProbabilities[i])
            {
                return groundTypes[i];
            }
            num -= groundTypesProbabilities[i];
        }
        return groundTypes[0];
    };

    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            SpriteTypes tileType = randomGroundType();

            SDL_Rect destrect;
            destrect.x = x * TILESIZE;
            destrect.y = y * TILESIZE;
            destrect.w = TILESIZE;
            destrect.h = TILESIZE;

            const SDL_Rect srcrect = GetSpriteRectFromSheet(tileType);

            SDL_BlitSurface(sprites, &srcrect, mapSurface, &destrect);
        }
    }
    map = SDL_CreateTextureFromSurface(rend, mapSurface);

    SDL_Point cPos;
    cPos.x = 0;
    cPos.y = 0;
    Chicken c = Chicken(cPos);

    chickens.push_back(c);

    return mapSurface;
}

void World::Render(SDL_Renderer *rend, Camera *cam, SDL_Texture *sprites)
{
    SDL_Rect mapRect;
    mapRect.x = -((cam->pos.x + width / 2) * TILESIZE);
    mapRect.y = -((cam->pos.y + height / 2) * TILESIZE);
    mapRect.w = width * TILESIZE;
    mapRect.h = height * TILESIZE;

    for (int i = 0; i < chickens.size(); i++)
    {
        SDL_Point pos = chickens[i].GetPosition();
        if (!SDL_PointInRect(&pos, &mapRect))
            continue;

        SDL_Rect chickenRect;
        chickenRect.x = ((pos.x - cam->pos.x) * TILESIZE) + SCREEN_CENTER_X;
        chickenRect.y = ((pos.y - cam->pos.y) * TILESIZE) + SCREEN_CENTER_Y;
        chickenRect.w = TILESIZE;
        chickenRect.h = TILESIZE;

        SDL_Rect spriteRect = GetSpriteRectFromSheet(chickens[i].GetSpriteType());

        SDL_RenderCopy(rend, sprites, &spriteRect, &chickenRect);
    }

    SDL_RenderCopy(rend, map, nullptr, &mapRect);
}

void World::Tick(int deltaTime)
{
    for (int i = 0; i < chickens.size(); i++)
    {
        chickens[i].Tick(deltaTime);
    }
}