#pragma once
#include"Direction.h"
#include"EntityState.h"
#include<SDL.h>
#include<string>
#include<vector>
extern SDL_Renderer* renderer;
extern SDL_Rect char_location_rect;
extern SDL_Point middle_screen;
extern SDL_Point charCol;
extern SDL_Texture* rabbitTexture;
enum entityType {
	rabbit = 0,
	arrowType = 12
};
class entity
{
	public:
		int type;
		int state;
		int direction;
		int textureCounter;
		int delayAction=0;
		std::vector<SDL_Rect> objectTexturePollList;
		SDL_Point ObjCol;
		SDL_Rect ObjPlaceHolder;
		SDL_Rect objectRenderCordinate;
		SDL_Rect object_texture_rect;
		SDL_Rect objectDefaultTextureRect;
		SDL_Rect getTextureRectPoll();
		entity(int x, int y, int type,int state);
		void updateEntity();
		void loadEntity(SDL_Renderer* renderer);
		void moveEntity(int direction);
		void setObjRenderCordinate();
};

