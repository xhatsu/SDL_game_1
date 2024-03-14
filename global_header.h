#pragma once
#include<SDL.h>
#include"Direction.h"
#include"background.h"
//enumerations for easy array declare
SDL_Window* main_window = NULL;
SDL_Rect _main_char_rect;
SDL_Rect char_location_rect;
SDL_Renderer* renderer = NULL;
SDL_Texture* grass_background = NULL;
SDL_Texture* _main_char = NULL;
SDL_Texture* tree_texture_1 = NULL;
Chunk a;
bool Direction[8];
int speed = 2;
int charSpriteDelay = 0;
int charSpriteDelayRate = 11;
double MovementDelayRate = 1.7;
int fps = 165;
int desiredDelta = 1000 / fps;
bool moveState = false;
bool quit = false;
int distance = 0;