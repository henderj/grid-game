#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

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
                                       1000, 1000, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Surface *temp;
    temp = IMG_Load("capguy-walk.png");

    SDL_Texture *spritesheet = SDL_CreateTextureFromSurface(rend, temp);
    SDL_FreeSurface(temp);

    SDL_Rect windowRect;
    windowRect.w = 140;
    windowRect.h = 200;
    windowRect.x = (1000 - windowRect.w) / 2;
    windowRect.y = (1000 - windowRect.h) / 2;

    SDL_Rect textureRect;
    textureRect.x = 0;
    textureRect.y = 0;
    SDL_QueryTexture(spritesheet, NULL, NULL, &textureRect.w, &textureRect.h);

    textureRect.w /= 8;

    int close = 0;
    int speed = 10;

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

        if (windowRect.x + windowRect.w > 1000)
            windowRect.x = 1000 - windowRect.w;
        if (windowRect.x < 0)
            windowRect.x = 0;
        if (windowRect.y + windowRect.h > 1000)
            windowRect.y = 1000 - windowRect.h;
        if (windowRect.y < 0)
            windowRect.y = 0;

        int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
        textureRect.x = frame * textureRect.w;

        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, spritesheet, &textureRect, &windowRect);

        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyTexture(spritesheet);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}