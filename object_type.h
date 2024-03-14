#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
extern SDL_Rect char_location_rect;
class object {
public:
	SDL_Rect object_cordinate;
	SDL_Texture* object_texture;
	SDL_Rect object_texture_rect;
	bool loadTextureMedia();
	void loadObject(SDL_Rect a,SDL_Renderer* renderer);
	object();
};
SDL_Texture* loadTexture(std::string path);
