#include"loop.h"
void loop() {
	mapProcess map1;
	map1.getChunkList("mapData.json");
	map1.activeChunk.push_back(map1.chunkList.at(0));
	SDL_Rect shadow_rect;
	shadow_rect.w = char_location_rect.w;
	shadow_rect.h = char_location_rect.h;
	shadow_rect.x = char_location_rect.x;
	shadow_rect.y = char_location_rect.y + 5;
	mainBackGround.updateChunk(-1);
	_main_char_rect.x = 512;
	//render first time
	SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
	map1.updateMap(false);
	SDL_RenderCopy(renderer, _main_char, &_main_char_rect, &char_location_rect);
	map1.updateMap(true);
	SDL_Delay(1000);
	//input handle
	bool WaitForInput = true;
	SDL_Event event_input;
	const Uint8* key_state = SDL_GetKeyboardState(NULL);
	int start_loop = SDL_GetTicks64();
	while (quit == false) {
		while (SDL_PollEvent(&event_input)) {
			if (event_input.type == SDL_QUIT) { quit = true; }
			//movement handle
			if (true) {
	
				if (event_input.type == SDL_KEYDOWN) {
					//reset
					if (key_state[SDL_SCANCODE_L]) {
						distance = 0;
						charCol.x = 0;
						charCol.y = 0;
					}
					if (key_state[SDL_SCANCODE_T]) {
						
					}
					if (key_state[SDL_SCANCODE_A]) {
						Direction[LEFT] = true;
					}
					if (key_state[SDL_SCANCODE_W]) {
						Direction[UP] = true;
					}
					if (key_state[SDL_SCANCODE_S]) {
						Direction[DOWN] = true;
					}
					if (key_state[SDL_SCANCODE_D]) {
						Direction[RIGHT] = true;
					}
				}
				if (event_input.type == SDL_KEYUP) {

					if (!key_state[SDL_SCANCODE_A]) {
						Direction[LEFT] = false;
					}
					if (!key_state[SDL_SCANCODE_W]) {
						Direction[UP] = false;
					}
					if (!key_state[SDL_SCANCODE_S]) {
						Direction[DOWN] = false;
					}
					if (!key_state[SDL_SCANCODE_D]) {
						Direction[RIGHT] = false;
					}
				}
				if (Direction[LEFT] + Direction[RIGHT] + Direction[UP] + Direction[DOWN] == 0) {
					moveState = false;
				}
				else if (Direction[LEFT] + Direction[RIGHT] + Direction[UP] + Direction[DOWN] != 0) {
						moveState = true;
					 if (Direction[LEFT] && Direction[RIGHT]) {
						moveState = false;
					 }
					 if (Direction[UP] && Direction[DOWN]) {
						moveState = false;
					 }
				}
				
				correctDirection();
			}
		}
		//render
		if (moveState == true) {
			WaitForInput = false;
			if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0) {
				SDL_Delay(int(5 * MovementDelayRate));
				charSpriteDelayRate += 2;
			}
			else {
				SDL_Delay(5);
			}
			if (Direction[LEFT]) {
				mainBackGround.updateChunk(LEFT);
				_main_char_rect.y = 576;
				map1.updateMap(false);
				SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
				updateChar(charSpriteDelay);
				map1.updateMap(true);
				distance += speed;
				charCol.x-=speed;
			}
			if (Direction[RIGHT]) {
				mainBackGround.updateChunk(RIGHT);
				_main_char_rect.y = 704;
				map1.updateMap(false);
				SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
				updateChar(charSpriteDelay);
				map1.updateMap(true);
				distance += speed;
				charCol.x+=speed;
			}
			if (Direction[UP]) {
				mainBackGround.updateChunk(UP);
				_main_char_rect.y = 512;
				map1.updateMap(false);
				SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
				updateChar(charSpriteDelay);
				map1.updateMap(true);
				distance += speed;
				charCol.y-=speed;
			}
			if (Direction[DOWN])	 {
				mainBackGround.updateChunk(DOWN);
				_main_char_rect.y = 640;
				map1.updateMap(false);
				SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
				updateChar(charSpriteDelay);
				map1.updateMap(true);
				distance += speed;
				charCol.y+=speed;
			}
			if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0) {
				charSpriteDelayRate -= 2;
			}
		}
		else if (moveState == false) {
			if (WaitForInput == false) {
				
				mainBackGround.updateChunk(-1);
				_main_char_rect.x = 512;
				map1.updateMap(false);
				SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
				SDL_RenderCopy(renderer, _main_char, &_main_char_rect, &char_location_rect);
				map1.updateMap(true);
				WaitForInput = true;
			}
		}
		if (charSpriteDelay > 99) { 
			charSpriteDelay = 0;
		}
		
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(main_window);
		int delta = SDL_GetTicks() - start_loop;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
	}
}