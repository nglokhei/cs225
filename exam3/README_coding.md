#### Question 9

You will be implementing the following methods in the `BinaryTree` class:

- `int find(int key);`

Given a binary tree and key, write a function `find(int key)` to compute the
number of occurences of the key in the tree.

The function should return the key's frequency.

If the key is not present, your function should return 0.

For example, if the tree given is:

```
     _10_
    /    \
  11      9
 /  \    / \
8    4  6   4
```

Then `find(4)` should return 2, and `find(20)` should return 0.

**Write your solution in `binarytree_q9.cpp`.**


- - -

#### Question 10

You will be implementing the following methods in the `BinaryTree` class:

- `void makeBST(std::vector<int>arr);`

Given a sorted array of size $2^{h+1}-1$, construct a perfect Binary Search
Tree with keys being the element of the array.

The root should be set to `NULL` if the array is of size 0.

For example, if the array is:

```
[12, 15, 18, 20, 22, 24, 26]
```


`makeBST` should produce the tree:

```
     20
   /    \
  15    24
 /  \  /  \
12  18 22 26
```

Recall that a perfect tree is one in which all the leaf nodes have same height
and every node other than the leaves has two children.

You can get the length of a vector `v` using `v.size()`.

*Hint: It is better NOT to use the `BinaryTree::insert` function with
`sorted=true`, because it may easily result in a BST that is not Perfect.*

**Write your solution in `binarytree_q10.cpp`.**
