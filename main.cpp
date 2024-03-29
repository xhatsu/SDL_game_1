#include "main.h"


int main(int argc, char* args[]) {
	if (InitWindow() == true) {
		if (loadGlobalMedia() == true) {
			loadTextureMedia();
			srand((int)time(NULL));
			//rendering
			SDL_RenderCopy(renderer, renderingScreen, NULL, NULL);
			int seed = rand();
			printf("%d", seed);
			render_process render_map1(seed,1280,"mapData.json");
			for (int i = -10; i <= 10; i++) {
				for (int j = -10; j <= 10; j++) {
					render_map1.renderChunk(i, j, 20);
				}
			}
			render_map1.writeToFile();
			SDL_Delay(1000);
			//loading
			SDL_RenderCopy(renderer, loadingScreen, NULL, NULL);
			//main char texture initialize
			if (true) {
				_main_char_rect.x = 0;
				_main_char_rect.y = 640;
				_main_char_rect.w = 64;
				_main_char_rect.h = 64;
				char_location_rect.x = SCREEN_WIDTH / 2 - 32;
				char_location_rect.y = SCREEN_HEIGHT / 2 - 64;
				char_location_rect.w = 64;
				char_location_rect.h = 64;
				mainChar_shadow_Rect.x = 0;
				mainChar_shadow_Rect.y = 0;
				mainChar_shadow_Rect.w = 64;
				mainChar_shadow_Rect.h = 64;
				SDL_SetTextureAlphaMod(mainChar_shadow, 80);
			}
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

