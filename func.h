#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
enum DirectionEnum {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
	DIRECTION_TOTAL
};
extern SDL_Texture* grass_background ;
extern SDL_Texture* tree_texture_1 ;
extern SDL_Texture* _main_char;
extern SDL_Renderer* renderer;
extern bool Direction[DIRECTION_TOTAL];
void correctDirection();
SDL_Texture* loadTexture(std::string path);
bool loadGlobalMedia();


