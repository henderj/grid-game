#include "world.h"

#include "utils.h"
#include "config.h"
#include "camera.h"
#include "sprites.h"
#include "chicken.h"
#include "random.h"
#include "vector2.h"
#include "rect.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <vector>
#include <iostream>

namespace game
{
    namespace World
    {
        namespace
        {
            int width, height;
            SDL_Texture *map;
            std::vector<Chicken> chickens;
            std::vector<SpriteTypes> mapTileTypes;

            const SpriteTypes groundTypes[4] = {DIRT, DIRT_COURSE, GRASS, GRASS_LONG};
            const int groundTypesProbabilities[4] = {50, 25, 20, 5};

            int GetTileIndexFromPos(int x, int y)
            {
                int offsetX = x + width / 2;
                int offsetY = y + height / 2;
                return x * height + y;
            }

            int GetTileIndexFromPos(const Vector2 *pos)
            {
                return GetTileIndexFromPos(pos->x, pos->y);
            }
        }

        void Init(int w, int h)
        {
            width = w;
            height = h;
        }

        void Destroy()
        {
            SDL_DestroyTexture(map);
        }

        SDL_Texture *BuildWorld(SDL_Renderer *rend, SDL_Surface *sprites)
        {
            SDL_Surface *mapSurface = CreateBlankSurface(width * TILESIZE, height * TILESIZE);

            auto randomGroundType = [&]() -> SpriteTypes
            {
                auto num = random::range(0, 100);
                for (auto i = 0; i < sizeof(groundTypes); i++)
                {
                    if (num < groundTypesProbabilities[i])
                    {
                        return groundTypes[i];
                    }
                    num -= groundTypesProbabilities[i];
                }
                return groundTypes[0];
            };

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    SpriteTypes tileType = SpriteTypes::GRASS; // randomGroundType();

                    SDL_Rect destrect;
                    destrect.x = x * TILESIZE;
                    destrect.y = y * TILESIZE;
                    destrect.w = TILESIZE;
                    destrect.h = TILESIZE;

                    const SDL_Rect srcrect = GetSpriteRectFromSheet(tileType).toSDL_Rect();

                    SDL_BlitSurface(sprites, &srcrect, mapSurface, &destrect);
                    mapTileTypes.push_back(tileType);
                }
            }
            map = SDL_CreateTextureFromSurface(rend, mapSurface);

            Vector2 cPos(0, 0);
            // Chicken c = Chicken(cPos);

            // chickens.push_back(c);

            return map;
        }

        SpriteTypes GetSpriteTypeAtPos(int x, int y)
        {

            auto index = GetTileIndexFromPos(x, y);
            return mapTileTypes[index];
        }

        SpriteTypes GetSpriteTypeAtPos(const Vector2 &pos)
        {
            return GetSpriteTypeAtPos(pos.x, pos.y);
        }

        TileData *GetDataAtPos(int x, int y)
        {

            TileData data;
            data.type = GetSpriteTypeAtPos(x, y);
            data.x = x;
            data.y = y;
            TileData *ptr = &data;
            return ptr;
        }

        TileData *GetDataAtPos(const Vector2 &pos)
        {
            return GetDataAtPos(pos.x, pos.y);
        }

        void Render(SDL_Renderer *rend, Camera &cam, SDL_Texture *spriteSheet)
        {
            // Rect worldRect = Rect(0, 0, width, height);
            // SpriteRenderData data[] = {}; //{SpriteRenderData(Vector2(0, 0), SpriteTypes::CHICKEN)};
            // int errorCount = cam.Render(rend, map, worldRect, data, 0, spriteSheet);

            // std::cout << errorCount << "\n";

            SDL_Rect mapRect;
            mapRect.x = -((cam.rect.x + width / 2) * TILESIZE);
            mapRect.y = -((cam.rect.y + height / 2) * TILESIZE);
            mapRect.w = width * TILESIZE;
            mapRect.h = height * TILESIZE;

            for (int i = 0; i < chickens.size(); i++)
            {
                Vector2 pos = chickens[i].GetPosition();
                SDL_Point p = pos.toSDL_Point();
                if (!SDL_PointInRect(&p, &mapRect))
                    continue;

                SDL_Rect chickenRect;
                chickenRect.x = ((pos.x - cam.rect.x) * TILESIZE) + SCREEN_CENTER_X;
                chickenRect.y = ((pos.y - cam.rect.y) * TILESIZE) + SCREEN_CENTER_Y;
                chickenRect.w = TILESIZE;
                chickenRect.h = TILESIZE;

                SDL_Rect spriteRect = GetSpriteRectFromSheet(chickens[i].GetSpriteType()).toSDL_Rect();

                SDL_RenderCopy(rend, spriteSheet, &spriteRect, &chickenRect);
            }

            SDL_RenderCopy(rend, map, nullptr, &mapRect);
        }

        void Tick(int deltaTime)
        {
            for (int i = 0; i < chickens.size(); i++)
            {
                chickens[i].Tick(deltaTime);
            }
        }
    }
} // namespace game