#include "world.h"

#include "utils.h"
#include "config.h"
#include "camera.h"
#include <SDL2/SDL.h>
#include <random>

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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 3);

    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            int index = distrib(gen);
            SDL_Point tileType = ground_types[index];

            SDL_Rect destrect;
            destrect.x = x * TILESIZE;
            destrect.y = y * TILESIZE;
            destrect.w = TILESIZE;
            destrect.h = TILESIZE;

            const SDL_Rect srcrect = GetSpriteRectFromSheet(&tileType);

            SDL_BlitSurface(sprites, &srcrect, mapSurface, &destrect);
        }
    }
    map = SDL_CreateTextureFromSurface(rend, mapSurface);

    return mapSurface;
}

void World::Render(SDL_Renderer *rend, Camera *cam)
{
    SDL_Rect mapRect;
    mapRect.x = -((cam->pos.x + width / 2) * TILESIZE);
    mapRect.y = -((cam->pos.y + height / 2) * TILESIZE);
    mapRect.w = width * TILESIZE;
    mapRect.h = height * TILESIZE;

    SDL_RenderCopy(rend, map, nullptr, &mapRect);
}