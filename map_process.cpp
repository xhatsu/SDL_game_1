#pragma once
#include"map_process.h"
bool ColYSort(object a, object b) {
	return (a.objectRenderCordinate.y < b.objectRenderCordinate.y);
}
bool ColXSort(object a, object b) {
	return (a.objectRenderCordinate.y < b.objectRenderCordinate.y);
}
void mapProcess::getChunkList(std::string path) {
	std::ifstream mapFile(path);
	json fileObject = json::object();
	mapFile >> fileObject;
	json chunkListJson=json::array();
	chunkListJson = fileObject["chunkList"];
	int numberOfChunk = chunkListJson.size();
	for (int i = 0; i < numberOfChunk; i++) {
		json chunkJson = json::array();
		chunkJson = chunkListJson.at(i);
		chunk tempChunk(chunkJson["CorX"],chunkJson["CorY"]);
		json chunkObjectListJson = json::array();
		chunkObjectListJson = chunkJson["chunkObjectList"];
		int objectListSize = chunkObjectListJson.size();
		for (int i = 0; i < objectListSize; i++) {
			object tempObj(chunkObjectListJson.at(i)["colX"], chunkObjectListJson.at(i)["colY"], chunkObjectListJson.at(i)["type"]);
			tempChunk.chunkObjectList.push_back(tempObj);
		}
		//std::sort(tempChunk.chunkObjectList.begin(),tempChunk.chunkObjectList.end(),ColYSort);
		chunkList.push_back(tempChunk);
	}
	mapFile.close();
}
void mapProcess::loadObjectList(bool isOver) {
	int objectNumber = objectList.size();
	if (!isOver) {
		for (int i = 0; i < objectNumber; i++) {
			if (objectList.at(i).ObjCol.y <= charCol.y)
			{	
				objectList.at(i).loadObject(renderer);
			}
		}
	}
	if (isOver) {
		for (int i = 0; i < objectNumber; i++) {
			if (objectList.at(i).ObjCol.y >= charCol.y)
			{	
				objectList.at(i).loadObject(renderer);
			}
		}
	}
}
void mapProcess::updateMap(bool isOver) {
	loadObjectList(isOver);
}
bool mapProcess::Collision::CollisionCheckPlayer(object a) {
	if ((charCol.x + 8 >= a.ObjCol.x - a.ObjPlaceHolder.w/2)&&charCol.x-8<=a.ObjCol.x+a.ObjPlaceHolder.w/2) {
		if ((charCol.y + 8 >= a.ObjCol.y - a.ObjPlaceHolder.h / 2)&&(charCol.y -8 <= a.ObjCol.y + a.ObjPlaceHolder.h / 2)) {
			//printf("\n blocked");
			return true;
		}
	}
	return false;
}
bool mapProcess::Collision::CollisionCheckListPLayer() {
	int size = checkList.size();
	for (int i = 0; i < size; i++) {
		if (CollisionCheckPlayer(checkList.at(i))) {
			return true;
		}
	}
	return false;
}
void mapProcess::arrangeObject() {
	objectList.clear();
	for (int i = 0; i < activeChunk.size(); i++) {
		for (int j = 0; j < activeChunk.at(i).chunkObjectList.size(); j++) {
			objectList.push_back(activeChunk.at(i).chunkObjectList.at(j));
		}
	}
	std::sort(objectList.begin(), objectList.end(), ColYSort);
	std::sort(objectList.begin(), objectList.end(), ColXSort);
}
void mapProcess::arrangeChunk(int chunkIndexX,int chunkIndexY) {
	activeChunk.clear();
	for (int i = 0; i < chunkList.size(); i++) {
		if (chunkList.at(i).CorX == chunkIndexX + 1 && chunkList.at(i).CorY == chunkIndexY) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX + 1 && chunkList.at(i).CorY == chunkIndexY - 1) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX + 1 && chunkList.at(i).CorY == chunkIndexY + 1) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX && chunkList.at(i).CorY == chunkIndexY - 1) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX && chunkList.at(i).CorY == chunkIndexY + 1) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX && chunkList.at(i).CorY == chunkIndexY) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX - 1 && chunkList.at(i).CorY == chunkIndexY - 1) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX - 1 && chunkList.at(i).CorY == chunkIndexY) {
			activeChunk.push_back(chunkList.at(i));
		}
		if (chunkList.at(i).CorX == chunkIndexX - 1 && chunkList.at(i).CorY == chunkIndexY + 1) {
			activeChunk.push_back(chunkList.at(i));
		}
	}
}
void mapProcess::updateCheckList() {
	mapCollisionControl.checkList.clear();
	int size = objectList.size();
	for (int i = 0; i < size; i++) {
		if (abs(charCol.x - objectList.at(i).ObjCol.x) <= 256) {
			mapCollisionControl.checkList.push_back(objectList.at(i));
		}
	}
}
mapProcess::mapProcess() {
	printf("\nmmap created\n");
}
mapProcess::~mapProcess() {
	chunkList.clear();
	activeChunk.clear();
	std::vector<chunk>().swap(chunkList);
	std::vector<chunk>().swap(activeChunk);
	printf("map deallocated");
}