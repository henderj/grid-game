#include "camera.h"

#include <SDL2/SDL.h>
#include <array>

#include "vector2.h"
#include "renderData.h"
#include "config.h"
#include "utils.h"
#include "rect.h"

namespace game
{

    Camera::~Camera() {}

    void Camera::Move(int x, int y)
    {
        rect.x += x;
        rect.y += y;
    }

    void Camera::ProcessEvent(SDL_Event *event)
    {
        if (event->type != SDL_KEYDOWN)
            return;

        SDL_Keymod mods = SDL_GetModState();
        int moddedSpeed = speed;
        if (mods & (KMOD_CTRL))
            moddedSpeed *= 5;
        if (mods & (KMOD_SHIFT))
            moddedSpeed *= 10;

        SDL_Scancode key = event->key.keysym.scancode;

        if (key == SDL_SCANCODE_RIGHT || key == SDL_SCANCODE_D)
            Move(moddedSpeed, 0);
        if (key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_A)
            Move(-moddedSpeed, 0);
        if (key == SDL_SCANCODE_DOWN || key == SDL_SCANCODE_S)
            Move(0, -moddedSpeed);
        if (key == SDL_SCANCODE_UP || key == SDL_SCANCODE_W)
            Move(0, moddedSpeed);
    }

    int Camera::Render(SDL_Renderer *rend, SDL_Texture *worldMap,
                       Rect &worldRect, SpriteRenderData sprites[], int spritesSize,
                       SDL_Texture *spriteSheet)
    {
        int errorCount = 0;
        auto topLeft = rect.topLeft();
        auto worldPos = Vector2(worldRect.x, worldRect.y);
        Vector2 worldScreenPos = (worldPos - topLeft) * TILESIZE;
        worldScreenPos.y = -worldScreenPos.y;
        SDL_Rect mapRect = Rect(worldScreenPos.x, worldScreenPos.y,
                                worldRect.w * TILESIZE, worldRect.h * TILESIZE)
                               .toSDL_Rect();

        for (auto i = 0; i < spritesSize; i++)
        {
            SpriteRenderData &sprite = sprites[i];
            Vector2 screenPos = (sprite.pos - topLeft) * TILESIZE;
            screenPos.y = -screenPos.y;

            SDL_Rect spriteRect = GetSpriteRectFromSheet(sprite.type).toSDL_Rect();
            SDL_Rect screenRect = Rect(screenPos.x, screenPos.y, TILESIZE, TILESIZE).toSDL_Rect();

            errorCount += SDL_RenderCopy(rend, spriteSheet, &spriteRect, &screenRect);
        }

        errorCount += SDL_RenderCopy(rend, worldMap, nullptr, &mapRect);
        return errorCount;
    }

} // namespace game