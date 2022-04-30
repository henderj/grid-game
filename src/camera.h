#pragma once

#include <SDL2/SDL.h>

class Camera
{
private:
    int speed;

public:
    SDL_Point pos;

    Camera();
    ~Camera();

    void Move(int x, int y);
    void ProcessEvent(SDL_Event *event);
};
