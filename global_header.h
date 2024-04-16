#pragma once
#include<SDL.h>
#include"Direction.h"
#include"background.h"
#include"chunk_control.h"
//enumerations for easy array declare
SDL_Window* main_window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* grass_background = NULL;
SDL_Texture* mainChar_shadow=NULL;
//SDL_Texture* tree_texture_1 = NULL;
SDL_Texture* loadingScreen = NULL;
SDL_Texture* renderingScreen = NULL;
SDL_Texture* treeTexture = NULL;
SDL_Texture* rabbitTexture = NULL;
SDL_Texture* boxTexture = NULL;
backGround mainBackGround;
bool Direction[8];
int speed = 2;
double MovementDelayRate = 1.8;
int fps = 165;
int desiredDelta = 1000 / fps;
bool moveState = false;
bool quit = false;
int distance = 0;
SDL_Point charCol;
SDL_Point middle_screen;