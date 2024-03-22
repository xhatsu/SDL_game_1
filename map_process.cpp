#pragma once
#include"map_process.h"
bool ColYSort(object a, object b) {
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
		std::sort(tempChunk.chunkObjectList.begin(),tempChunk.chunkObjectList.end(),ColYSort);
		chunkList.push_back(tempChunk);
	}
	mapFile.close();
}
void mapProcess::loadChunk(chunk currentChunk, bool isOver) {
	int objectNumber = currentChunk.chunkObjectList.size();
	if (!isOver) {
		for (int i = 0; i < objectNumber; i++) {
			if (currentChunk.chunkObjectList.at(i).ObjCol.y <= charCol.y)
			{	
				currentChunk.chunkObjectList.at(i).loadObject(renderer);
			}
		}
	}
	if (isOver) {
		for (int i = 0; i < objectNumber; i++) {
			if (currentChunk.chunkObjectList.at(i).ObjCol.y >= charCol.y)
			{	
				currentChunk.chunkObjectList.at(i).loadObject(renderer);
			}
		}
	}
}
void mapProcess::updateMap(bool isOver) {
	int size = activeChunk.size();
	for (int i = 0; i < size; i++) {
		loadChunk(activeChunk.at(i),isOver);
	}
}