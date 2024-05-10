#pragma once
#include"entity.h"
#include"arrow.h"
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
	std::vector<arrow> arrowList;
	entityControl();
	void addEntity(entity a);
	void loadEntityList();
	bool arrowHitCheck(arrow ar, entity a);
	void listArrowHitCheck(int& hitNumber);
	void spawnRandomEntity(int eSpeed,bool isStarted,int colX, int colY,double spawnRate,int spawnRange);
};

