#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"json.hpp"
#include"ObjectTypeEnum.h"
using namespace nlohmann::json_abi_v3_11_3;
class render_process
{
public:
    render_process(int seed,int sizeRange,std::string path);
    class chunk {
        int CorX;
        int CorY;
        std::vector<json> chunkObjectList;
    };
    int seed;
    int sizeRange;
    std::string path;
    std::string typeList[3] = { "tree","rock","grass" };
    std::string extraPath = "resources/";
    std::string fileType = ".png";
    json outPutFile;
    json chunkList = json::array();
    json addData(json& a, int colX, int colY, int type);
    json generateObject(json& a, int type, int range_1_X, int range_1_Y, int sizeRange, int seed);
    void renderChunk(int range_1_X,int range_1_Y,int number);
    void writeToFile();
};

