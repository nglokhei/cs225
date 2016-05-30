/* Your code here! */

#ifndef _MAZE_H_
#define _MAZE_H_

#include <vector>
#include "png.h"
#include "dsets.h"

class SquareMaze {
    public :
	SquareMaze();
	void makeMaze (int width, int height);
	bool canTravel (int x, int y, int dir) const;
	void setWall (int x, int y, int dir, bool exists);
	std::vector<int> solveMaze();
	PNG* drawMaze() const;
	PNG* drawMazeWithSolution();
    private :
	std::vector<bool> rightWalls;
	std::vector<bool> downWalls;
	int width;
	int height;
	DisjointSets s;
};

#endif
