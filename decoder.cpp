#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

   // TODO
   pathPts.push_back(start);
}

PNG decoder::renderSolution(){
   PNG solImg = mapImg;
   // TODO: check if it is the shortest path to the point which is farthest
   for(auto p : pathPts){
      RGBAPixel *pixel = solImg.getPixel(p.first, p.second);
      pixel->r = 255;
      pixel->g = 0;
      pixel->b = 0;
   }
   return solImg;
}

PNG decoder::renderMaze(){
   PNG mazeImg = mapImg;
   vector<vector<bool>> visited(mazeImg.height(), vector<bool>(mazeImg.width()));
   // TODO: populate dist
   vector<vector<int>> dist(mazeImg.height(), vector<int>(mazeImg.width()));
   Queue<pair<int, int>> queue;

   visited[start.second][start.first] = true;
   setGrey(mazeImg, start);
   queue.enqueue(start);

   while(!queue.isEmpty()){
      auto curr = queue.dequeue();
      for(auto p: neighbors(curr)) {
         if(good(visited,dist,curr,p)) {
            visited[p.second][p.first] = true;
            setGrey(mazeImg, p);
            queue.enqueue(p);
         }
      }  
   }

   // draw a red 7px x 7 px square
   int xPos = start.first;
   int yPos = start.second;
   for (int y = yPos - 3; y < yPos + 4; y++)
   {
      for (int x = xPos - 3; x < xPos + 4; x++)
      {
         if (withinImg(make_pair(x, y)))
         {
            RGBAPixel *pixel = mazeImg.getPixel(x, y);
            pixel->r = 255;
            pixel->g = 0;
            pixel->b = 0;
         }
      }
   }

   return mazeImg;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){
   RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
   pixel->r = 2 * (pixel->r / 4);
   pixel->g = 2 * (pixel->g / 4);
   pixel->b = 2 * (pixel->b / 4);
}

pair<int,int> decoder::findSpot(){

   return pathPts[pathPts.size() - 1];
}

int decoder::pathLength(){

   return pathPts.size();
}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){
   int curr_d = d[curr.second][curr.first];
   RGBAPixel next_pixel = *mapImg.getPixel(next.first, next.second);

   return withinImg(next) && !visited(v, next) && compare(next_pixel, curr_d);
}

bool decoder::withinImg(pair<int,int> loc) const{
   int x = loc.first;
   int y = loc.second;
   return x >= 0 && x < (int)mapImg.width() && y >= 0 && y < (int)mapImg.height();
}

bool decoder::visited(vector<vector<bool>> &visited, pair<int, int> next) const
{
   return visited[next.second][next.first];
}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

   vector<pair<int, int>> neighbors;
   neighbors.push_back(pair<int, int>(curr.first - 1, curr.second));
   neighbors.push_back(pair<int, int>(curr.first, curr.second + 1));
   neighbors.push_back(pair<int, int>(curr.first + 1, curr.second));
   neighbors.push_back(pair<int, int>(curr.first, curr.second - 1));

   return neighbors;
}

bool decoder::compare(RGBAPixel p, int d){
   int val = (p.r % 4) * 16 + (p.g % 4) * 4 + (p.b % 4); // val = [0,63]
   d %= 64;

   return abs(val - d) == 1;
}
