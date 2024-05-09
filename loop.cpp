#include"loop.h"
//init processor
int getDirection() {
	for (int i = 0; i < 8; i++) {
		if (Direction[i]) {
			return i;
		}
	}
	return -1;
}
int aimDirection(int mouseX,int mouseY,double aimAngle) {
	//SDL_GetMouseState(&mouseX, &mouseY);
	if (aimAngle<=-30 && aimAngle>=-90) {
		if (mouseY >= 0) {return DOWN; }
		if (mouseY <= 0) {return UP; }
	}
	if (aimAngle >= 30 && aimAngle <= 90) {
		if (mouseY >= 0) { return DOWN; }
		if (mouseY <= 0) { return UP; }
	}
	if (aimAngle >= 0 && aimAngle < 30) {
		if (mouseX >= 0) { return RIGHT; }
		if (mouseX <= 0) { return LEFT; }
	}
	if (aimAngle <0 && aimAngle>-30) {
		if (mouseX >= 0) {  return RIGHT; }
		if (mouseX <= 0) {  return LEFT; }
	}
	return -1;
}
void loop() {
	int delay=5;
	entityControl mapEntityControl;
	mapProcess map1;
	characterHandle char1;
	GameControl game1;
	inGameMenu inGameMenu1(game1.level, static_cast<int>(game1.levelDuration.count()),game1.levelTarget);
	//test
	TimeCounter newCounter = TimeCounter(50);
	//action initialize
	int charState=MOVING;
	bool aiming = false;
	int aimTime = 0;
	double aimAngle = 0;
	int _aimDirection = -1;
	int aimCounter = 0;
	//map initialize
	int chunkIndexX=0, chunkIndexY=0;
	int chunkIndexX_new=0, chunkIndexY_new=0;
	map1.getChunkList("mapData.json");
	map1.arrangeChunk(chunkIndexX, chunkIndexY);
	map1.arrangeObject();
	map1.updateCheckList();
	//first time render
	mainBackGround.updateChunk(-1);
	map1.updateMap(false);
	char1.updateChar(MOVING, -1);
	mapEntityControl.loadEntityList();
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
					mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
					mouseX = mouseX - 640;
					mouseY = mouseY - 360;
					if (aiming == true) {
						aimAngle = angleCaluculate(mouseX, mouseY);
						char1.direction = _aimDirection = aimDirection(mouseX, mouseY, aimAngle);
						//printf("\naim angle: %f", aimAngle);
					}
				}
				if (event_input.type == SDL_MOUSEBUTTONDOWN) {
					//printf("\nevent");
					if (event_input.button.button == SDL_BUTTON_LEFT) {
						mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
						mouseX = mouseX - 640;
						mouseY = mouseY - 360;
						printf("\nx: %d", mouseX);
						printf("\ny: %d", mouseY);
						aimAngle = angleCaluculate(mouseX, mouseY);
						printf("\naim angle: %f ", aimAngle);
						char1.direction = _aimDirection = aimDirection(mouseX, mouseY, aimAngle);
						printf("\naim direction: %d ", _aimDirection);
						printf("\nclick");
						aiming = true;
						charState = ATTACKING;
						char1.resetAim();
						if (aimTime > 400) {
							aimCounter = 1;
							aiming = false;
							charState = MOVING;
							char1.resetAim();
							aimTime = 0;
						}
					}
				}
				if (event_input.type == SDL_MOUSEBUTTONUP) {
					//printf("\nevent");
					mouseButton = SDL_GetMouseState(&mouseX, &mouseY);
					if (aiming==true&&event_input.button.button ==SDL_BUTTON_LEFT) {
						mouseX = mouseX - 640;
						mouseY = mouseY - 360;
						aiming = false;
						//aimCounter = 0;
						printf("\nup");
						char1.resetAim();
						charState = MOVING;
						aimTime = 0;
					}
				}
				if (event_input.type == SDL_KEYDOWN) {
					//printf("\nevent");
					//reset
					if (key_state[SDL_SCANCODE_L]) {
						int x = charCol.x;
						int y = charCol.y;
						entity test = entity(x, y, rabbit,eMOVING);
						mapEntityControl.entityList.push_back(test);
					}
					if (key_state[SDL_SCANCODE_T]) {
						game1.startGame();
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
					 if (Direction[LEFT] && Direction[RIGHT]&&charState==MOVING) {
						moveState = false;
					 }
					 if (Direction[UP] && Direction[DOWN]&&charState==MOVING) {
						moveState = false;
					 }
				}
				
				correctDirection();
				//char1.direction = getDirection();
			}
		}
		//end input register
		//is aiming
		if (aiming == true&&charState==ATTACKING) {
			//printf("\naiming");
			//SDL_Delay(5);
			mainBackGround.updateChunk(-1);
			mapEntityControl.loadEntityList();
			map1.updateMap(false);
			char1.updateChar(charState, _aimDirection);	
			map1.updateMap(true);
			aimCounter++;
			if (aimCounter > 130) {
				printf("\nshooted");
				arrow newArrow=arrow(charCol.x,charCol.y-32,arrowType,-5,mouseX,mouseY,5,aimAngle);
				mapEntityControl.arrowList.push_back(newArrow);
				aimCounter = 0;
			}
		}
		else {
			//if aiming previously -> reset to normal state
			if (aimCounter != 0) {
				printf("\n %d", aimCounter);
				SDL_Delay(8);
				//printf("s");
				mainBackGround.updateChunk(-1);
				mapEntityControl.loadEntityList();
				map1.updateMap(false);
				char1.updateChar(charState, char1.direction);
				map1.updateMap(true);
				aimCounter = 0;
				char1.resetAim();
			}
			charState = MOVING;
		}
		//update chunk
		chunkIndexX_new = charCol.x / 720;
		if (charCol.x < 0) {
			chunkIndexX_new--; //fix chunk (0,0) error
		}
		chunkIndexY_new = charCol.y / 720;
		if (charCol.y < 0) {
			chunkIndexY_new--; //fix chunk (0,0) error
		}
		//check if moving to new chunk
		if (chunkIndexX != chunkIndexX_new || chunkIndexY != chunkIndexY_new) {
			chunkIndexX = chunkIndexX_new;
			chunkIndexY = chunkIndexY_new;
			printf("\n%d", chunkIndexX);
			printf("\n%d", chunkIndexY);
			map1.arrangeChunk(chunkIndexX, chunkIndexY);
			map1.arrangeObject();
		}
		//is moving
		if (moveState == true && charState == MOVING) {
			//printf("\nmoving");
			WaitForInput = false;
			if (Direction[LEFT]) {
				//printf("l");
				charCol.x -= speed;
				char1.direction = LEFT;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(char1.direction);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(charState, char1.direction);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.x += speed;
					mainBackGround.updateChunk(-1);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(STANDSTILL, char1.direction);
					map1.updateMap(true);
				}
			}
			if (Direction[RIGHT]) {
				//printf("r");
				charCol.x += speed;
				char1.direction = RIGHT;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					//printf("\n direction: %d", char1.direction);
					mainBackGround.updateChunk(char1.direction);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(charState, char1.direction);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.x -= speed;
					mainBackGround.updateChunk(-1);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(STANDSTILL, char1.direction);
					map1.updateMap(true);
				}

			}
			if (Direction[UP]) {
				//printf("u");
				charCol.y -= speed;
				char1.direction = UP;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(char1.direction);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(charState, char1.direction);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.y += speed;
					mainBackGround.updateChunk(-1);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(STANDSTILL, char1.direction);
					map1.updateMap(true);
				}
			}
			if (Direction[DOWN]) {
				//printf("do");
				charCol.y += speed;
				char1.direction = DOWN;
				if (!map1.mapCollisionControl.CollisionCheckListPLayer()) {
					mainBackGround.updateChunk(char1.direction);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(charState, char1.direction);
					map1.updateMap(true);
					distance += speed;
				}
				else {
					charCol.y -= speed;
					mainBackGround.updateChunk(-1);
					mapEntityControl.loadEntityList();
					map1.updateMap(false);
					char1.updateChar(STANDSTILL, char1.direction);
					map1.updateMap(true);
				}
			}
			//if ((Direction[LEFT] == true && Direction[RIGHT] == true) || (Direction[UP] == true && Direction[DOWN] == true)) {
			//	//charSpriteDelayRate -= 2;
			//	if (aiming == false) {
			//		charState = STANDSTILL;
			//	}
			//}
		}
		
		//not moving
		else if (moveState == false && aiming == false) {
			//printf("\n standing");
			if (true) {
				charState = STANDSTILL;
				mainBackGround.updateChunk(-1);
				mapEntityControl.loadEntityList();
				map1.updateMap(false);
				//printf("\n direction: %d",char1.direction);
				char1.updateChar(charState, char1.direction);
				map1.updateMap(true);
				WaitForInput = true;
			}
		}
		//SDL_Delay(25);
		if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0&&aiming==false) {
			SDL_Delay(int(delay * MovementDelayRate));
		}
		else {
			SDL_Delay(delay);
		}
		//update data
		map1.updateCheckList();
		mapEntityControl.listArrowHitCheck(aimAngle);
		game1.getTimeLeft();
		inGameMenu1.updateData(game1.level, static_cast<int>(game1.levelTimeLeft.count()), game1.targetKilled, game1.levelTarget);
		inGameMenu1.renderTopLeft();
		//render to screen
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(main_window);
		//fps cap
		int delta = SDL_GetTicks64() - start_loop;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
	}
}