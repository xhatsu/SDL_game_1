#include "main.h"


int main(int argc, char* args[]) {
	if (InitWindow() == true) {
		if (loadGlobalMedia() == true) {			
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);			
			//main char texture initialize
			if (true) {
				_main_char_rect.x = 0;
				_main_char_rect.y = 640;
				_main_char_rect.w = 64;
				_main_char_rect.h = 64;
				char_location_rect.x = SCREEN_WIDTH / 2 - 32;
				char_location_rect.y = SCREEN_HEIGHT / 2 - 32;
				char_location_rect.w = 64;
				char_location_rect.h = 64;
			}
			middle_screen.x = SCREEN_WIDTH / 2;
			middle_screen.y = SCREEN_HEIGHT / 2;
			charCol.x = 0;
			charCol.y = 0;
			SDL_RenderCopy(renderer, grass_background, NULL, &a.background_rect);
			SDL_RenderCopy(renderer, _main_char, &_main_char_rect, &char_location_rect);
			//test
			
			//test
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

