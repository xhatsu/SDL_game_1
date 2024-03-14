#include"loop.h"
void loop() {
	SDL_Event event_input;
	bool quit = false;
	while (quit == false) {
		const Uint8* key_state = SDL_GetKeyboardState(NULL);
		int start_loop = SDL_GetTicks64();
		while (SDL_PollEvent(&event_input)) {
			if (event_input.type == SDL_QUIT) { quit = true; }
			if (true) {
				//movement handle	
				if (event_input.type == SDL_KEYDOWN) {
					if (key_state[SDL_SCANCODE_L]) {
						distance = 0;
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
				}
				correctDirection();
			}
		}
		if (moveState == true) {
			if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0) {
				SDL_Delay(int(5 * MovementDelayRate));
				charSpriteDelayRate += 2;
			}
			else {
				SDL_Delay(5);
			}
			if (Direction[LEFT]) {
				a.updateChunk(LEFT);
				_main_char_rect.y = 576;
				updateChar(charSpriteDelay);
				distance += speed;
			}
			if (Direction[RIGHT]) {
				a.updateChunk(RIGHT);
				_main_char_rect.y = 704;
				updateChar(charSpriteDelay);
				distance += speed;
			}
			if (Direction[UP]) {
				a.updateChunk(UP);
				_main_char_rect.y = 512;
				updateChar(charSpriteDelay);
				distance += speed;
			}
			if (Direction[DOWN]) {
				a.updateChunk(DOWN);
				_main_char_rect.y = 640;
				updateChar(charSpriteDelay);
				distance += speed;
			}
			if (Direction[UP_LEFT] + Direction[UP_RIGHT] + Direction[DOWN_LEFT] + Direction[DOWN_RIGHT] != 0) {
				charSpriteDelayRate -= 2;
			}
		}
		else if (moveState == false) {

		}
		if (charSpriteDelay > 99) {
			charSpriteDelay = 0;
		}
		printf("%d\n", distance);
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(main_window);
		int delta = SDL_GetTicks() - start_loop;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
	}
}