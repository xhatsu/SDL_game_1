#pragma once
#include"SDL.h"
#include<stdio.h>
#include"SDL_image.h"
#include"SDL_ttf.h"
#include<string>
#include<vector>
extern SDL_Texture* submittingScore;
extern SDL_Window* main_window;
extern SDL_Renderer* renderer;
extern SDL_Texture* grass_background;
extern SDL_Texture* mainChar_shadow;
extern SDL_Texture* loadingScreen;
extern SDL_Texture* menuScreen;
extern SDL_Texture* treeTexture;
extern SDL_Texture* rabbitTexture;
extern SDL_Texture* boxTexture;
extern TTF_Font* pixelFont;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
void close_window();
bool InitWindow();
int createGameMenu(SDL_Renderer* renderer);