#pragma once
#include"entity.h"
#include<vector>
extern double angleCaluculate(int corX, int corY);
extern SDL_Renderer* renderer;
class entityControl
{
public:
	/*class bullettrail {
		int x;
		int y;
	};*/
	std::vector<entity> entityList;
	entityControl();
	void addEntity(entity a);
	void loadEntityList();
	bool arrowHitCheck(double aimAngle,entity a);
	void listArrowHitCheck(double aimAngle) {
		for (int i = 0; i < entityList.size(); i++) {
			if (arrowHitCheck(aimAngle, entityList.at(i))) {
				entityList.erase(entityList.begin()+i);
				return;
			}
		}
	}
};

