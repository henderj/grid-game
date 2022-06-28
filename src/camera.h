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
        float speed;
        Rect rect;

    public:
        Camera(Rect rect) : rect(rect), speed(1) {}
        Camera(float x, float y, float w, float h, float speed) : rect(Rect(x, y, w, h)), speed(speed) {}
        ~Camera();

        void Move(int x, int y);
        void ProcessEvent(SDL_Event *event);
        int Render(SDL_Renderer *rend, SDL_Texture *worldMap,
                   Rect &worldRect, SpriteRenderData sprites[], int spritesSize,
                   SDL_Texture *spriteSheet);
    };

} // namespace game