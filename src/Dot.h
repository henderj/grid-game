//
// Created by tonystank on 1/31/22.
//

#ifndef GRID_GAME_DOT_H
#define GRID_GAME_DOT_H

#include "LTexture.h"
#include <SDL.h>

//The dot that will move around on the screen
class Dot
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 64;
    static const int DOT_HEIGHT = 64;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 640;

    //Initializes the variables
    Dot(LTexture _texture);

    //Takes key presses and adjusts the dot's velocity
    void handleEvent(SDL_Event &e);

    //Moves the dot
    void move(float timeStep);

    //Shows the dot on the screen
    void render();

private:
    float mPosX, mPosY;
    float mVelX, mVelY;
    LTexture texture;
};

#endif //GRID_GAME_DOT_H
