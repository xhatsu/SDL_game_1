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
	setObjRenderCordinate();
	switch (type)
	{
	case tree:
		ObjPlaceHolder.w = 32;
		ObjPlaceHolder.h = 32;
		ObjPlaceHolder.x = ObjCol.x - ObjPlaceHolder.w/2;
		ObjPlaceHolder.y = ObjCol.y - ObjPlaceHolder.h/2;
	default:
		break;
	}
}
void object::loadObject(SDL_Renderer* renderer) {
	setObjRenderCordinate();
	switch (type)
	{
	case tree:
		SDL_RenderCopy(renderer, treeTexture, NULL, &objectRenderCordinate);
	default:
		break;
	}
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

