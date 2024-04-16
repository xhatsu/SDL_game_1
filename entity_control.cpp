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