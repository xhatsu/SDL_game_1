#include"object_type.h"
object::object(int x, int y,int type) {
	ObjCol.x = x;
	ObjCol.y = y;
	this->type = type;
	object_texture_rect.w = 128;
	object_texture_rect.h = 192;
	objectRenderCordinate.w = object_texture_rect.w;
	objectRenderCordinate.h = object_texture_rect.h;
	object_texture_rect.x = 0;
	object_texture_rect.y = 0;
	if (!loadTextureMedia()) {
		printf("cannot load texture media");
	}
	setObjRenderCordinate();
}
bool object::loadTextureMedia() {
	bool success_state = true;
	object_texture = loadTexture("resources/Tree.png");
	if (object_texture == NULL) {
		printf("error loading object texture");
		success_state = false;
	}
	return success_state;
}
void object::loadObject(SDL_Renderer* renderer) {
	setObjRenderCordinate();
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
	if (type == tree) {
		int prefix_X = ObjCol.x - charCol.x;
		int prefix_Y = ObjCol.y - charCol.y;
		objectRenderCordinate.x = middle_screen.x + prefix_X - object_texture_rect.w/2;
		objectRenderCordinate.y = middle_screen.y + prefix_Y - object_texture_rect.h+16;
	}
}

