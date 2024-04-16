#include "render_process.h"
json render_process::addData(json& a, int colX, int colY, int type) {
    a["type"] = type;
    a["texture"] = extraPath + typeList[type] + fileType;
    a["colX"] = colX;
    a["colY"] = colY;
    return a;
}
json render_process::generateObject(json& a, int type, int range_1_X, int range_1_Y, int sizeRange, int seed) {
    if (range_1_X >= 2147483000 || range_1_Y >= 2147483000) return false;
    int randomX = (rand()+1)*seed*2 * 120587;
    int randomY = (rand()+2)*seed/2 * 5825;
    if (randomX < 0) {
        randomX = -randomX;
    }
    if (randomY < 0) {
        randomY = -randomY;
    }
    int x = randomX % sizeRange + range_1_X;
    int y = randomY % sizeRange + range_1_Y;
    return addData(a, x, y, type);
}
void render_process::renderChunk(int CorX,int CorY,int number) {
    json chunk;
    json chunkObjectList = json::array();
    chunk["CorX"] = CorX;
    chunk["CorY"] = CorY;
    for (int i = 0; i < number; i++) {
        json object;
        //int type = rand() % 2;
        int type = tree;
        chunkObjectList.push_back(generateObject(object, type, CorX * sizeRange, CorY * sizeRange, sizeRange, seed));
    }
    chunk["chunkObjectList"] = chunkObjectList;
    chunkList.push_back(chunk);
}
render_process::render_process(int seed, int sizeRange, std::string path) {
    this->seed = seed;
    this->sizeRange = sizeRange;
    this->path = path;
}
void render_process::writeToFile() {
    std::ofstream jsonFileOut(path);
    outPutFile["chunkList"] = chunkList;
    jsonFileOut << std::setw(4) << outPutFile;
    jsonFileOut.close();
}
