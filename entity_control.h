#pragma once
#include"entity.h"
#include<vector>
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
};

