#include "binarytree.h"

int BinaryTree::find(int key) {
    /* Your code here! */
    return find(key, root);
}

int BinaryTree::find(int key, Node* subroot){
    if (subroot == NULL)
	return 0;
    int l = find(key, subroot -> left);
    int r = find(key, subroot -> right);
    int cur = 0;
    if (subroot -> elem == key)
	cur ++;
    return l + r + cur;
}
