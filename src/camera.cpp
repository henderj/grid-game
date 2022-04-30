#include "camera.h"
#include <SDL2/SDL.h>

Camera::Camera()
{
    pos.x = 0;
    pos.y = 0;

    speed = 1;
}

void Camera::Move(int x, int y)
{
    pos.x += x;
    pos.y += y;
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
        Move(0, moddedSpeed);
    if (key == SDL_SCANCODE_UP || key == SDL_SCANCODE_W)
        Move(0, -moddedSpeed);
}

Camera::~Camera()
{
}
