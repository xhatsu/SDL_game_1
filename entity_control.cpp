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
}
bool entityControl::arrowHitCheck(double aimAngle,entity a) {
	double entityAngle = angleCaluculate(a.objectRenderCordinate.x, a.objectRenderCordinate.y);
	if (abs(entityAngle-aimAngle)<5) {
		return true;
	}
	else {
		return false;
	}
	return false;
}