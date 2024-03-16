#include "render_process.h"
json render_process::addData(json& a, int colX, int colY, int type) {
    a["type"] = typeList[type];
    a["texture"] = extraPath + typeList[type] + fileType;
    a["colX"] = colX;
    a["colY"] = colY;
    return a;
}
bool render_process::generateObject(json& a, int type, int range_1_X, int range_1_Y, int sizeRange, int seed) {
    if (range_1_X >= 2147483000 || range_1_Y >= 2147483000) return false;
    int x = (rand()*seed+18735) % sizeRange + range_1_X;
    int y = (-rand()*seed+73458) % sizeRange + range_1_Y;
    objectList.push_back(addData(a, x, y, type));
    return true;
}
void render_process::render(int seed) {
    std::ofstream jsonFileOut(path);
    json file;
    for (int i = 0; i < listSize; i++) {
        json a;
        generateObject(a, tree, 0, 0, sizeRange, seed);
    }
    file["objectList"] = objectList;
    jsonFileOut << file;
    jsonFileOut.close();
}
render_process::render_process(int seed, int sizeRange, int listSize, std::string path) {
    this->seed = seed;
    this->sizeRange = sizeRange;
    this->listSize = listSize;
    this->path = path;
}