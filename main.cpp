#include "main.h"


int main(int argc, char* args[]) {
	if (InitWindow() == true) {
		if (loadGlobalMedia() == true) {
			loadTextureMedia();
			SDL_RenderClear(renderer);
			srand((int)time(NULL));
			//rendering
			SDL_Delay(100);
			SDL_RenderCopy(renderer, renderingScreen, NULL, NULL);
			int seed = rand();
			printf("%d", seed);
			render_process render_map1(seed,720,"mapData.json");
			for (int i = -10; i <= 10; i++) {
				for (int j = -10; j <= 10; j++) {
					render_map1.renderChunk(i, j, 15);
				}
			}
			render_map1.writeToFile();
			//SDL_Delay(1000);
			//loading
			SDL_RenderCopy(renderer, loadingScreen, NULL, NULL);
			//main char texture initialize
			middle_screen.x = SCREEN_WIDTH / 2;
			middle_screen.y = SCREEN_HEIGHT / 2;
			charCol.x = 640;
			charCol.y = 640;
			//test
			//pre render
			SDL_RenderPresent(renderer);
			//start loop
			loop();
			
		}
		else {
			printf("Cannot load media");
		}
	}
	else { printf("Error initialize"); }
	close_window();
	return 0;
}

