/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include "quadtree.h"

Quadtree::Quadtree():root(NULL), size(0){}

Quadtree::Quadtree(PNG const &source, int resolution){
    size = resolution;
    root = subtree(source, 0, 0, resolution);
}

Quadtree::Quadtree(Quadtree const &other){
    size = other.size;
    root = copy(other.root);
}

Quadtree::~Quadtree(){
    clear();
}

Quadtree const & Quadtree::operator= (Quadtree const &other){
    if (this != &other){
	clear();
	size = other.size;
	root = copy(other.root);
    }
    return *this;
}
 
void Quadtree::buildTree(PNG const &source, int resolution){
    clear();
    size = resolution;
    root = subtree(source, 0, 0, resolution);
}    

RGBAPixel Quadtree::getPixel(int x, int y) const{
    if (x >= size || y >= size || root == NULL){
	RGBAPixel retval;
	return retval;
    }
    return getThePixel(x, y, root, size);
}

PNG Quadtree::decompress() const{
    if (size == 0){
	PNG img;
	return img;
    }

    PNG img(size, size);

    for(int i = 0; i < size; i++){
	for(int j = 0; j < size; j++){
	    *img(i,j) = getPixel(i,j);
	}
    }

    return img;
}

void Quadtree::clockwiseRotate(){
    if (root == NULL)
	return;
    clockwiseRotate(root);
}   

void Quadtree::prune (int tolerance){
    if (root == NULL)
	return;
    prune(root, tolerance);
}

int Quadtree::pruneSize (int tolerance) const{
    return pruneSize(root, tolerance, 0);
}

int Quadtree::idealPrune (int numLeaves) const{
    if (pruneSize(root, 0, 0) <= numLeaves)
	return 0;
	
    int upperBound = findUpperBound(numLeaves, 1);
    return bisection(numLeaves, upperBound, upperBound/2);
}

/* helper functions*/
Quadtree::QuadtreeNode* Quadtree::subtree(PNG const &source, size_t x, size_t y, int resolution){
    QuadtreeNode* r = new QuadtreeNode;
    if (resolution == 1){
	r -> element = *source(x,y);
	r -> nwChild = NULL;
	r -> neChild = NULL;
	r -> swChild = NULL;
	r -> seChild = NULL;
	return r;
    }

    int s = resolution/2;
    r -> nwChild = subtree(source, x, y, s);
    r -> neChild = subtree(source, x + s, y, s);
    r -> swChild = subtree(source, x, y + s, s);
    r -> seChild = subtree(source, x + s, y + s, s);
    r -> element = r -> average();
    return r;
}

Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* subroot){
    if (subroot == NULL)
	return NULL;

    QuadtreeNode* r = new QuadtreeNode;
    r -> nwChild = copy(subroot -> nwChild);
    r -> neChild = copy(subroot -> neChild);
    r -> swChild = copy(subroot -> swChild);
    r -> seChild = copy(subroot -> seChild);
    r -> element = subroot -> element;
    return r;
}

void Quadtree::clearTree(QuadtreeNode* &subroot){
    if (subroot == NULL)
	return;

    clearTree(subroot -> nwChild);
    clearTree(subroot -> neChild);
    clearTree(subroot -> swChild);
    clearTree(subroot -> seChild);

    delete subroot;  
    subroot = NULL;  
}

void Quadtree::clear(){
    clearTree(root);
    root = NULL;
}

RGBAPixel Quadtree::getThePixel(int x, int y, QuadtreeNode* subroot, int resolution) const{
    if (subroot -> nwChild == NULL || subroot -> neChild == NULL || subroot -> swChild == NULL || subroot -> seChild == NULL)
	return subroot -> element;

    int s = resolution/2;

    if (x < s && y < s)
	return getThePixel(x, y, subroot -> nwChild, s);
    else if (x >=s && y < s)
	return getThePixel(x - s, y, subroot -> neChild, s);
    else if (x < s && y >= s)
	return getThePixel(x, y - s, subroot -> swChild, s);
    else
	return getThePixel(x - s, y - s, subroot -> seChild, s);
}

// amazing algorithm !
void Quadtree::clockwiseRotate(QuadtreeNode* subroot){
    if (subroot -> nwChild == NULL || subroot -> neChild == NULL || subroot -> swChild == NULL || subroot -> seChild == NULL)
	return;

    clockwiseRotate(subroot -> nwChild);
    clockwiseRotate(subroot -> neChild);
    clockwiseRotate(subroot -> swChild);
    clockwiseRotate(subroot -> seChild);

    subroot -> clockwiseRotate();
}

void Quadtree::QuadtreeNode::clockwiseRotate(){
    QuadtreeNode* tmp = nwChild;
    nwChild = swChild;
    swChild = seChild;
    seChild = neChild;
    neChild = tmp;
    tmp = NULL;
}

RGBAPixel Quadtree::QuadtreeNode::average(){
    int red = nwChild -> element.red + neChild -> element.red + swChild -> element.red + seChild -> element.red;
    int green = nwChild -> element.green + neChild -> element.green + swChild -> element.green + seChild -> element.green;
    int blue = nwChild -> element.blue + neChild -> element.blue + swChild -> element.blue + seChild -> element.blue;

    RGBAPixel retval(red/4,green/4,blue/4);
    return retval;
}

void Quadtree::prune(QuadtreeNode* subroot, int tolerance){
    if (subroot == NULL)
	return;

    if (isPrune(subroot, tolerance, subroot -> element, true)){
	clearTree(subroot -> nwChild);
	clearTree(subroot -> neChild);
	clearTree(subroot -> swChild);
	clearTree(subroot -> seChild);
	return;
    }

    prune(subroot -> nwChild, tolerance);
    prune(subroot -> neChild, tolerance);
    prune(subroot -> swChild, tolerance);
    prune(subroot -> seChild, tolerance);
}

bool Quadtree::isPrune(QuadtreeNode* subroot, int tolerance, RGBAPixel ref, bool canPrune) const{
    if (canPrune){
	if (subroot -> nwChild == NULL || subroot -> neChild == NULL || subroot -> swChild == NULL || subroot -> seChild == NULL){
	    int diffRed = ref.red - subroot -> element.red;
	    int diffGreen = ref.green - subroot -> element.green;
	    int diffBlue = ref.blue - subroot -> element.blue;
	   
	    int dist = diffRed*diffRed + diffGreen*diffGreen + diffBlue*diffBlue;
	    if (dist > tolerance)
		return false;
	    return true;
	}

	canPrune = isPrune(subroot -> nwChild, tolerance, ref, canPrune);
	canPrune = isPrune(subroot -> neChild, tolerance, ref, canPrune);
	canPrune = isPrune(subroot -> swChild, tolerance, ref, canPrune);
	canPrune = isPrune(subroot -> seChild, tolerance, ref, canPrune);
    }
    return canPrune;
}	

int Quadtree::pruneSize (QuadtreeNode* subroot, int tolerance, int count) const{
    if (subroot == NULL)
	return count;

    if (isPrune(subroot, tolerance, subroot -> element, true))
	return ++ count;

    if (subroot -> nwChild == NULL || subroot -> neChild == NULL || subroot -> swChild == NULL || subroot -> seChild == NULL)
	return ++ count;

    int nwPrune = pruneSize(subroot -> nwChild, tolerance, 0);
    int nePrune = pruneSize(subroot -> neChild, tolerance, 0);
    int swPrune = pruneSize(subroot -> swChild, tolerance, 0);
    int sePrune = pruneSize(subroot -> seChild, tolerance, 0);
    return count + nwPrune + nePrune + swPrune + sePrune;
}

int Quadtree::findUpperBound(int numLeaves, int tolerance) const{
    if (pruneSize(root, tolerance, 0) <= numLeaves)
	return tolerance;
    return findUpperBound(numLeaves, tolerance * 2);
}

int Quadtree::bisection(int numLeaves, int upperBound, int lowerBound) const{
    if (upperBound - lowerBound < 2){
	if (pruneSize(lowerBound) <= numLeaves)
	    return lowerBound;
	return upperBound;
    }

    int tolerance = (upperBound + lowerBound)/2;
    if (pruneSize(tolerance) > numLeaves)
	return bisection(numLeaves, upperBound, tolerance);
    return bisection(numLeaves, tolerance, lowerBound);
}
