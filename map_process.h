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
	std::vector<object> objectList;
	void arrangeChunk(int chunkIndexX, int chunkIndexY);
	void arrangeObject();
	void getChunkList(std::string path);
	void loadObjectList(bool isOver);
	void updateMap(bool isOver);
	void updateCheckList();
	mapProcess();
	~mapProcess();
};
