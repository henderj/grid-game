#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <random>

#include "src/config.h"
#include "src/World.h"

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

    World world = World(100, 100);

    SDL_Surface *temp_map = world.BuildWorld(temp);
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