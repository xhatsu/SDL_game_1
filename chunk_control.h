#pragma once
#include"object_type.h"
#include"json.hpp"
#include<vector> 
class chunk
{
public:
	int CorX;
	int CorY;
	std::vector<object> chunkObjectList;
	chunk(int CorX,int CorY);
	
};

