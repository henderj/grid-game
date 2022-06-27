#pragma once

#include <SDL2/SDL.h>
#include "vector2.h"

namespace game
{

    class Camera
    {
    private:
        int speed;

    public:
        Vector2 pos;

        Camera();
        ~Camera();

        void Move(int x, int y);
        void ProcessEvent(SDL_Event *event);
    };

} // namespace game