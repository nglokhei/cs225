/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node* tmp = t -> right;
    t -> right = tmp -> left;
    tmp -> left = t;

    t -> height = max(heightOrNeg1(t -> left), heightOrNeg1(t -> right)) + 1;
    tmp -> height = max(heightOrNeg1(tmp -> left), heightOrNeg1(tmp -> right)) + 1;

    t = tmp;
    tmp = NULL;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node* tmp = t -> left;
    t -> left = tmp -> right;
    tmp -> right = t;

    t -> height = max(heightOrNeg1(t -> left), heightOrNeg1(t -> right)) + 1;
    tmp -> height = max(heightOrNeg1(tmp -> left), heightOrNeg1(tmp -> right)) + 1;

    t = tmp; 
    tmp = NULL;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t -> right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL)
	return;

    int b = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
    if (b == -2){
	int lb = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left -> left);
	if (lb == -1) 
	    rotateRight(subtree);
	else
	    rotateLeftRight(subtree);
    }
    else if (b == 2){
	int rb = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right -> left);
	if (rb == 1)
	    rotateLeft(subtree);
	else
	    rotateRightLeft(subtree);	
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL){
	subtree = new Node(key, value);
        return;
    }
    else{
	if (key < subtree -> key)
	    insert(subtree -> left, key, value);
	else
	    insert(subtree -> right, key, value);
	
	rebalance(subtree);

	// update the height
	int left = heightOrNeg1(subtree -> left);
	int right = heightOrNeg1(subtree -> right);
	subtree -> height = max(left, right) + 1;
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
	remove(subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
	remove(subtree -> right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here

	    delete subtree;
	    subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
	    Node* tmp = subtree -> left;
	    Node* tmp2;
	    while (tmp -> right != NULL){
	 	tmp2 = tmp;
		tmp = tmp -> right;
	    }
	    swap(tmp, subtree);
	    remove(tmp, key);
	    tmp = NULL;
	    tmp2 -> right = NULL;
	    tmp2 = NULL;

        } else {
            /* one-child remove */
            // your code here
	    Node* tmp = subtree;
	    if (subtree -> left != NULL)
		tmp = subtree -> left;
	    else
		tmp = subtree -> right;
	
	    delete subtree;
	    subtree = tmp;
	    tmp = NULL;
        }
        // your code here
    }

    rebalance(subtree);
}
