#include"loop.h"
void loop() {
	//map initialize
	int chunkIndexX=0, chunkIndexY=0;
	int chunkIndexX_new=0, chunkIndexY_new=0;
	mapProcess map1;
	map1.getChunkList("mapData.json");
	map1.activeChunk.clear();
	for (int i = 0; i < map1.chunkList.size(); i++) {
		if (map1.chunkList.at(i).CorX == chunkIndexX && map1.chunkList.at(i).CorY == chunkIndexY) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX + 1 && map1.chunkList.at(i).CorY == chunkIndexY + 1) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX - 1 && map1.chunkList.at(i).CorY == chunkIndexY - 1) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX + 1 && map1.chunkList.at(i).CorY == chunkIndexY) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX && map1.chunkList.at(i).CorY == chunkIndexY + 1) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX - 1 && map1.chunkList.at(i).CorY == chunkIndexY) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX - 1 && map1.chunkList.at(i).CorY == chunkIndexY + 1) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX && map1.chunkList.at(i).CorY == chunkIndexY - 1) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
		if (map1.chunkList.at(i).CorX == chunkIndexX + 1 && map1.chunkList.at(i).CorY == chunkIndexY - 1) {
			map1.activeChunk.push_back(map1.chunkList.at(i));
		}
	}
	map1.mapCollisionControl.checkList.clear();
	for (int i = 0; i < map1.activeChunk.size(); i++) {
		if (map1.activeChunk.at(i).CorX == chunkIndexX && map1.activeChunk.at(i).CorY == chunkIndexY) {
			for (int j = 0; j < map1.activeChunk.at(i).chunkObjectList.size(); j++) {
				map1.mapCollisionControl.checkList.push_back(map1.activeChunk.at(i).chunkObjectList.at(j));
			}
		}
	}
	//shadow(temp)
	SDL_Rect shadow_rect;
	shadow_rect.w = char_location_rect.w;
	shadow_rect.h = char_location_rect.h;
	shadow_rect.x = char_location_rect.x;
	shadow_rect.y = char_location_rect.y + 5;
	mainBackGround.updateChunk(-1);
	_main_char_rect.x = 512;
	//first time render
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
						printf("\n%d", charCol.x);
						printf("\n%d", charCol.y);
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
		//is moving
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
				charCol.x -= speed;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(LEFT);
					_main_char_rect.y = 576;
					map1.updateMap(false);
					SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
					updateChar(charSpriteDelay);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.x += speed;
				}
			}
			if (Direction[RIGHT]) {
				charCol.x += speed;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(RIGHT);
					_main_char_rect.y = 704;
					map1.updateMap(false);
					SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
					updateChar(charSpriteDelay);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.x -= speed;
				}

			}
			if (Direction[UP]) {
				charCol.y -= speed;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(UP);
					_main_char_rect.y = 512;
					map1.updateMap(false);
					SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
					updateChar(charSpriteDelay);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.y += speed;
				}
			}
			if (Direction[DOWN]) {
				charCol.y += speed;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(DOWN);
					_main_char_rect.y = 640;
					map1.updateMap(false);
					SDL_RenderCopy(renderer, mainChar_shadow, &mainChar_shadow_Rect, &shadow_rect);
					updateChar(charSpriteDelay);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.y -= speed;
				}
			}
			if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0) {
				charSpriteDelayRate -= 2;
			}
		}
		//not moving
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
		//sprite delay
		if (charSpriteDelay > 99) { 
			charSpriteDelay = 0;
		}
		//update current chunk
		chunkIndexX_new = charCol.x / 1280;
		if (charCol.x < 0) {
			chunkIndexX_new--;
		}
		chunkIndexY_new = charCol.y / 1280;
		if (charCol.y < 0) {
			chunkIndexY_new--;
		}
		if (chunkIndexX != chunkIndexX_new || chunkIndexY != chunkIndexY_new) {
			chunkIndexX = chunkIndexX_new;
			chunkIndexY = chunkIndexY_new;
			printf("\n%d", chunkIndexX);
			printf("\n%d", chunkIndexY);
			map1.activeChunk.clear();
			for (int i = 0; i < map1.chunkList.size(); i++) {
				if (map1.chunkList.at(i).CorX == chunkIndexX     && map1.chunkList.at(i).CorY == chunkIndexY     ) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX + 1 && map1.chunkList.at(i).CorY == chunkIndexY + 1 ) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX - 1 && map1.chunkList.at(i).CorY == chunkIndexY - 1 ) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX + 1 && map1.chunkList.at(i).CorY == chunkIndexY    ) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX     && map1.chunkList.at(i).CorY == chunkIndexY + 1 ) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX - 1 && map1.chunkList.at(i).CorY == chunkIndexY     ) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX  -1   && map1.chunkList.at(i).CorY == chunkIndexY   +1 ) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX && map1.chunkList.at(i).CorY == chunkIndexY-1) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
				if (map1.chunkList.at(i).CorX == chunkIndexX +1&& map1.chunkList.at(i).CorY == chunkIndexY-1) {
					map1.activeChunk.push_back(map1.chunkList.at(i));
				}
			}
			map1.mapCollisionControl.checkList.clear();
			for (int i = 0; i < map1.activeChunk.size(); i++) {
				if (map1.activeChunk.at(i).CorX == chunkIndexX && map1.activeChunk.at(i).CorY == chunkIndexY) {
					for (int j = 0; j < map1.activeChunk.at(i).chunkObjectList.size(); j++) {
						map1.mapCollisionControl.checkList.push_back(map1.activeChunk.at(i).chunkObjectList.at(j));
					}
				}
			}
		}
		//render to screen
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(main_window);
		//fps cap
		int delta = SDL_GetTicks() - start_loop;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
	}
}