#include "main.h"


int main(int argc, char* args[]) {
	if (InitWindow() == true) {
		if (loadGlobalMedia() == true) {
			loadTextureMedia();
			SDL_RenderClear(renderer);
			srand((int)time(NULL));
			//rendering
			SDL_Delay(100);
			int seed = rand();
			printf("%d", seed);
			render_process render_map1(seed,720,"mapData.json");
			for (int i = -10; i <= 10; i++) {
				for (int j = -10; j <= 10; j++) {
					if (i == 0 && j == 0) continue;
					render_map1.renderChunk(i, j, 7);
				}
			}
			render_map1.writeToFile();
			//SDL_Delay(1000);
			//loading
			SDL_RenderCopy(renderer, loadingScreen, NULL, NULL);
			//main char texture initialize
			middle_screen.x = SCREEN_WIDTH / 2;
			middle_screen.y = SCREEN_HEIGHT / 2;
			charCol.x = 320;
			charCol.y = 320;
			//test
			//pre render
			SDL_RenderPresent(renderer);
			int menuState=100;
			//menu
			while (menuState != -1) {
				menuState = createGameMenu(renderer);
				//printf("\n menu %d", menuState);
				if (menuState == 0) {
					SDL_RenderCopy(renderer, loadingScreen, NULL, NULL);
					SDL_RenderPresent(renderer);
					printf("\n start game");
					quit = false;
					loop();
				}
				if (menuState == 1) {
					return 0;
				}
			}

			//start loop
			
			
		}
		else {
			printf("Cannot load media");
		}
	}
	else { printf("Error initialize"); }
	close_window();
	return 0;
}

