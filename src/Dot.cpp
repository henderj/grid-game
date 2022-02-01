//
// Created by tonystank on 1/31/22.
//

#include "Dot.h"
#include "config.h"
#include "LTexture.h"
Dot::Dot(LTexture *_texture)
{
    texture = _texture;
    //Initialize the position
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent(SDL_Event &e)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= DOT_VEL;
            break;
        case SDLK_DOWN:
            mVelY += DOT_VEL;
            break;
        case SDLK_LEFT:
            mVelX -= DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += DOT_VEL;
            break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += DOT_VEL;
            break;
        case SDLK_DOWN:
            mVelY -= DOT_VEL;
            break;
        case SDLK_LEFT:
            mVelX += DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= DOT_VEL;
            break;
        }
    }
}

void Dot::move(float timeStep)
{
    //Move the dot left or right
    mPosX += mVelX * timeStep;

    //If the dot went too far to the left or right
    if (mPosX < 0)
    {
        mPosX = 0;
    }
    else if (mPosX > SCREEN_WIDTH - DOT_WIDTH)
    {
        mPosX = SCREEN_WIDTH - DOT_WIDTH;
    }

    //Move the dot up or down
    mPosY += mVelY * timeStep;

    //If the dot went too far up or down
    if (mPosY < 0)
    {
        mPosY = 0;
    }
    else if (mPosY > SCREEN_HEIGHT - DOT_HEIGHT)
    {
        mPosY = SCREEN_HEIGHT - DOT_HEIGHT;
    }
}

void Dot::render()
{
    //Show the dot
    texture->render((int)mPosX, (int)mPosY);
}
