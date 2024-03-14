#pragma once
#include<SDL.h>
#include"Direction.h"
extern SDL_Renderer* renderer;
extern SDL_Texture* grass_background;
extern int speed;
class Chunk {
public:
	SDL_Rect background_rect;
	SDL_Rect background_rect_DOWN;
	SDL_Rect background_rect_UP;
	SDL_Rect background_rect_LEFT;
	SDL_Rect background_rect_RIGHT;
	SDL_Rect background_rect_UP_LEFT;
	SDL_Rect background_rect_DOWN_LEFT;
	SDL_Rect background_rect_UP_RIGHT;
	SDL_Rect background_rect_DOWN_RIGHT;
	Chunk() {
			background_rect.x = 0;
			background_rect.y = 0;
			background_rect.w = 2560;
			background_rect.h = 1440;

			background_rect_DOWN.x = 0;
			background_rect_DOWN.y = 1440;
			background_rect_DOWN.w = 2560;
			background_rect_DOWN.h = 1440;

			background_rect_UP.x = 0;
			background_rect_UP.y = -1440;
			background_rect_UP.w = 2560;
			background_rect_UP.h = 1440;

			background_rect_LEFT.x = -2560;
			background_rect_LEFT.y = 0;
			background_rect_LEFT.w = 2560;
			background_rect_LEFT.h = 1440;

			background_rect_RIGHT.x = 2560;
			background_rect_RIGHT.y = 0;
			background_rect_RIGHT.w = 2560;
			background_rect_RIGHT.h = 1440;

			background_rect_UP_LEFT.x = -2560;
			background_rect_UP_LEFT.y = -1440;
			background_rect_UP_LEFT.w = 2560;
			background_rect_UP_LEFT.h = 1440;

			background_rect_UP_RIGHT.x = 2560;
			background_rect_UP_RIGHT.y = -1440;
			background_rect_UP_RIGHT.w = 2560;
			background_rect_UP_RIGHT.h = 1440;

			background_rect_DOWN_RIGHT.x = 2560;
			background_rect_DOWN_RIGHT.y = 1440;
			background_rect_DOWN_RIGHT.w = 2560;
			background_rect_DOWN_RIGHT.h = 1440;

			background_rect_DOWN_LEFT.x = -2560;
			background_rect_DOWN_LEFT.y = 1440;
			background_rect_DOWN_LEFT.w = 2560;
			background_rect_DOWN_LEFT.h = 1440;
	}
	void renderChunk();
	void stickChunk();
	void moveChunk(int direction);
	void updateChunk(unsigned int state);

};