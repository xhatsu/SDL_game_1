#include "entity_control.h"
entityControl::entityControl() {
	printf("\nentity process loaded");
}
void entityControl::addEntity(entity a) {
	entityList.push_back(a);
}
void entityControl::loadEntityList() {
	for (int i = 0; i < entityList.size(); i++) {
		entityList.at(i).updateEntity();
	}
	for (int i = 0; i < arrowList.size(); i++) {
		arrowList.at(i).updateArrow();
		if (arrowList.at(i).objectRenderCordinate.x > 1280 || arrowList.at(i).objectRenderCordinate.x < 0 || arrowList.at(i).objectRenderCordinate.y>720 || arrowList.at(i).objectRenderCordinate.y < 0) {
			arrowList.erase(arrowList.begin() + i);
		}
	}
}
bool entityControl::arrowHitCheck(arrow ar,entity a) {
	if ((ar.ObjCol.x + 8 >= a.ObjCol.x - a.ObjPlaceHolder.w / 2) && ar.ObjCol.x - 8 <= a.ObjCol.x + a.ObjPlaceHolder.w / 2) {
		if ((ar.ObjCol.y + 8 >= a.ObjCol.y - a.ObjPlaceHolder.h / 2) && (ar.ObjCol.y - 8 <= a.ObjCol.y + a.ObjPlaceHolder.h / 2)) {
			//printf("\n blocked");
			return true;
		}
	}
	return false;
}
void entityControl::listArrowHitCheck(double aimAngle) {
	for (int i = 0; i < entityList.size(); i++) {
		for (int j = 0; j < arrowList.size(); j++) {
			if (arrowHitCheck(arrowList.at(j), entityList.at(i))) {
				entityList.erase(entityList.begin()+i);
				arrowList.erase(arrowList.begin() + j);
			}
		}
	}
}