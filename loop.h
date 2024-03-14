#pragma once
#include<SDL.h>
#include"Direction.h"
#include"background.h"
#include"object_type.h"
#include"char_handle.h"
extern void correctDirection();
extern void updateChar(int charSpriteDelay);
extern SDL_Window* main_window;
extern SDL_Rect _main_char_rect;
extern SDL_Rect char_location_rect;
extern SDL_Renderer* renderer;
extern SDL_Texture* grass_background;
extern SDL_Texture* _main_char;
extern SDL_Texture* tree_texture_1;
extern Chunk a;
extern bool Direction[8];
extern int speed;
extern int charSpriteDelay;
extern int charSpriteDelayRate;
extern double MovementDelayRate;
extern int temp;
extern bool moveState;
extern bool quit;

//test
extern int distance;
//end test
extern int fps;
extern int desiredDelta;
void loop();
