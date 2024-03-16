#pragma once
#include"object_type.h"
#include"json.hpp"
#include<fstream>
#include<vector>
using namespace nlohmann::json_abi_v3_11_3;
extern SDL_Renderer* renderer;
extern std::vector<object> objectListTop;
extern std::vector<object> objectListBottom;
class mapProcess {
public:
	void getObjectListFromFile(std::vector<object> &a);
	bool addObject(std::vector<object>& a, object target);
	void loadObjectList(std::vector<object>& a);
};
