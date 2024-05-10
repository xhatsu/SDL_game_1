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
	if (SDL_PointInRect(&ar.ObjCol, &a.ObjPlaceHolder)) {
		return true;
	}
	return false;
}
void entityControl::listArrowHitCheck(int& hitNumber) {
	for (int i = 0; i < entityList.size(); i++) {
		for (int j = 0; j < arrowList.size(); j++) {
			if (arrowHitCheck(arrowList.at(j), entityList.at(i))) {
				entityList.erase(entityList.begin()+i);
				arrowList.erase(arrowList.begin() + j);
				hitNumber++;
			}
		}
	}
}
void entityControl::spawnRandomEntity(int eSpeed,bool isStarted,int colX, int colY,double spawnRate,int spawnRange) {
	if (isStarted == false) {
		return;
	}
	if (entityList.size() >= 128) {
		return;
	}
	int x = colX + rand() % spawnRange - spawnRange/2;
	int y = colY + rand() % spawnRange - spawnRange/2;
	double randomNum = rand() % 100;
	if (randomNum / 100 < spawnRate) {
		entity test = entity(x, y, rabbit, eMOVING,eSpeed);
		entityList.push_back(test);
	}
	
}