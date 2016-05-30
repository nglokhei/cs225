/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim] || (first[curDim] == second[curDim] && first < second))
	return true;
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int curDist = d(currentBest, target);
    int poDist = d(potential, target);
    if (poDist < curDist || (poDist == curDist && potential < currentBest))
	return true;
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    if (!points.empty())
	buildTree(0, points.size() - 1, 0);
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> currentBest;
    int radius = 0;
    bool first = true;
    findNearestNeighbor(query, 0, 0, points.size() - 1, currentBest, radius, first);
    return currentBest;
}

// helper functions
template <int Dim>
int KDTree<Dim>::d(const Point<Dim>& first, const Point<Dim>& second) const{
    int d = 0;
    int diff = 0;
    for (int i = 0; i < Dim; i++){
	diff = first[i] - second[i];
	d += diff*diff;
    }
    return d;
}

template <int Dim>
void KDTree<Dim>::buildTree(int start, int end, int dim){
    if (start >= end)
	return;

    int medianIdx = (start + end) / 2;
    quickSort(start, end, dim, medianIdx);

    int newDim = (dim + 1) % Dim;
    buildTree(start, medianIdx - 1, newDim);
    buildTree(medianIdx + 1, end, newDim);
}

template <int Dim>
void KDTree<Dim>::quickSort(int start, int end, int dim, int medianIdx){
    int idx = start;
    for (int i = start; i < end; i++){
	if (smallerDimVal(points[i], points[end], dim)){
	    swap(i, idx);
	    idx++;
	}
    }
    swap(end, idx);
    if (idx < medianIdx)
	quickSort(idx + 1, end, dim, medianIdx);
    else if (idx > medianIdx)
	quickSort(start, idx - 1, dim, medianIdx);
}

template <int Dim>
void KDTree<Dim>::swap(int idx1, int idx2){
    Point<Dim> tmp = points[idx1];
    points[idx1] = points[idx2];
    points[idx2] = tmp;
}

template <int Dim>
void KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int dim, unsigned int start, unsigned int end, 
				      Point<Dim>& currentBest, int& radius, bool& first) const{
    if (start > end)
	return;
    
    // descend to the leaf
    unsigned int subroot = (start + end) / 2;
    int newDim = (dim + 1) % Dim;
    bool goLefted = false;
    if (smallerDimVal(query, points[subroot], dim)){
	goLefted = true;
	if (start < subroot)
	    findNearestNeighbor(query, newDim, start, subroot - 1, currentBest, radius, first);
    }
    else {
	if (subroot < end)
	    findNearestNeighbor(query, newDim, subroot + 1, end, currentBest, radius, first);
    }
        
    // check the subroot
    if (first || shouldReplace(query, currentBest, points[subroot])){
	currentBest = points[subroot];
	radius = d(currentBest, query);
	first = false;
    }

    int verDist = points[subroot][dim] - query[dim];
    if (verDist * verDist <= radius){
	if (goLefted){
	    if (subroot < end)
		findNearestNeighbor(query, newDim, subroot + 1, end, currentBest, radius, first);
	}
	else{
	    if (start < subroot)
		findNearestNeighbor(query, newDim, start, subroot - 1, currentBest, radius, first);
	}
    }

    return;
}





