#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <random>

#include "src/config.h"

SDL_Rect getSpritesheetRect(const SDL_Point *pos)
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
    rect.w = 16;
    rect.h = 16;
    rect.x = pos->x * 16 + pos->x;
    rect.y = pos->y * 16 + pos->y;
    return rect;
}

SDL_Surface *buildWorld(SDL_Surface *sprites, int w, int h)
{
    /*
    self.tiles = np.zeros(self.size, np.int16)
        ground_types = [TileTypes.DIRT, TileTypes.DIRT_COURSE, TileTypes.GRASS]
        for x in range(self.size[0]):
            for y in range(self.size[1]):
                tile = choice(ground_types)
                self.tiles[x][y] = tile.value

        self.entities: list[Entity] = []
        self.entities.append(Chicken(Vector2(0,0)))
        self.entities.append(Chicken(Vector2(5,0)))
        self.entities.append(Chicken(Vector2(-4,3)))

    def load_surfaces(self, sheet: list[Surface]):
        for x in range(self.size[0]):
            for y in range(self.size[1]):
                surfacepos = (x*TILESIZE, y*TILESIZE)
                rect = Rect(surfacepos[0],surfacepos[1],TILESIZE,TILESIZE)
                self.map_surface.blit(sheet[self.tiles[x][y]], rect)
    */

    const SDL_Point DIRT = {0, 0};
    const SDL_Point DIRT_COURSE = {1, 0};
    const SDL_Point GRASS = {5, 0};

    const SDL_Point ground_types[3] = {DIRT,
                                       DIRT_COURSE,
                                       GRASS};

    SDL_Point tiles[w][h];

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

    surface = SDL_CreateRGBSurface(0, w * 16, h * 16, 32,
                                   rmask, gmask, bmask, amask);
    if (surface == NULL)
    {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    SDL_Surface *map_surface = surface;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 3);

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            int index = distrib(gen);
            SDL_Point tileType = tiles[x][y] = ground_types[index];

            SDL_Rect destrect;
            destrect.x = x * 16;
            destrect.y = y * 16;
            destrect.w = 16;
            destrect.h = 16;

            const SDL_Rect srcrect = getSpritesheetRect(&tileType);

            SDL_BlitSurface(sprites, &srcrect, map_surface, &destrect);
        }
    }

    return map_surface;
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

    SDL_Surface *temp_map = buildWorld(temp, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16);
    SDL_Texture *map = SDL_CreateTextureFromSurface(rend, temp_map);

    SDL_FreeSurface(temp_map);
    SDL_FreeSurface(temp);

    SDL_Rect windowRect;
    windowRect.w = SCREEN_WIDTH;
    windowRect.h = SCREEN_HEIGHT;
    windowRect.x = 0;
    windowRect.y = 0;

    // SDL_Rect textureRect = getSpritesheetRect(1, 0);

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

        // if (windowRect.x + windowRect.w > SCREEN_WIDTH)
        //     windowRect.x = 1000 - windowRect.w;
        // if (windowRect.x < 0)
        //     windowRect.x = 0;
        // if (windowRect.y + windowRect.h > SCREEN_HEIGHT)
        //     windowRect.y = 1000 - windowRect.h;
        // if (windowRect.y < 0)
        //     windowRect.y = 0;

        // int frame = (SDL_GetTicks() / delayPerFrame) % totalFrames;
        // textureRect.x = frame * textureRect.w;

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