#include "entity.h"
#include"object_type.h"
entity::entity(int x=0, int y=0, int type=rabbit,int state = eSTANDING,int speed=1) {
	ObjCol.x = x;
	ObjCol.y = y;
	this->type = type;
	textureCounter = 0;
	direction = rand() % 3;
	this->speed = speed;
	switch (type)
	{
	case rabbit:
		ObjPlaceHolder.w = 32;
		ObjPlaceHolder.h = 32;
		ObjPlaceHolder.x = ObjCol.x;
		ObjPlaceHolder.y = ObjCol.y;
		objectDefaultTextureRect.x = 0;
		objectDefaultTextureRect.y = 0;
		objectDefaultTextureRect.w = 36;
		objectDefaultTextureRect.h = 36;
		break;
	default:
		break;
	}
	objectRenderCordinate.w = objectDefaultTextureRect.w;
	objectRenderCordinate.h = objectDefaultTextureRect.h;
	setObjRenderCordinate();

}

SDL_Rect entity::getTextureRectPoll() {
	SDL_Rect temp = objectTexturePollList.at(objectTexturePollList.size() - 1);
	objectTexturePollList.pop_back();
	return temp;
}
void entity::updateEntity() {
		switch (state) {
		case eSTART:
			if (state == eSTART) {
				int padding = 0;
				switch (direction) {
				case LEFT:
					padding = 864;
					break;
				case RIGHT:
					padding = 576;
					break;
				case DOWN:
					padding = 288;
					break;
				case UP:
					padding = 0;
					break;
				default:
					break;
				}
				objectTexturePollList.clear();
				for (int i = 0; i < 8; i++) {
					SDL_Rect texture_rect=objectDefaultTextureRect;
					texture_rect.x = i*36 + padding;
					//printf("\n%d", texture_rect.x);
					//printf("\n%d", texture_rect.y);
					//printf("\n%d", texture_rect.w);
					//printf("\n%d", texture_rect.h);
					objectTexturePollList.push_back(texture_rect);
				}
				state = eMOVING;
			}
			break;
		case eMOVING:
			if (delayAction % 12 == 0) {
				if (!objectTexturePollList.empty()) {
					object_texture_rect = getTextureRectPoll();
					
				}
			}
			if (delayAction % 3 == 0) {
				moveEntity(direction);
				/*switch (direction) {
				case LEFT:
					if (delayAction)
					break;
				default:
					break;
				};*/
				//moveEntity(delayAction % 4);
			}
			//printf("\n%d", int(objectTexturePollList.size()));
			if (objectTexturePollList.size() < 1) {
				state = eSTANDING;
				delayAction = 0;
			}	
			break;
		case eSTANDING:
			break;
		default:
			break;
		}
	ObjPlaceHolder.x = ObjCol.x-ObjPlaceHolder.w/2;
	ObjPlaceHolder.y = ObjCol.y-ObjPlaceHolder.h-ObjPlaceHolder.h/2;
	loadEntity(renderer);
	delayAction++;
	if (delayAction > 500) {
		delayAction = 0;
	}
	if (delayAction%100==1) {
		int temp = rand() % 3;
		if (temp == 2) {
			delayAction = 0;
			state = eSTART;
			direction = rand() % 4;
		}
	}
}
void entity::loadEntity(SDL_Renderer* renderer) {
	setObjRenderCordinate();
	switch (type)
	{
	case rabbit:
		//printf("\nsize: %d", int(objectTexturePollList.size()));
		//SDL_RenderDrawRect(renderer, &objectRenderCordinate);
		SDL_RenderCopy(renderer, rabbitTexture, &object_texture_rect, &objectRenderCordinate);
		break;
	default:
		break;
	}
}
void entity::moveEntity(int direction) {
	switch (direction) {
	case UP:
		ObjCol.y+=speed;
		break;
	case DOWN:
		ObjCol.y-=speed;
		break;
	case LEFT:
		ObjCol.x-=speed;
		break;
	case RIGHT:
		ObjCol.x+=speed;
		break;
	default:
		break;
	}
}
void entity::setObjRenderCordinate() {
	if (type == rabbit) {
		int prefix_X = ObjCol.x - charCol.x;
		int prefix_Y = ObjCol.y - charCol.y;
		objectRenderCordinate.x = middle_screen.x + prefix_X - object_texture_rect.w / 2;
		objectRenderCordinate.y = middle_screen.y + prefix_Y - object_texture_rect.h / 2;
	}
	if (type == arrowType) {
		int prefix_X = ObjCol.x - charCol.x;
		int prefix_Y = ObjCol.y - charCol.y+32;
		objectRenderCordinate.x = middle_screen.x + prefix_X;
		objectRenderCordinate.y = middle_screen.y + prefix_Y;
	}
}

