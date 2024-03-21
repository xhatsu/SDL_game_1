#pragma once
#include"map_process.h"
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
		chunkList.push_back(tempChunk);
	}
	mapFile.close();
}