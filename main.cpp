#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <random>

#include "src/config.h"

SDL_Rect GetSpriteRectFromSheet(const SDL_Point *pos)
{
    /*
    Tilesheet information:
    Tile size                 •  16px × 16px
    Space between tiles       •  1px × 1px
    ---
    Total tiles (horizontal)  •  49 tiles
    Total tiles (vertical)    •  22 tiles
    ---
    Total tiles in sheet      •  1078 tiles
    */
    SDL_Rect rect;
    rect.w = TILESIZE;
    rect.h = TILESIZE;
    rect.x = pos->x * TILESIZE + pos->x;
    rect.y = pos->y * TILESIZE + pos->y;
    return rect;
}

SDL_Surface *CreateBlankSurface(int w, int h)
{
    /* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
           as expected by OpenGL for textures */
    SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    surface = SDL_CreateRGBSurface(0, w, h, 32,
                                   rmask, gmask, bmask, amask);
    if (surface == NULL)
    {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }
    return surface;
}

SDL_Surface *BuildWorld(SDL_Surface *sprites, int w, int h)
{

    const SDL_Point DIRT = {0, 0};
    const SDL_Point DIRT_COURSE = {1, 0};
    const SDL_Point GRASS = {5, 0};

    const SDL_Point ground_types[3] = {DIRT,
                                       DIRT_COURSE,
                                       GRASS};

    SDL_Surface *map_surface = CreateBlankSurface(w * TILESIZE, h * TILESIZE);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 3);

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
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

class World
{
private:
    /* data */
public:
    World(int w, int h);
    ~World();
};

World::World(int w, int h)
{
}

World::~World()
{
}

int main(int argc, char *argv[])
{

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Window *win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    SDL_Surface *temp;
    temp = IMG_Load("colored-transparent.png");
    SDL_Texture *spritesheet = SDL_CreateTextureFromSurface(rend, temp);

    SDL_Surface *temp_map = BuildWorld(temp, 100, 100);
    SDL_Texture *map = SDL_CreateTextureFromSurface(rend, temp_map);

    SDL_FreeSurface(temp_map);
    SDL_FreeSurface(temp);

    SDL_Rect windowRect;
    SDL_QueryTexture(map, NULL, NULL, &windowRect.w, &windowRect.h);
    windowRect.x = 0;
    windowRect.y = 0;

    int close = 0;
    int speed = 8;

    while (!close)
    {
        SDL_Event event;
        int totalFrames = 8;
        int delayPerFrame = 100;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    windowRect.y -= speed;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    windowRect.x -= speed;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    windowRect.y += speed;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    windowRect.x += speed;
                    break;
                default:
                    break;
                }

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(rend, 71, 45, 60, 255);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, map, NULL, &windowRect);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyTexture(spritesheet);
    SDL_DestroyTexture(map);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}