#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"json.hpp"
using namespace nlohmann::json_abi_v3_11_3;
enum objectData {
    tree = 0,
    rock,
    grass
};
class render_process
{
public:
    render_process(int seed,int sizeRange,int listSize,std::string path);
    int seed;
    int sizeRange;
    int listSize ;
    std::string path;
    std::string typeList[3] = { "tree","rock","grass" };
    std::string extraPath = "resources/";
    std::string fileType = ".png";
    std::vector<json> objectList;
    json addData(json& a, int colX, int colY, int type);
    bool generateObject(json& a, int type, int range_1_X, int range_1_Y, int sizeRange, int seed);
    void render(int seed);
};

