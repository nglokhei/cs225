/* Your code here! */

#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "maze.h"
#include "dsets.h"

SquareMaze :: SquareMaze() {}

void SquareMaze :: makeMaze (int width, int height) {
    this -> height = height;
    this -> width = width;
    int n = width * height;
    s.addelements(n);

    // initialize the walls
    std::vector<std::vector<int>> potentialWallBreak;
    downWalls = {};
    rightWalls = {};
    for (int i = 0; i < height; i++){
	for (int j = 0; j < width; j++){
	    downWalls.push_back(true);
	    rightWalls.push_back(true);
	    if (i != height - 1){
		potentialWallBreak.push_back({j,i,1});
	    }
	    if (j != width - 1){
		potentialWallBreak.push_back({j,i,0});
	    }
	}
    }

    // make random maze
    int edgeNum = 0 ;
    int potSize = potentialWallBreak.size();
    for (int i = 0 ; i < potSize; i++)
	std::cout << potentialWallBreak[i][0] << " " << potentialWallBreak[i][1] << " " << potentialWallBreak[i][2] << std::endl;
    while (edgeNum < n - 1 ) {
	// randomly pick a wall
	int index = rand() % potSize;

	std::vector<int> chosenWall = potentialWallBreak[index];
	potentialWallBreak[index] = potentialWallBreak[potSize- 1];
	potSize--;
	
	// extract information
	int index1 = chosenWall[1]*width + chosenWall[0];
	int index2;
	if (chosenWall[2] == 0)
	    index2 = index1 + 1;
	else
	    index2 = index1 + width;

	// set walls 
	if (s.find(index1) != s.find(index2)){
	    edgeNum++;
	    s.setunion(index1,index2);
	    setWall(chosenWall[0], chosenWall[1], chosenWall[2], false);
	}
    }
}

bool SquareMaze :: canTravel (int x, int y, int dir) const {
    if (dir == 0)
	return !rightWalls[width*y+x];
    if (dir == 1)
	return !downWalls[width*y+x];
    if (dir == 2 && x > 0)
	return !rightWalls[width*y + x - 1];
    if (dir == 3 && y > 0)
	return !downWalls[width*(y-1) + x];
    return false;
}

void SquareMaze :: setWall (int x, int y, int dir, bool exists){
    if (dir)
	downWalls[width*y + x] = exists;
    else
	rightWalls[width*y + x] = exists;
    return;
}

std::vector<int> SquareMaze :: solveMaze(){
    int x;
    int y;
    int lastDir;
    int count = 0;
    std::vector<int> pathDest = {0,0,1};
    std::queue<std::vector<int>> q;
    q.push(pathDest);
 
    while (count < width){
	pathDest = q.front();
	q.pop();
	x = pathDest[0];
	y = pathDest[1];
	if (y == height - 1){
	    count++;
	}
	lastDir = pathDest[pathDest.size() - 1];
	if (lastDir != 2 && canTravel(x,y,0)){
	    pathDest.push_back(0);
	    pathDest[0]++;
	    q.push(pathDest);
	    pathDest[0]--;
	    pathDest.pop_back();
	}
	if (lastDir != 3 && canTravel(x,y,1)){
	    pathDest.push_back(1);
	    pathDest[1]++;
	    q.push(pathDest);
	    pathDest[1]--;
	    pathDest.pop_back();
	}
	if (lastDir != 0 && canTravel(x,y,2)){
	    pathDest.push_back(2);
	    pathDest[0]--;
	    q.push(pathDest);
	    pathDest[0]++;
	    pathDest.pop_back();
	}
	if (lastDir != 1 && canTravel(x,y,3)){
	    pathDest.push_back(3);
	    pathDest[1]--;
	    q.push(pathDest);
	    pathDest[1]++;
	    pathDest.pop_back();
	}
    }

    //print dest and path
    pathDest.erase(pathDest.begin(),pathDest.begin() + 3);
    return pathDest;
}

PNG* SquareMaze :: drawMaze() const {
    PNG* img = new PNG(10 * width + 1, 10 * height + 1);

    // blacken the topmost and leftmost
	(*img)(0,0) -> red = 0;
	(*img)(0,0) -> green = 0;
	(*img)(0,0) -> blue = 0;

    for (int i = 0; i < 10 * height; i++){
	(*img)(0,i) -> red = 0;
	(*img)(0,i) -> green = 0;
	(*img)(0,i) -> blue = 0;
    }
    for (int j = 10; j < 10 * width; j++){
	(*img)(j,0) -> red = 0;
	(*img)(j,0) -> green = 0;
	(*img)(j,0) -> blue = 0;
    }

    // draw internal structure of the maze
    for (int y = 0; y < height; y++){
	for (int x = 0; x < width; x++){

	    if (rightWalls[width*y+x]){
		for (int k = 0; k <= 10; k++){
		    (*img)(10*(x+1), 10*y+k) -> red = 0;
		    (*img)(10*(x+1), 10*y+k) -> green = 0;
		    (*img)(10*(x+1), 10*y+k) -> blue = 0;
		}
	    }
	    if (downWalls[width*y+x]){
		for (int k = 0; k <= 10; k++){
		    (*img)(10*x+k,(y+1)*10) -> red = 0;
		    (*img)(10*x+k,(y+1)*10) -> green = 0;
		    (*img)(10*x+k,(y+1)*10) -> blue = 0;
		}
	    }
	}
    }
    return img;
}

PNG* SquareMaze :: drawMazeWithSolution() {
    PNG* img = drawMaze();
    std::vector<int> path = solveMaze();
    int x = 5;
    int y = 5;
    int length = 11;
    for (size_t i = 0; i < path.size(); i++){

	if (path[i] == 0){
	    for (int k = 0; k < length; k++){
		(*img)(x + k,y) -> red = 255;
		(*img)(x + k,y) -> green = 0;
		(*img)(x + k,y) -> blue = 0;
	    }
	    x += 10;
	}
	if (path[i] == 1){
	    for (int k = 0; k < length; k++){
		(*img)(x,y + k) -> red = 255;
		(*img)(x,y + k) -> green = 0;
		(*img)(x,y + k) -> blue = 0;
	    }
	    y += 10;
	}
	if (path[i] == 2){
	    for (int k = 0; k < length; k++){
		(*img)(x - k,y) -> red = 255;
		(*img)(x - k,y) -> green = 0;
		(*img)(x - k,y) -> blue = 0;
	    }
	    x -= 10;
	}
	if (path[i] == 3){
	    for (int k = 0; k < length; k++){
		(*img)(x,y - k) -> red = 255;
		(*img)(x,y - k) -> green = 0;
		(*img)(x,y - k) -> blue = 0;
	    }
	    y -= 10;
	}
    }
    x = x - 4;
    for (int i = 0; i < 9; i++){
	(*img)(x,10 * height) -> red = 255;
	(*img)(x,10 * height) -> green = 255;
	(*img)(x++,10 * height) -> blue = 255;
    }
    return img;
}




