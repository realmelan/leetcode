# Ref:
https://abitofcs.blogspot.com/2014/11/data-structure-sliding-window-minimum.html

Data Structure: Sliding Window Minimum / Monotonic Queue
Given an array of elements a0,a1,a2,…,an, and queries Q(i,i+L) which means "find the minimum element in ai,ai+1,…,ai+L ".
How can we answer such queries efficiently?

We can have an O(nlgn) complexity by using a minimum priority queue, RB tree, or a binary tree representation of multiset, 
but there in this setting we can implement a data structure called monotonic queue which only requires O(n) in construction.
The implementation of this data structure requires a dequeue.

Let D be the dequeue which maintain a pair of information (i, ai). 
An important property of D that we will maintain is that element in D will always be in sorted order (invariant). 
We will first start with an empty D, and will insert ai and remove elements from D accordingly as we iterate
from the left to the right of array a (which is from i = 0, 1, 2, ..., n).

Suppose that we are now at index i and considering to add ai. 
Notice that when ai is added, all elements in (j, aj) in D such that aj is bigger than ai can never be a minimum value as we go forward, 
hence they can be removed from D. Furthermore, if the element (i-L-1, ai−L−1) is in D (which will be located at the top of D if it exists),
we remove that element as well. Lastly, we append ai at the back of D. Then we will have Q(i-L, i) = the top element in D
when we reach index i. Since each element will enter and leave D only once, we have a total of O(N) operations. 


# New reference:
* https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/discuss/204290/Monotonic-Queue-Summary
* https://reprog.wordpress.com/2010/04/25/writing-correct-code-part-1-invariants-binary-search-part-4a/
