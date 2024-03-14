#pragma once
#include"object_type.h"
#include<vector>
extern SDL_Renderer* renderer;
extern std::vector<object> objectListTop;
extern std::vector<object> objectListBottom;
object getObjectFromFile();
bool addObject(std::vector<object> &a,object target);
void loadObjectList(std::vector<object>& a);


