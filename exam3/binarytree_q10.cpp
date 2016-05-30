#include "binarytree.h"

void BinaryTree::makeBST(std::vector<int>arr) {
    /* Your code here! */
    if (arr.size() == 0){
	root = NULL;
	return;
    }
    makeBST(arr, root);
    return;
}

void BinaryTree::makeBST(std::vector<int> arr, Node* &subroot){
    int rootelem = arr[arr.size()/2];
    root -> elem = rootelem;
    std::vector<int> arr1;
    std::vector<int> arr2;
    for (unsigned int i = 0; i < arr.size(); i++){
	if (i < arr.size()/2)
	    arr1.push(arr[i]);
	else if (i > arr.size()/2)
	    arr2.push(arr[i]);
    }
    makeBST(arr1, subroot -> left);
    makeBST(arr2, subroot -> right);

    delete arr1;
    delete arr2;
    return;
