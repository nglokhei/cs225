/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    Quadtree();
    Quadtree(PNG const &source, int resolution);
    Quadtree(Quadtree const &other);
    ~Quadtree();
    Quadtree const & operator=(Quadtree const &other);
    void buildTree(PNG const &source, int resolution);
    RGBAPixel getPixel(int x, int y) const;
    PNG decompress() const;
    void clockwiseRotate();
    void prune (int tolerance);
    int pruneSize (int tolerance) const;
    int idealPrune (int numLeaves) const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */	
    class QuadtreeNode
    {
      public:

        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
	
	void clockwiseRotate();
	RGBAPixel average();
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    /** (x,y) is the pixel at the top left corner **/
    QuadtreeNode* subtree(PNG const &source, size_t x, size_t y, int resolution);

    QuadtreeNode* copy(QuadtreeNode* subroot);

    void clearTree(QuadtreeNode* &subroot);

    void clear();
 
    int size;

    RGBAPixel getThePixel(int x, int y, QuadtreeNode* subroot, int resolution) const;

    void clockwiseRotate(QuadtreeNode* subroot);

    void prune(QuadtreeNode* subroot, int tolerance);

    bool isPrune(QuadtreeNode* subroot, int tolerance, RGBAPixel ref, bool canPrune) const;

    int pruneSize (QuadtreeNode* subroot, int tolerance, int count) const;

    int findUpperBound(int numLeaves, int tolerance) const;
  
    int bisection(int numLeaves, int upperBound, int lowerBound) const;

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
