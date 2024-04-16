#include"object_type.h"
object::object(int x, int y,int type) {
	ObjCol.x = x;
	ObjCol.y = y;
	this->type = type;
	switch (type)
	{
	case tree:
		ObjPlaceHolder.w = 32;
		ObjPlaceHolder.h = 32;
		ObjPlaceHolder.x = ObjCol.x - ObjPlaceHolder.w / 2;
		ObjPlaceHolder.y = ObjCol.y - ObjPlaceHolder.h / 2;
		object_texture_rect.w = 128;
		object_texture_rect.h = 192;
		break;
	case box:
		ObjPlaceHolder.w = 59;
		ObjPlaceHolder.h = 59;
		ObjPlaceHolder.x = ObjCol.x;
		ObjPlaceHolder.y = ObjCol.y;
		object_texture_rect.w = 59;
		object_texture_rect.h = 59;
		break;
	default:
		break;
	}
	objectRenderCordinate.w = object_texture_rect.w;
	objectRenderCordinate.h = object_texture_rect.h;
	object_texture_rect.x = 0;
	object_texture_rect.y = 0;
	setObjRenderCordinate();
	
}
void object::loadObject(SDL_Renderer* renderer) {
	setObjRenderCordinate();
	switch (type)
	{
	case box:
		SDL_RenderCopy(renderer, boxTexture, NULL, &objectRenderCordinate);
		break;
	case tree:
		SDL_RenderCopy(renderer, treeTexture, NULL, &objectRenderCordinate);
		break;
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
	if (type == box) {
		int prefix_X = ObjCol.x - charCol.x;
		int prefix_Y = ObjCol.y - charCol.y;
		objectRenderCordinate.x = middle_screen.x + prefix_X - object_texture_rect.w / 2;
		objectRenderCordinate.y = middle_screen.y + prefix_Y - object_texture_rect.h / 2-16;
	}
}

