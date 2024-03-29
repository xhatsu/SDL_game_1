#include"func.h"

void correctDirection() {
	if (Direction[UP] == true && Direction[LEFT] == true) {
		Direction[UP_LEFT] = true;
	}
	if (Direction[DOWN] == true && Direction[LEFT] == true) {
		Direction[DOWN_LEFT] = true;
	}
	if (Direction[UP] == true && Direction[RIGHT] == true) {
		Direction[UP_RIGHT] = true;
	}
	if (Direction[DOWN] == true && Direction[RIGHT] == true) {
		Direction[DOWN_RIGHT] = true;
	}


	if (Direction[UP] == false || Direction[LEFT] == false) {
		Direction[UP_LEFT] = false;
	}
	if (Direction[DOWN] == false || Direction[LEFT] == false) {
		Direction[DOWN_LEFT] = false;
	}
	if (Direction[UP] == false || Direction[RIGHT] == false) {
		Direction[UP_RIGHT] = false;
	}
	if (Direction[DOWN] == false || Direction[RIGHT] == false) {
		Direction[DOWN_RIGHT] = false;
	}
}
SDL_Texture* loadTexture(std::string path) {
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
//load resources
//close
bool loadGlobalMedia() {
	bool success_state = true;
	_main_char = loadTexture("resources/main_char_sprite_sheet.png");
	if (_main_char == NULL) {
		printf("error loading main char");
		success_state = false;
	}
	grass_background = loadTexture("resources/grass_background.png");
	if (grass_background == NULL) {
		printf("error loading background");
		success_state = false;
	}
	mainChar_shadow = loadTexture("resources/mainChar_shadow.png");
	if (mainChar_shadow == NULL) {
		printf("error loading char shadow");
		success_state = false;
	}
	loadingScreen = loadTexture("resources/loading_screen.png");
	if (loadingScreen == NULL) {
			printf("error loading char shadow");
			success_state = false;
	}
	renderingScreen = loadTexture("resources/rendering_screen.png");
	if (renderingScreen == NULL) {
		printf("error loading char shadow");
		success_state = false;
	}
	return success_state;
}
bool loadTextureMedia() {
	bool success_state = true;
	treeTexture = loadTexture("resources/Tree.png");
	if (treeTexture == NULL) {
		printf("error loading object texture");
		success_state = false;
	}
	return success_state;
}
