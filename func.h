#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
#include "Direction.h"
#include"json.hpp"
#include<math.h>
extern SDL_Texture* grass_background ;
extern SDL_Texture* tree_texture_1 ;
extern SDL_Renderer* renderer;
extern SDL_Texture* mainChar_shadow;
extern SDL_Texture* loadingScreen;
extern SDL_Texture* renderingScreen;
extern SDL_Texture* treeTexture;
extern SDL_Texture* rabbitTexture;
extern SDL_Texture* boxTexture;
extern TTF_Font* pixelFont;
extern SDL_Point middle_screen;
extern bool Direction[DIRECTION_TOTAL];
void correctDirection();
SDL_Texture* loadTexture(std::string path);
bool loadGlobalMedia();
bool loadTextureMedia();
double angleCaluculate(int corX, int corY);
void renderTransparentBlackRectangle(SDL_Renderer* renderer, SDL_Rect const & rect,int alpha);