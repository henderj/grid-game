#pragma once

#include <SDL2/SDL.h>
#include "camera.h"
#include "chicken.h"
#include <vector>

class World
{
private:
    /* data */
    int width, height;
    SDL_Texture *map;
    std::vector<Chicken> chickens;

    const SDL_Point DIRT = {0, 0};
    const SDL_Point DIRT_COURSE = {1, 0};
    const SDL_Point GRASS = {5, 0};

    const SDL_Point ground_types[3] = {DIRT, DIRT_COURSE, GRASS};

public:
    World(int w, int h);
    ~World();

    SDL_Surface *BuildWorld(SDL_Renderer *rend, SDL_Surface *sprites);
    void Render(SDL_Renderer *rend, Camera *cam, SDL_Texture *sprites);
    void Tick(int deltaTime);
};