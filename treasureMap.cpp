#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
    : base(baseim), maze(mazeim), start(s) {}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){  
    RGBAPixel* pixel = im.getPixel(loc.first, loc.second);
    pixel->r /= 2;
    pixel->g /= 2;
    pixel->b /= 2;
    pixel->a /= 2;
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    d %= 256; // 8 bit integer
    pixel->r = d >> 6 & 0x3;
    pixel->g = d << 4 & 0x3;
    pixel->b = d << 2 & 0x3;
    pixel->a = d << 0 & 0x3;
}

PNG treasureMap::renderMap(){

    return PNG();
}

PNG treasureMap::renderMaze(){

    setGrey(maze, start);
    return PNG();
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    auto neighborPixels = neighbors(curr);
    if (withinImg(next)){

    }
        return false;
}

bool treasureMap::withinImg(pair<int,int> loc){
    int x = loc.first;
    int y = loc.second;
    return x >= 0 && x <= width && y >= 0 && y <= height;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
{

    vector<pair<int, int>> neighbors;
    neighbors.push_back(pair<int, int>(curr.first + 1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first - 1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first, curr.second + 1));
    neighbors.push_back(pair<int, int>(curr.first, curr.second - 1));

    return neighbors;
}
