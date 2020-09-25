Virtual index is a permutation of index 0 to n-1, such that vi(i) = another index into the same array, usually different from i.
Note, virtual index of (0..n-1) must map to (0..n-1).

Here are 2 examples of virtual index:
* Rotated index:
  a sorted array rotated index k, then let vi(i) = (i+k)%n. vi(0) would be able to access the smallest element of the array.
  
* Wiggle index:
  use vi(i) = (1+i*2)%(n|1) would be able to access array in order of 1, 3, 5, ..., 0, 2, 4...
  
# Problems:
* https://leetcode.com/problems/wiggle-sort-ii/
* https://leetcode.com/problems/search-in-rotated-sorted-array/
