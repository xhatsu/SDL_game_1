#include"map_process.h"

bool mapProcess::addObject(std::vector<object> &a,object target) {
	a.push_back(target);
	if (a.size()) { return true; }
	else {
		return false;
	}
}
void mapProcess::loadObjectList(std::vector<object> &a) {
	for (int i = 0; i < a.size(); i++) {
		a[i].setObjRenderCordinate();
		a[i].loadObject(renderer);
	}
}
void mapProcess::getObjectListFromFile(std::vector<object>& a) {
	json file = json::object();
	json ObjList = json::array();
	std::ifstream jsonFileIn("mapData.json");
	jsonFileIn >> file;
	jsonFileIn.close();
	ObjList = file["objectList"];
	int listSize = ObjList.size();
	for (int i = 0; i < listSize; i++) {
		int colX = ObjList.at(i)["colX"];
		int colY = ObjList.at(i)["colY"];
		object temp(colX, colY);
		addObject(a, temp);
	}
}

