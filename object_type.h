#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"Direction.h"
#include <algorithm>
#include"ObjectTypeEnum.h"
extern SDL_Rect char_location_rect;
extern SDL_Point middle_screen;
extern SDL_Point charCol;
extern SDL_Texture* treeTexture;
class object {
public:
	object(int x, int y,int type);
	int type;
	SDL_Point ObjCol;
	SDL_Rect ObjPlaceHolder;
	SDL_Rect objectRenderCordinate;
	SDL_Rect object_texture_rect;
	void loadObject(SDL_Renderer* renderer);
	void moveObject(int direction);
	void setObjRenderCordinate();
};
SDL_Texture* loadTexture(std::string path);
