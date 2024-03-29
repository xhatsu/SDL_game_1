#pragma once
#include"chunk_control.h"
#include"json.hpp"
#include<fstream>
#include<vector>
#include<string>
using namespace nlohmann::json_abi_v3_11_3;
extern SDL_Renderer* renderer;
class mapProcess {
public:
	std::vector<SDL_Texture*> textureList;
	class Collision {
		public:
			bool CollisionCheckPlayer(object a);
			bool CollisionCheckListPLayer();
			std::vector<object> checkList;
	};
	Collision mapCollisionControl;
	std::vector<chunk> chunkList;
	std::vector<chunk> activeChunk;
	void getChunkList(std::string path);
	void loadChunk(chunk currentChunk,bool isOver);
	void updateMap(bool isOver);
	//void getObjectListFromFile(std::vector<object> &a);
	//void addObject(std::vector<object>& a, object target);
	//void loadObjectList(std::vector<object>& a);
	mapProcess();
};
