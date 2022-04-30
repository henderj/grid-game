#include "world.h"

#include "utils.h"
#include "config.h"
#include <SDL2/SDL.h>
#include <random>

World::World(int w, int h)
{
    this->width = w;
    this->height = h;
}

World::~World()
{
}

SDL_Surface *World::BuildWorld(SDL_Surface *sprites)
{
    SDL_Surface *map_surface = CreateBlankSurface(this->width * TILESIZE, this->height * TILESIZE);

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

            SDL_BlitSurface(sprites, &srcrect, map_surface, &destrect);
        }
    }

    return map_surface;
}
