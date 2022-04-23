#include <SDL2/SDL.h>
#include "config.h"

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
