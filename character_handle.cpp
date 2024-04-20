#include "character_handle.h"
void characterHandle::updateChar(int state,int direction) {
	switch (state) {
	case STANDSTILL:
		charTextureSpriteLocation.x = 320;
		switch (direction) {
		case UP:
			charTextureSpriteLocation.y = 512;
			break;
		case DOWN:
			charTextureSpriteLocation.y = 640;
			break;
		case LEFT:
			charTextureSpriteLocation.y = 576;
			break;
		case RIGHT:
			charTextureSpriteLocation.y = 704;
			break;
		default:
			break;
		}
		break;
	case MOVING:
		switch (direction) {
		case UP:
			charTextureSpriteLocation.y = 512;
			break;
		case DOWN:
			charTextureSpriteLocation.y = 640;
			break;
		case LEFT:
			charTextureSpriteLocation.y = 576;
			break;
		case RIGHT:
			charTextureSpriteLocation.y = 704;
			break;
		default:
			charTextureSpriteLocation.x = 64;
			break;
		}
		if (charTextureSpriteLocation.x == 0) {
			charTextureSpriteLocation.x = 64;
		}
		if (counter % charSpriteDelayRate == 0) {
			charTextureSpriteLocation.x += 64;
		}
		//delay animation
		counter++;
		if (charTextureSpriteLocation.x >= 576) {
			charTextureSpriteLocation.x = 64;
		}
		if (counter > 100) {
			counter = 0;
		}
		break;
	case ATTACKING:
		switch (direction) {
		case UP:
			charTextureSpriteLocation.y = 1024;
			break;
		case DOWN:
			charTextureSpriteLocation.y = 1152;
			break;
		case LEFT:
			charTextureSpriteLocation.y = 1088;;
			break;
		case RIGHT:
			charTextureSpriteLocation.y = 1216;
			break;
		default:
			break;
		}
		if (charTextureSpriteLocation.x == 0) {
			charTextureSpriteLocation.x = 64;
		}
		//delay animation
		counter++;
		if (counter % charSpriteDelayRate == 0) {
			charTextureSpriteLocation.x += 64;
		}		
		if (charTextureSpriteLocation.x >= 768) {
			charTextureSpriteLocation.x = 64;
		}
		if (counter > 100) {
			counter = 0;
		}
		break;
	default:
		break;
	}
	SDL_RenderCopy(renderer, charTexture, &charTextureSpriteLocation, &charRenderLocation);
}

characterHandle::characterHandle() {
	charTextureSpriteLocation.x = 0;
	charTextureSpriteLocation.y = 640;
	charTextureSpriteLocation.w = 64;
	charTextureSpriteLocation.h = 64;
	charRenderLocation.x = 1280 / 2 - 32;
	charRenderLocation.y = 720 / 2 - 64;
	charRenderLocation.w = 64;
	charRenderLocation.h = 64;
	state = -1;
	counter = 0;
	charSpriteDelayRate = 11;
	charTexture = loadCharTexture("resources/main_char_sprite_sheet.png");
}
void characterHandle::resetAim() {
	charTextureSpriteLocation.x = 0;
}
SDL_Texture* loadCharTexture(std::string path) {
	//define optimized surface
	SDL_Texture* newTexture = NULL;

	//load surface from image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Error load image to surface, IMG_Error: \n", IMG_GetError());
	}
	else
	{
		//create texture from surface
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("cannot cannot create texture from surface", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}