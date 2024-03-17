#pragma once
#include<SDL.h>
extern SDL_Rect _main_char_rect;
extern SDL_Rect char_location_rect;
extern SDL_Texture* _main_char;
extern SDL_Renderer* renderer;
extern SDL_Texture* mainChar_shadow;
extern int charSpriteDelayRate;
extern int charSpriteDelay;
extern SDL_Rect mainChar_shadow_Rect;
void updateChar(int delay);