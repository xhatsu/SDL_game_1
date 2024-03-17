#include"object_type.h"
object::object(int x, int y) {
	ObjCol.x = x;
	ObjCol.y = y;
	printf("%d\n", ObjCol.x);
	printf("%d\n", ObjCol.y);
	objectRenderCordinate.w = 64;
	objectRenderCordinate.h = 64;
	object_texture_rect.x = 0;
	object_texture_rect.y = 0;
	object_texture_rect.w = 64;
	object_texture_rect.h = 64;
	if (!loadTextureMedia()) {
		printf("cannot load texture media");
	}
	setObjRenderCordinate();
}
bool object::loadTextureMedia() {
	bool success_state = true;
	object_texture = loadTexture("resources/Tree_SpriteSheet.png");
	if (object_texture == NULL) {
		printf("error loading object texture");
		success_state = false;
	}
	return success_state;
}
void object::loadObject(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, object_texture,NULL, &objectRenderCordinate);
}
void object::moveObject(int direction) {
	switch (direction) {
	case UP:
		ObjCol.y++;
		break;
	case DOWN:
		ObjCol.y--;
		break;
	case LEFT:
		ObjCol.x--;
		break;
	case RIGHT:
		ObjCol.x++;
		break;
	default:
		break;
	}

}
void object::setObjRenderCordinate() {
	int prefix_X = ObjCol.x - charCol.x;
	int prefix_Y = ObjCol.y - charCol.y;
	objectRenderCordinate.x = middle_screen.x + prefix_X;
	objectRenderCordinate.y = middle_screen.y + prefix_Y;
}

