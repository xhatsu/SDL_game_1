#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"Direction.h"
#include"CharState.h"
extern SDL_Renderer* renderer;
class characterHandle
{
public:
	SDL_Rect charTextureSpriteLocation;
	SDL_Rect charRenderLocation;
	SDL_Texture* charTexture;
	int state;
	int charSpriteDelayRate;
	int counter;
	void updateChar(int state,int direction);
	characterHandle();
};
SDL_Texture* loadCharTexture(std::string path);

