/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int row = theSource.getRows();
    int col = theSource.getColumns();
    MosaicCanvas* retval = new MosaicCanvas(row, col);
    vector<Point<3>> treeVec; 
    map <Point<3>, int> imgIdx;
    Point<3> avgColVec;
    RGBAPixel avgCol;
    
    // build treeVec
    for (unsigned long i = 0; i < theTiles.size(); i++){
	avgCol = theTiles[i].getAverageColor();
	avgColVec[0] = avgCol.red;
	avgColVec[1] = avgCol.green; 
	avgColVec[2] = avgCol.blue;
	treeVec.push_back(avgColVec);
	imgIdx[avgColVec] = i;
    }
    KDTree<3> mytree(treeVec);

    for (int i = 0; i < row; i++){
	for (int j = 0; j < col; j++){
	    avgCol = theSource.getRegionColor(i, j);
	    avgColVec[0] = avgCol.red;
	    avgColVec[1] = avgCol.green;
	    avgColVec[2] = avgCol.blue;
	    Point<3> nbr = mytree.findNearestNeighbor(avgColVec);
	    retval -> setTile(i, j, theTiles[imgIdx[nbr]]);
	}
    }

    return retval;
}

