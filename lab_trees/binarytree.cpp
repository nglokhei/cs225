/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    // your code here
    return mirror(root);
}


/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    
    return isOrdered(root);
}


/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    // your code here
    int* path = new int[height(root) + 1];

    // print the paths by recurrence
    printPaths(path, 0, root);

    delete [] path;
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int sum = 0;
    sumDistances(root, sum, 0);
    return sum;
}

template <typename T>
void BinaryTree<T>::mirror(Node* subroot){
    if (subroot == NULL)  
	return;
    
    mirror(subroot -> left);
    mirror(subroot -> right);
    
    Node* tmp = subroot -> left;
    subroot -> left = subroot -> right;
    subroot -> right = tmp;
    tmp = NULL;
}

template <typename T>
T BinaryTree<T>::maxVal(Node* subroot) const{
    T mx = subroot -> elem;
    T tmp = mx;

    // compare with left node
    if (subroot -> left != NULL){
	tmp = maxVal(subroot -> left);
	if (mx < tmp)
  	    mx =tmp;
    }
    
    //comopare with right node
    if (subroot -> right != NULL){
	tmp = maxVal(subroot -> right);
	if (mx < tmp)
  	    mx =tmp;
    }
    return mx;
}

template <typename T>
T BinaryTree<T>::minVal(Node* subroot) const{
    T mn = subroot -> elem;
    T tmp = mn;

    // compare with left node
    if (subroot -> left != NULL){
	tmp = minVal(subroot -> left);
	if (mn > tmp)
  	    mn =tmp;
    }
    
    //comopare with right node
    if (subroot -> right != NULL){
	tmp = minVal(subroot -> right);
	if (mn > tmp)
  	    mn =tmp;
    }
    return mn;
}

template <typename T>
bool BinaryTree<T>::isOrdered(Node* subroot) const{
    if (subroot == NULL || height(subroot) == 0)
	return true;

    T nodeVal = subroot -> elem;

    T maxLeft = nodeVal;
    if (subroot -> left != NULL)
	maxLeft = maxVal(subroot -> left);

    T minRight = nodeVal;
    if (subroot -> right != NULL)
	minRight = minVal(subroot -> right);  

 
    if (isOrdered(subroot -> left) && maxLeft <= nodeVal && nodeVal <= minRight && isOrdered(subroot -> right))
	return true;
    return false;
}

template <typename T>
void BinaryTree<T>::printPaths(int* path, int idx, Node* subroot) const{

    path[idx++] = subroot -> elem;
    
    if (subroot -> left == NULL && subroot -> right == NULL){
	// print the path
	cout << "Path:";
	for (int i = 0; i < idx; i++)
	    cout << " " << path[i];
	cout << endl;
	return;
    }
    
    if (subroot -> left != NULL)
	printPaths(path, idx, subroot -> left);

    if (subroot -> right != NULL)
	printPaths(path, idx, subroot -> right);
}


template <typename T>
void BinaryTree<T>::sumDistances(Node* subroot, int &sum, int depth) const{
    if (subroot == NULL)
	return;
    
    sum = sum + depth;
    
    if (subroot -> left != NULL)
	sumDistances(subroot -> left, sum, depth + 1);

    if (subroot -> right != NULL)
	sumDistances(subroot -> right, sum, depth + 1);

}




