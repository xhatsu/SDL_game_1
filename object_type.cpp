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
	
	

