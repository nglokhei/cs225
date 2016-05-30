#include <iostream>
using namespace std;

class TreeNode {
public:
  int element;
  TreeNode * left;
  TreeNode * right;
  
  TreeNode(int value){ 
    element = value;
    left = NULL;
    right = NULL;
  }
};


int countSingleParents(TreeNode * root){
  //Your code goes here.
  //You may add helper methods if needed.
  if (root == NULL)
    return 0;

  int count = 0;
  if ((root -> left == NULL && root -> right != NULL) || (root -> left != NULL && root -> right == NULL))
	  count++;

  return count + countSingleParents(root -> left) + countSingleParents(root -> right);
}

int main(){
  //Example driver class for testing
  //You may add code here as you wish
  //This code will not be evaluated
  //This code does not test all possible test cases
                                                               
  TreeNode root = TreeNode(3);
  TreeNode elem1 = TreeNode(5);
  TreeNode elem2 = TreeNode(2);
  TreeNode elem3 = TreeNode(7);
  TreeNode elem4 = TreeNode(8);

  root.left = &elem1;
  root.right = &elem2;
  root.left->right = &elem3;
  root.right->right = &elem4;

  cout << countSingleParents(&root) << endl;

  return 0;
}
  
