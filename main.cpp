#include<SDL.h>
#include<stdio.h>
#include<string>
#include<SDL_image.h>
#include <utility>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int speed = 2;
int charSpriteDelay = 0;
int charSpriteDelayRate = 11;
double MovementDelayRate = 1.7;
//enumerations for easy array declare
enum DirectionEnum {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
	DIRECTION_TOTAL
};
bool Direction[DIRECTION_TOTAL];
void correctDirection() {
	if (Direction[UP] == true && Direction[LEFT] == true) {
		Direction[UP_LEFT] = true;
	}
	if (Direction[DOWN] == true && Direction[LEFT] == true) {
		Direction[DOWN_LEFT] = true;
	}
	if (Direction[UP] == true && Direction[RIGHT] == true) {
		Direction[UP_RIGHT] = true;
	}
	if (Direction[DOWN] == true && Direction[RIGHT] == true) {
		Direction[DOWN_RIGHT] = true;
	}


	if (Direction[UP] == false || Direction[LEFT] == false) {
		Direction[UP_LEFT] = false;
	}
	if (Direction[DOWN] == false || Direction[LEFT] == false) {
		Direction[DOWN_LEFT] = false;
	}
	if (Direction[UP] == false || Direction[RIGHT] == false) {
		Direction[UP_RIGHT] = false;
	}
	if (Direction[DOWN] == false || Direction[RIGHT] == false) {
		Direction[DOWN_RIGHT] = false;
	}
}
//image for each event
SDL_Texture* grass_background = NULL;
//main window define
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
SDL_Texture* _main_char = NULL;
SDL_Rect _main_char_rect;
SDL_Rect char_location_rect;
struct object {
	SDL_Rect object;
	void loadChunk(SDL_Rect a, SDL_Texture* object_Texture) {
		SDL_RenderCopy(renderer, object_Texture, NULL, &a);
	}
};
//load image func
SDL_Texture* loadTexture(std::string path) {
	//define optimized surface
	SDL_Texture* newTexture = NULL;

	//load surface from image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Error load image to surface, IMG_Error: \n", IMG_GetError());
	}
	else
	{
		//create texture from surface
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("cannot cannot create texture from surface", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
//INITIALIZE
bool init() {
	bool success_state = true;
	//initialize
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize. SDL_ERROR: ", SDL_GetError());
		success_state = false;
	}
	else {
		window = SDL_CreateWindow("SDL_game_1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created SDL_Error:\n", SDL_GetError());
			success_state = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("renderer cannot be created", SDL_GetError());
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success_state = false;
				}
			}

		}

	}
	return success_state;
}
//load resources
bool loadMedia() {
	bool success_state = true;
	//load all image first
	//default
	_main_char = loadTexture("resources/main_char_sprite_sheet.png");
	if (_main_char == NULL) {
		printf("error loading main char");
		success_state = false;
	}

	grass_background = loadTexture("resources/grass_background.png");
	if (grass_background == NULL) {
		printf("error loading background");
		success_state = false;
	}
	return success_state;
}
//close
void close_window() {
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	printf("closed window");
	SDL_Quit();
	IMG_Quit();
}
//main
void updateChar(int delay) {
	if (_main_char_rect.x == 0) {
		_main_char_rect.x = 64;
	}
	if (delay % charSpriteDelayRate == 0) {
		_main_char_rect.x = _main_char_rect.x + 64;
	}
	charSpriteDelay++;
	if (_main_char_rect.x >= 576) {
		_main_char_rect.x = 64;
	}
	SDL_RenderCopy(renderer, _main_char, &_main_char_rect, &char_location_rect);
}
struct Chunk {

	SDL_Rect background_rect;
	SDL_Rect background_rect_DOWN;
	SDL_Rect background_rect_UP;
	SDL_Rect background_rect_LEFT;
	SDL_Rect background_rect_RIGHT;
	SDL_Rect background_rect_UP_LEFT;
	SDL_Rect background_rect_DOWN_LEFT;
	SDL_Rect background_rect_UP_RIGHT;
	SDL_Rect background_rect_DOWN_RIGHT;

	void renderChunk() {
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_UP);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_DOWN);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_LEFT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_RIGHT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_DOWN_LEFT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_DOWN_RIGHT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_UP_LEFT);
		SDL_RenderCopy(renderer, grass_background, NULL, &background_rect_UP_RIGHT);
	}

	void stickChunk() {
		background_rect_UP.y = background_rect.y - 1440;
		background_rect_LEFT.y = background_rect.y;
		background_rect_RIGHT.y = background_rect.y;
		background_rect_UP_RIGHT.y = background_rect_UP.y;
		background_rect_UP_LEFT.y = background_rect_UP.y;
		background_rect_DOWN.y = background_rect.y + 1440;
		background_rect_DOWN_LEFT.y = background_rect_DOWN.y;
		background_rect_DOWN_RIGHT.y = background_rect_DOWN.y;

		background_rect_UP.x = background_rect.x;
		background_rect_LEFT.x = background_rect.x - 2560;
		background_rect_RIGHT.x = background_rect.x + 2560;
		background_rect_UP_RIGHT.x = background_rect_UP.x + 2560;
		background_rect_UP_LEFT.x = background_rect_UP.x - 2560;
		background_rect_DOWN.x = background_rect.x;
		background_rect_DOWN_LEFT.x = background_rect_DOWN.x - 2560;
		background_rect_DOWN_RIGHT.x = background_rect_DOWN.x + 2560;
	}

	void moveChunk(int direction) {
		switch (direction) {
		case DOWN:
			background_rect.y -= speed;
			background_rect_UP.y -= speed;
			background_rect_DOWN.y -= speed;
			background_rect_LEFT.y -= speed;
			background_rect_RIGHT.y -= speed;
			background_rect_UP_LEFT.y -= speed;
			background_rect_UP_RIGHT.y -= speed;
			background_rect_DOWN_RIGHT.y -= speed;
			background_rect_DOWN_LEFT.y -= speed;
			break;
		case UP:
			background_rect.y += speed;
			background_rect_UP.y += speed;
			background_rect_DOWN.y += speed;
			background_rect_LEFT.y += speed;
			background_rect_RIGHT.y += speed;
			background_rect_UP_LEFT.y += speed;
			background_rect_UP_RIGHT.y += speed;
			background_rect_DOWN_RIGHT.y += speed;
			background_rect_DOWN_LEFT.y += speed;
			break;
		case LEFT:
			background_rect.x += speed;
			background_rect_UP.x += speed;
			background_rect_DOWN.x += speed;
			background_rect_LEFT.x += speed;
			background_rect_RIGHT.x += speed;
			background_rect_UP_LEFT.x += speed;
			background_rect_UP_RIGHT.x += speed;
			background_rect_DOWN_RIGHT.x += speed;
			background_rect_DOWN_LEFT.x += speed;
			break;
		case RIGHT:
			background_rect.x -= speed;
			background_rect_UP.x -= speed;
			background_rect_DOWN.x -= speed;
			background_rect_LEFT.x -= speed;
			background_rect_RIGHT.x -= speed;
			background_rect_UP_LEFT.x -= speed;
			background_rect_UP_RIGHT.x -= speed;
			background_rect_DOWN_RIGHT.x -= speed;
			background_rect_DOWN_LEFT.x -= speed;
			break;
		default:
			break;
		}
	}

	void updateChunk(unsigned int state) {
		switch (state) {
		case UP:
			if (background_rect.y < -720) {
				background_rect.y = background_rect.y + 1440;
			}
			stickChunk();
			moveChunk(UP);
			renderChunk();
			if (background_rect.y >= SCREEN_HEIGHT) {
				background_rect.y -= 1440;
				background_rect_UP.y -= 1440;
				background_rect_DOWN.y -= 1440;
				background_rect_LEFT.y -= 1440;
				background_rect_RIGHT.y -= 1440;
				background_rect_UP_LEFT.y -= 1440;
				background_rect_UP_RIGHT.y -= 1440;
				background_rect_DOWN_RIGHT.y -= 1440;
				background_rect_DOWN_LEFT.y -= 1440;
			}
			break;
		case DOWN:
			if (background_rect.y > 0) {
				background_rect.y = background_rect.y - 1440;
			}
			stickChunk();
			moveChunk(DOWN);
			renderChunk();
			if (background_rect.y <= -1440) {
				background_rect.y += 1440;
				background_rect_UP.y += 1440;
				background_rect_DOWN.y += 1440;
				background_rect_LEFT.y += 1440;
				background_rect_RIGHT.y += 1440;
				background_rect_UP_LEFT.y += 1440;
				background_rect_UP_RIGHT.y += 1440;
				background_rect_DOWN_RIGHT.y += 1440;
				background_rect_DOWN_LEFT.y += 1440;
			}
			break;
		case LEFT:
			if (background_rect.x <= -1280) {
				background_rect.x = background_rect.x + 2560;
			}
			stickChunk();
			moveChunk(LEFT);
			renderChunk();
			if (background_rect.x >= 1280) {
				background_rect.x -= 2560;
				background_rect_UP.x -= 2560;
				background_rect_DOWN.x -= 2560;
				background_rect_LEFT.x -= 2560;
				background_rect_RIGHT.x -= 2560;
				background_rect_UP_LEFT.x -= 2560;
				background_rect_UP_RIGHT.x -= 2560;
				background_rect_DOWN_RIGHT.x -= 2560;
				background_rect_DOWN_LEFT.x -= 2560;
			}
			break;
		case RIGHT:
			if (background_rect.x >= 0) {
				background_rect.x = background_rect.x - 2560;
			}
			stickChunk();
			moveChunk(RIGHT);
			renderChunk();
			if (background_rect.x <= -2560) {
				background_rect.x += 2560;
				background_rect_UP.x += 2560;
				background_rect_DOWN.x += 2560;
				background_rect_LEFT.x += 2560;
				background_rect_RIGHT.x += 2560;
				background_rect_UP_LEFT.x += 2560;
				background_rect_UP_RIGHT.x += 2560;
				background_rect_DOWN_RIGHT.x += 2560;
				background_rect_DOWN_LEFT.x += 2560;
			}
			break;
		default:
			renderChunk();
			break;
		}

	}
};
int main(int argc, char* args[]) {
	if (init() == true) {
		if (loadMedia() == true) {
			int temp = 0;
			Chunk a;
			// rect initialize
			if (true) {
				a.background_rect.x = 0;
				a.background_rect.y = 0;
				a.background_rect.w = 2560;
				a.background_rect.h = 1440;

				a.background_rect_DOWN.x = 0;
				a.background_rect_DOWN.y = 1440;
				a.background_rect_DOWN.w = 2560;
				a.background_rect_DOWN.h = 1440;

				a.background_rect_UP.x = 0;
				a.background_rect_UP.y = -1440;
				a.background_rect_UP.w = 2560;
				a.background_rect_UP.h = 1440;

				a.background_rect_LEFT.x = -2560;
				a.background_rect_LEFT.y = 0;
				a.background_rect_LEFT.w = 2560;
				a.background_rect_LEFT.h = 1440;

				a.background_rect_RIGHT.x = 2560;
				a.background_rect_RIGHT.y = 0;
				a.background_rect_RIGHT.w = 2560;
				a.background_rect_RIGHT.h = 1440;

				a.background_rect_UP_LEFT.x = -2560;
				a.background_rect_UP_LEFT.y = -1440;
				a.background_rect_UP_LEFT.w = 2560;
				a.background_rect_UP_LEFT.h = 1440;

				a.background_rect_UP_RIGHT.x = 2560;
				a.background_rect_UP_RIGHT.y = -1440;
				a.background_rect_UP_RIGHT.w = 2560;
				a.background_rect_UP_RIGHT.h = 1440;

				a.background_rect_DOWN_RIGHT.x = 2560;
				a.background_rect_DOWN_RIGHT.y = 1440;
				a.background_rect_DOWN_RIGHT.w = 2560;
				a.background_rect_DOWN_RIGHT.h = 1440;

				a.background_rect_DOWN_LEFT.x = -2560;
				a.background_rect_DOWN_LEFT.y = 1440;
				a.background_rect_DOWN_LEFT.w = 2560;
				a.background_rect_DOWN_LEFT.h = 1440;
			}
			//moving state
			bool moveState = false;
			//update surface
			//event handler
			SDL_Event event_input;
			bool quit = false;
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			SDL_RenderCopy(renderer, grass_background, NULL, &a.background_rect);
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
			//test
			int distance = 0;
			object BGC1;
			BGC1.object.x = char_location_rect.x;
			BGC1.object.y = char_location_rect.y;
			BGC1.object.w = 320;
			BGC1.object.h = 320;
			//BGC1.loadChunk(BGC1.object, grass_background);
			//test
			SDL_RenderCopy(renderer, _main_char, &_main_char_rect, &char_location_rect);
			SDL_RenderPresent(renderer);
			int fps = 165;
			int desiredDelta = 1000 / fps;
			//start loop
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
						SDL_Delay(int(5*MovementDelayRate));
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
				printf("%d\n",distance);
				SDL_RenderPresent(renderer);
				SDL_UpdateWindowSurface(window);
				
				int delta = SDL_GetTicks() - start_loop;
				if (delta < desiredDelta) {
					SDL_Delay(desiredDelta - delta);
				}
			}

		}

		else {
			printf("Cannot load media");
		}
	}
	else { printf("Error initialize"); }
	close_window();
	return 0;
}

