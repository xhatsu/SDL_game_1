#include "main.h"


int main(int argc, char* args[]) {
	if (InitWindow() == true) {
		if (loadGlobalMedia() == true) {		
			srand((int)time(NULL));
			int seed = (rand()+176234)*3*(rand()/5+1)+174;
			printf("%d", seed);
			render_process render_map1(seed,2000,"mapData.json");
			render_map1.renderChunk(0, 0,50);
			render_map1.writeToFile();
			SDL_RenderClear(renderer);
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
			charCol.x = 0;
			charCol.y = 0;
			//test
			//pre render
			SDL_RenderPresent(renderer);
			//sort(objectList.begin(),objectList.end(),render_map1.);
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

