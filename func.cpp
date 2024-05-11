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
	if ((Direction[LEFT] == true && Direction[RIGHT] == true) || (Direction[UP] == true && Direction[DOWN] == true)) {
		Direction[LEFT] == false;
		Direction[RIGHT] == false;
		Direction[UP] == false;
		Direction[DOWN] == false;
	}
}
SDL_Texture* loadTexture(std::string path) {
	//define optimized surface
	SDL_Texture* newTexture = NULL;

	//load surface from image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Error load image to surface, IMG_Error: %s\n", IMG_GetError());
	}
	else
	{
		//create texture from surface
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("cannot cannot create texture from surface %s", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
//load resources
//close
bool loadGlobalMedia() {
	bool success_state = true;
	grass_background = loadTexture("resources/grass_background.png");
	if (grass_background == NULL) {
		printf("error loading background");
		success_state = false;
	}
	loadingScreen = loadTexture("resources/loading_screen.png");
	if (loadingScreen == NULL) {
			printf("error loading loading screen");
			success_state = false;
	}
	menuScreen = loadTexture("resources/menuScreen.png");
	if (menuScreen == NULL) {
		printf("error loading menu screen");
		success_state = false;
	}
	pixelFont = TTF_OpenFont("resources/PixelEmulator-xq08.ttf",24);
	if (pixelFont == NULL) {
		printf("cannot load font");
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
	rabbitTexture = loadTexture("resources/Rabbit.png");
	if (rabbitTexture == NULL) {
		printf("error loading object texture");
		success_state = false;
	}
	boxTexture = loadTexture("resources/Box.png");
	if (boxTexture == NULL) {
		printf("error loading object texture");
		success_state = false;
	}
	return success_state;
	grassTexture = loadTexture("resources/Grass.png");
	if (boxTexture == NULL) {
		printf("error loading object texture");
		success_state = false;
	}
}
double angleCaluculate(int corX, int corY) {
	double d = double(corY);
	double k = double(corX);
	//printf("\nx:%f", k);
	//printf("\ny:%f", d);
	double tan = d / k;
	double arctan = atan(tan);
	return arctan * 180 / 3.1415;
}
void renderTransparentBlackRectangle(SDL_Renderer* renderer, SDL_Rect const & rect,int alpha) {
	// Save the current draw color
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	// Set the blend mode for the renderer to blend the alpha channel
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Set the draw color to black with 50% transparency
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);

	// Render the rectangle
	SDL_RenderFillRect(renderer, &rect);

	// Restore the original draw color
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}