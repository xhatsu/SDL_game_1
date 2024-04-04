#pragma once
#include<SDL.h>
#include"Direction.h"
#include"background.h"
#include"map_process.h"
#include"character_handle.h"
#include<algorithm>
extern void correctDirection();
extern void updateChar(int charSpriteDelay);
extern SDL_Window* main_window;
extern SDL_Renderer* renderer;
extern SDL_Texture* grass_background;
extern SDL_Texture* tree_texture_1;
extern backGround mainBackGround;
extern bool Direction[8];
extern int speed;
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
