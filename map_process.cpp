#include"map_process.h"

bool addObject(std::vector<object> &a,object target) {
	a.push_back(target);
	if (a.size()) { return true; }
	else {
		return false;
	}
}
void loadObjectList(std::vector<object> &a) {
	for (int i = 0; i < a.size(); i++) {
		a[i].setObjRenderCordinate();
		a[i].loadObject(renderer);
	}
}
object getObjectFromFile() {
	object a(0,0);
	return a;
}
