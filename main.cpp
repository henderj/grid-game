#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <random>

#include "src/config.h"
#include "src/world.h"
#include "src/camera.h"

void PlayGame(SDL_Renderer *rend);

int main(int argc, char *argv[])
{

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    PlayGame(rend);

    // SDL_Surface *temp;
    // temp = IMG_Load("colored-transparent.png");
    // SDL_Texture *spritesheet = SDL_CreateTextureFromSurface(rend, temp);
    // // SDL_Surface *temp_map = world.BuildWorld(rend, temp);
    // // SDL_Texture *map = SDL_CreateTextureFromSurface(rend, temp_map);
    // // SDL_FreeSurface(temp_map);
    // SDL_FreeSurface(temp);
    // SDL_Rect windowRect;
    // SDL_QueryTexture(map, NULL, NULL, &windowRect.w, &windowRect.h);
    // windowRect.x = 0;
    // windowRect.y = 0;
    // World world = World(100, 100);
    // Camera cam = Camera(SCREEN_WIDTH / TILESIZE, SCREEN_HEIGHT / TILESIZE);
    // int close = 0;
    // int speed = 8;
    // while (!close)
    // {
    //     SDL_Event event;
    //     int totalFrames = 8;
    //     int delayPerFrame = 100;
    //     while (SDL_PollEvent(&event))
    //     {
    //         switch (event.type)
    //         {
    //         case SDL_QUIT:
    //             close = 1;
    //             break;
    //         default:
    //             cam.ProcessEvent(&event);
    //             break;
    //         }
    //     }
    //     SDL_SetRenderDrawColor(rend, 71, 45, 60, 255);
    //     SDL_RenderClear(rend);
    //     world.Render(rend, &cam);
    //     // SDL_RenderCopy(rend, map, NULL, &windowRect);
    //     SDL_RenderPresent(rend);
    //     SDL_Delay(1000 / 60);
    // }
    // SDL_DestroyTexture(spritesheet);
    // SDL_DestroyTexture(map);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

void PlayGame(SDL_Renderer *rend)
{
    SDL_Surface *temp;
    temp = IMG_Load("colored-transparent.png");
    SDL_Texture *spritesheet = SDL_CreateTextureFromSurface(rend, temp);
    World world = World(100, 100);
    world.BuildWorld(rend, temp);

    Camera cam;

    SDL_FreeSurface(temp);

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
            default:
                cam.ProcessEvent(&event);
                break;
            }
        }

        SDL_SetRenderDrawColor(rend, 71, 45, 60, 255);
        SDL_RenderClear(rend);

        world.Render(rend, &cam);

        // SDL_RenderCopy(rend, map, NULL, &windowRect);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyTexture(spritesheet);
}