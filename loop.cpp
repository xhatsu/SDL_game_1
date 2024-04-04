#include"loop.h"

void loop() {
	//action initialize
	int charState=MOVING;
	bool aiming = false;
	int aimTime = 0;
	//map initialize
	int chunkIndexX=0, chunkIndexY=0;
	int chunkIndexX_new=0, chunkIndexY_new=0;
	mapProcess map1;
	characterHandle char1;
	map1.getChunkList("mapData.json");
	map1.arrangeChunk(chunkIndexX, chunkIndexY);
	map1.arrangeObject();
	map1.updateCheckList();
	mainBackGround.updateChunk(-1);
	//first time render
	map1.updateMap(false);
	char1.updateChar(MOVING, -1);
	map1.updateMap(true);
	SDL_Delay(1000);
	//input handle
	bool WaitForInput = true;
	SDL_Event event_input;
	const Uint8* key_state = SDL_GetKeyboardState(NULL);
	int mouseX, mouseY;
	Uint32 mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
	int start_loop = SDL_GetTicks64();
	//start loop
	while (quit == false) {
		//polling event
		while (SDL_PollEvent(&event_input)) {
			if (event_input.type == SDL_QUIT) { quit = true; }
			//movement handle
			if (true) {
				if (event_input.type == SDL_MOUSEMOTION) {
					SDL_GetMouseState(&mouseX, &mouseY);
				}
				if (event_input.type == SDL_MOUSEBUTTONDOWN) {
					mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
					if (mouseButton == SDL_BUTTON(1) ) {aiming = true;}
					if (aimTime >= 1000) {
						aiming = false;
						aimTime = 0;
					}
				}
				if (event_input.type == SDL_MOUSEBUTTONUP) {
					if (aiming == true) {
						//char1.updateChar(ATTACKING,)
						aiming = false;
						aimTime = 0;
					}
				}
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
		if (aiming == true) {
			aimTime++;
			printf("\n%d", aimTime);
		}
		//update chunk
		chunkIndexX_new = charCol.x / 720;
		if (charCol.x < 0) {
			chunkIndexX_new--;
		}
		chunkIndexY_new = charCol.y / 720;
		if (charCol.y < 0) {
			chunkIndexY_new--;
		}
		if (chunkIndexX != chunkIndexX_new || chunkIndexY != chunkIndexY_new) {
			chunkIndexX = chunkIndexX_new;
			chunkIndexY = chunkIndexY_new;
			printf("\n%d", chunkIndexX);
			printf("\n%d", chunkIndexY);
			map1.arrangeChunk(chunkIndexX, chunkIndexY);
			map1.arrangeObject();
		}
		//is moving
		if (moveState == true&&aiming==false) {
			WaitForInput = false;
			if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0) {
				SDL_Delay(int(5 * MovementDelayRate));
			}
			else {
				SDL_Delay(5);
			}
			if (Direction[LEFT]) {
				charCol.x -= speed;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(LEFT);
					map1.updateMap(false);
					char1.updateChar(MOVING, LEFT);
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
					map1.updateMap(false);
					char1.updateChar(MOVING, RIGHT);
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
					map1.updateMap(false);
					char1.updateChar(MOVING, UP);
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
					map1.updateMap(false);
					char1.updateChar(MOVING, DOWN);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.y -= speed;
				}
			}
			if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0) {
				//charSpriteDelayRate -= 2;
			}
		}
		//not moving
		else if (moveState == false) {
			if (WaitForInput == false) {
				mainBackGround.updateChunk(-1);
				map1.updateMap(false);
				char1.updateChar(MOVING, -1);
				map1.updateMap(true);
				WaitForInput = true;
			}
		}
		map1.updateCheckList();
		//render to screen
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(main_window);
		//fps cap
		int delta = SDL_GetTicks() - start_loop;
		if (delta < desiredDelta) {
			//SDL_Delay(desiredDelta - delta);
		}
	}
}