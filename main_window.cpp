#include"main_window.h"
bool InitWindow() {
	bool success_state = true;
	//initialize
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize. SDL_ERROR: %s", SDL_GetError());
		success_state = false;
	}
	else {
		main_window = SDL_CreateWindow("Hunt 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (main_window == NULL) {
			printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
			success_state = false;
		}
		else {
			renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("renderer cannot be created %s", SDL_GetError());
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success_state = false;
				}
				if (TTF_Init() < 0) {
					success_state = false;
					printf("SDL_ttf could not initialize! %s\n ", TTF_GetError());
				}
				SDL_Surface* icon = IMG_Load("resources/icon.png");
				SDL_SetWindowIcon(main_window, icon);
				SDL_FreeSurface(icon);
				icon = NULL;
			}

		}

	}
	return success_state;
}
int createGameMenu(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, menuScreen, NULL, NULL);
    // Load the font and create a color for the text
    SDL_Color textColor = { 255, 255, 255 }; // white color
	int menuChoose = 100;
    // Create the menu items
    std::vector<std::string> menuItems = { "Start Game", "Exit" };
    // Render the menu items
    std::vector<SDL_Rect> menuItemRects(menuItems.size());
    for (int i = 0; i < menuItems.size(); i++) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(pixelFont, menuItems[i].c_str(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        SDL_Rect& textRect = menuItemRects[i];
        textRect.x = 50;
        textRect.y = 50 + i * 60;
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
    }
    SDL_RenderPresent(renderer);

    SDL_Event event_input;
    while (SDL_WaitEvent(&event_input)) {
        if (event_input.type == SDL_QUIT) {
			return -1;
            break;
        }
        else if (event_input.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            for (int i = 0; i < menuItemRects.size(); i++) {
				SDL_Point mouse;
				mouse.x = x;
				mouse.y = y;
                if (SDL_PointInRect(&mouse, &menuItemRects[i])) {
					menuChoose = i;
                    break;
                }
            }
        }
    }
	return menuChoose;
}
void close_window() {
	SDL_DestroyWindow(main_window);
	SDL_DestroyTexture(treeTexture);
	SDL_DestroyTexture(grass_background);
	SDL_DestroyTexture(mainChar_shadow);
	SDL_DestroyTexture(loadingScreen);
	SDL_DestroyTexture(menuScreen);
	SDL_DestroyTexture(rabbitTexture);
	SDL_DestroyTexture(boxTexture);
	SDL_DestroyTexture(submittingScore);
	TTF_CloseFont(pixelFont);
	printf("closed window");
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}