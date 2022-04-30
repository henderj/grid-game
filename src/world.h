#include <SDL2/SDL.h>

class World
{
private:
    /* data */
    int width, height;

    const SDL_Point DIRT = {0, 0};
    const SDL_Point DIRT_COURSE = {1, 0};
    const SDL_Point GRASS = {5, 0};

    const SDL_Point ground_types[3] = {DIRT, DIRT_COURSE, GRASS};

public:
    World(int w, int h);
    ~World();

    SDL_Surface *BuildWorld(SDL_Surface *sprites);
};