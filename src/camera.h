#pragma once

#include <SDL2/SDL.h>
#include "vector2.h"
#include "renderData.h"
#include "rect.h"

namespace game
{

    class Camera
    {
    private:
        int speed;

    public:
        Rect rect;

        Camera();
        Camera(Rect rect) : rect(rect) {}
        Camera(float x, float y, float w, float h) : rect(Rect(x, y, w, h)) {}
        ~Camera();

        void Move(int x, int y);
        void ProcessEvent(SDL_Event *event);
        int Render(SDL_Renderer *rend, SDL_Texture *worldMap,
                   Rect &worldRect, SpriteRenderData sprites[], int spritesSize,
                   SDL_Texture *spriteSheet);
    };

} // namespace game