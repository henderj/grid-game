#pragma once

#include <SDL2/SDL.h>
#include "camera.h"
#include "chicken.h"
#include "sprites.h"
#include <vector>

class World
{
private:
    /* data */
    int width, height;
    SDL_Texture *map;
    std::vector<Chicken> chickens;

    const SpriteTypes groundTypes[3] = {DIRT, DIRT_COURSE, GRASS};
    const int groundTypesProbabilities[3] = {40, 40, 20};

public:
    World(int w, int h);
    ~World();

    SDL_Surface *BuildWorld(SDL_Renderer *rend, SDL_Surface *sprites);
    void Render(SDL_Renderer *rend, Camera *cam, SDL_Texture *sprites);
    void Tick(int deltaTime);
};