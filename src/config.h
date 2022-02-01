//
// Created by tonystank on 1/31/22.
//
#pragma once
#ifndef GRID_GAME_CONFIG_H

#define GRID_GAME_CONFIG_H
#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Scene textures
LTexture gDotTexture;
#endif //GRID_GAME_CONFIG_H
