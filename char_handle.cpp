#include "char_handle.h"
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