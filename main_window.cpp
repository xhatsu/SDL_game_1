#include"main_window.h"
bool InitWindow() {
	bool success_state = true;
	//initialize

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize. SDL_ERROR: ", SDL_GetError());
		success_state = false;
	}
	else {
		main_window = SDL_CreateWindow("SDL_game_1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (main_window == NULL) {
			printf("Window could not be created SDL_Error:\n", SDL_GetError());
			success_state = false;
		}
		else {
			renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("renderer cannot be created", SDL_GetError());
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success_state = false;
				}
			}

		}

	}
	return success_state;
}
void close_window() {
	SDL_DestroyWindow(main_window);
	main_window = NULL;
	renderer = NULL;
	printf("closed window");
	SDL_Quit();
	IMG_Quit();
}