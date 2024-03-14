#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"Direction.h"
extern SDL_Rect char_location_rect;
extern SDL_Point middle_screen;
extern SDL_Point charCol;
class object {
public:
	object(int x, int y);
	SDL_Point ObjCol;
	SDL_Rect objectRenderCordinate;
	SDL_Texture* object_texture;
	SDL_Rect object_texture_rect;
	bool loadTextureMedia();
	void loadObject(SDL_Renderer* renderer);
	void moveObject(int direction);
	void setObjRenderCordinate();
};
SDL_Texture* loadTexture(std::string path);
