You will be implementing the following function:

```
vector<int> buildMinHeap(vector<int> partialMinHeap)
```

Given a `std::vector` representation of a min-heap, with only leaf nodes
visible (the invisible nodes have placeholder values of -1), recover the rest
of the heap such that value of the parent node is the value of its max priority
child minus 1. Root of heap should correspond to index 1. For example, given
`[-inf, -1, -1, -1, 4, 5, 7, 8]`, you should return `[-inf, 2, 3, 6, 4, 5, 7,
8]`. (Note that the `-inf` at index 0 is just a placeholder so that heap starts
at index 1.)

Visual aid: 
```
given heap: 
      -1
    /    \
   -1    -1
  /  \   /  \
 4    5 7    8

returned heap:
      2
    /   \
   3     6
  / \   / \
 4   5 7   8 
```
