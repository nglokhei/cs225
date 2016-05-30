You will be implementing the following function:

```
vector<int> orderedGroup(int arr[], int size);
```

Given an unsorted array that may contain duplicates and its length `size`,
write a function that returns a vector that has grouped all the elements in the
array based on their first occurence in the array.

Examples:

- `arr = {1, 2, 3, 2, 1}` should return `<1, 1, 2, 2, 3>` (1 occurs before 2 and 2 occurs before 3 in the array)
- `arr = {1, 2, 3, 2, 5, 6, 5}` should return `<1, 2, 2, 3, 5, 5, 6>`
- `arr = {2, 4, 1, 3, 3, 2, 4, 1, 1, 2, 4, 3}` should return `<2, 2, 2, 4, 4, 4, 1, 1, 1, 3, 3, 3}` (2 occurs before 4, 4 occurs before 1 and 1 occurs before 3 in the array)

You may find the <a href="<%= clientFile('cpp-reference/en/cpp/utility/pair/make_pair.html') %>" target="_blank">make_pair</a> function useful.

*Hint: think about how you will keep the order intact. The C++
`map`/`unordered_map` that you will be using won't guarantee you an order. So,
what should you iterate over?*
