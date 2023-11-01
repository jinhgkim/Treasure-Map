#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s){
    base = baseim;
    start = s;
    maze = mazeim;
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){  
    RGBAPixel* pixel = im.getPixel(loc.first, loc.second);
    pixel->r /= 2;
    pixel->g /= 2;
    pixel->b /= 2;
}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    pixel->r = (pixel->r & 0xFC) | ((d % 64) >> 4);
    pixel->g = (pixel->g & 0xFC) | ((d % 64) >> 2);
    pixel->b = (pixel->b & 0xFC) | (d % 64);
}

PNG treasureMap::renderMap(){
    PNG copy = base;
    vector<vector<bool>> visited(copy.height(), vector<bool>(copy.width()));
    vector<vector<int>> dist(copy.height(), vector<int> (copy.width()));
    Queue<pair<int, int>> queue;

    int xPos = start.first;
    int yPos = start.second;

    visited[yPos][xPos] = true;
    dist[yPos][xPos] = 0;

    setLOB(copy, start, 0);

    queue.enqueue(start);
    while(!queue.isEmpty()){
        auto curr = queue.dequeue();
        auto adjPixels = neighbors(curr);
        for(auto p : adjPixels){
            if(good(visited,curr,p)){
                visited[p.second][p.first] = true;
                dist[p.second][p.first] = dist[curr.second][curr.first] + 1;
                setLOB(copy, p, dist[p.second][p.first]);
                
                queue.enqueue(p);
            }
        }
    }

    return copy;
}

PNG treasureMap::renderMaze(){

    // draw a red 7px x 7 px square
    int xStartPos = start.first;
    for (int i = xStartPos + 1; i <= xStartPos + 3; i++)
    {
        for (int j = xStartPos + 1; j <= xStartPos + 3; j++)
        {
            maze.getPixel(i, j)->r = 255;
            maze.getPixel(i - 4, i - 4)->r = 255;
        }
    }
    // find path and render maze map
    vector<vector<bool>> visited(maze.height(), vector<bool> (maze.width()));

    Queue<pair<int, int>> queue;
    queue.enqueue(start);
    while (!queue.isEmpty())
    {
        auto curr = queue.dequeue();
        auto adjPixels = neighbors(curr);
        for (auto p : adjPixels)
        {
            if(good(visited,curr,p)){
                setGrey(maze, p);
                queue.enqueue(p);
            }
        }
    }
    return maze;
}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    return withinImg(next) && unvisited(v, next) && sameColor(curr, next);
}

bool treasureMap::withinImg(pair<int,int> loc) const {
    int x = loc.first;
    int y = loc.second;
    return x >= 0 && x <= (int)base.width() && y >= 0 && y <= (int)base.height();
}

bool treasureMap::unvisited(vector<vector<bool>>& visited, pair<int,int> next) const {
    return visited[next.second][next.first];
}

bool treasureMap::sameColor(pair<int,int> curr, pair<int,int> next) const {
    RGBAPixel *currPix = base.getPixel(curr.first,curr.second);
    RGBAPixel *nextPix = base.getPixel(next.first,next.second);
    
    return *currPix == *nextPix;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
{

    vector<pair<int, int>> neighbors;
    neighbors.push_back(pair<int, int>(curr.first - 1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first, curr.second-1));
    neighbors.push_back(pair<int, int>(curr.first+1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first, curr.second + 1));

    return neighbors;
}
