#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s){
    base = baseim;
    maze = mazeim;
    start = s;
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){  
    // RGBAPixel* pixel = im.getPixel(loc.first, loc.second);
    // pixel->r = 2 * (pixel->r / 4);
    // pixel->g = 2 * (pixel->g / 4);
    // pixel->b = 2 * (pixel->b / 4);
}

void treasureMap::Debug(PNG &im, pair<int, int> loc, int d)
{
    setLOB(im, loc, d);
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    d %= 64;
    pixel->r = (pixel->r & 0xFC) | ((d >> 4) & 0x3);
    pixel->g = (pixel->g & 0xFC) | ((d >> 2) & 0x3);
    pixel->b = (pixel->b & 0xFC) | (d & 0x3);

    // cout<< "pixel = "<< *pixel<<endl;
}

PNG treasureMap::renderMap(){
    PNG baseMap = base;
    vector<vector<bool>> visited(baseMap.height(), vector<bool>(baseMap.width()));
    vector<vector<int>> dist(baseMap.height(), vector<int>(baseMap.width()));

    Queue<pair<int,int>> queue;

    visited[start.second][start.first] = true;
    dist[start.second][start.first] = 0;
    setLOB(baseMap, start, 0);
    queue.enqueue(start);

    while(!queue.isEmpty()){
        auto curr = queue.dequeue();
        for(auto p: neighbors(curr)){
            if(good(visited,curr,p)){
                visited[p.second][p.first] = true;
                dist[p.second][p.first] = dist[curr.second][curr.first] + 1;
                setLOB(baseMap, p, dist[p.second][p.first]);
                queue.enqueue(p);
            }
        }
    }

    return baseMap;
}

PNG treasureMap::renderMaze(){

    // // draw a red 7px x 7 px square
    // int xStartPos = start.first;
    // int yStartPos = start.second;
    // for (int i = xStartPos + 1; i <= xStartPos + 3; i++)
    // {
    //     for (int j = yStartPos + 1; j <= yStartPos + 3; j++)
    //     {
    //         if(withinImg(make_pair(i,j))){
    //             maze.getPixel(i, j)->r = 255;
    //         }
    //         if(withinImg(make_pair(i-4,j-4))){
    //             maze.getPixel(i - 4, j - 4)->r = 255;
    //         }
    //     }
    // }
    // // find path and render maze map
    // vector<vector<bool>> visited(maze.height(), vector<bool> (maze.width()));

    // Queue<pair<int, int>> queue;
    // queue.enqueue(start);
    // while (!queue.isEmpty())
    // {
    //     auto curr = queue.dequeue();
    //     auto adjPixels = neighbors(curr);
    //     for (auto p : adjPixels)
    //     {
    //         if(good(visited,curr,p)){
    //             setGrey(maze, p);
    //             queue.enqueue(p);
    //         }
    //     }
    // }
    // return maze;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    return withinImg(next) && !visited(v, next) && sameColor(curr, next);
}

bool treasureMap::withinImg(pair<int,int> loc) const {
    int x = loc.first;
    int y = loc.second;
    return x >= 0 && x < (int)base.width() && y >= 0 && y < (int)base.height();
}

bool treasureMap::visited(vector<vector<bool>>& visited, pair<int,int> next) const {
    return visited[next.second][next.first];
}

bool treasureMap::sameColor(pair<int,int> curr, pair<int,int> next) const {
    RGBAPixel *currPix = maze.getPixel(curr.first,curr.second);
    RGBAPixel *nextPix = maze.getPixel(next.first,next.second);
    
    return *currPix == *nextPix;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
{
    vector<pair<int, int>> neighbors;
    neighbors.push_back(pair<int, int>(curr.first - 1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first, curr.second + 1));
    neighbors.push_back(pair<int, int>(curr.first + 1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first, curr.second - 1));

    return neighbors;
}
