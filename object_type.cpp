#include"object_type.h"
bool object::loadTextureMedia() {
	bool success_state = true;
	object_texture = loadTexture("resources/Tree_SpriteSheet.png");
	if (object_texture == NULL) {
		printf("error loading object texture");
		success_state = false;
	}
	return success_state;
}
void object::loadObject(SDL_Rect a,SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, object_texture, &object_texture_rect, &a);
}
object::object() {
	object_cordinate.x = char_location_rect.x;
	object_cordinate.y = char_location_rect.y;
	object_cordinate.w = 82;
	object_cordinate.h = 128;
	object_texture_rect.x = 0;
	object_texture_rect.y = 0;
	object_texture_rect.w = 82;
	object_texture_rect.h = 128;
	loadTextureMedia();
}
	
	

