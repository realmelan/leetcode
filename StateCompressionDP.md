# State Compression Dynamic Programming

This kind of dynamic programming problems specify # of elements, but the result requires a set of the elements. 
For instance, courses have dependencies, and result is to finish all courses in shortest time. Here, each course 
can be represented with a bit in the state integer, and the final state integer has all bits set.

Code like below can be used to solve this problem:
```c++
for st in 0 to (1<<n)-1:
    for each choice i in available choices:
        nst = st | <state udpate>
        nres = updated result using st and i
        dp[nst] = min(dp[nst], nres)
        // note since nst > st, by the time for processing nst, nst has been updated by every situation that leads to it
```


Here available choices may be a single element or a subset of elements (if required to take more than 1 element).
Code like below can loop through all possible subset of available choices
```c++
// say avail represents all bits that are now available for st
for (int i = avail; i > 0; i=(i-1)&avail) {
   // deal with choice i
}
```

Note, this kind of problems has very small input set, like <=20 or so.


# Reference
* https://www.hackerearth.com/practice/algorithms/dynamic-programming/bit-masking/tutorial/
* http://codeforces.com/blog/entry/337

# problems
* https://leetcode.com/problems/parallel-courses-ii/discuss/708445/Weak-test-case-most-solutions-posted-using-depth-or-outdgree-are-wrong
* https://leetcode.com/problems/smallest-sufficient-team/

