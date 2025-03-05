# Segment Tree
Segment tree solves similar problems as [Fenwick Tree](FenwickTree.md), but applies to more problem categories like minimum/maximum, instead of just sums.
Time for update and query is similar to Fenwick tree, O(logN). However the constant factor is larger than Fenwick Tree.

The number of nodes(N) of a segment tree is predefined. Normally it is round up to the nearest power of 2. It takes 4 * N nodes to store N elements.
The sum of the root vertex at index 1, the sums of its two child vertices at indices 2 and 3, the sums of the children of those two vertices at indices 4 to 7, and so on. With 1-indexing, conveniently the left child of a vertex at index  
$i$  is stored at index  
$2i$ , and the right one at index  
$2i + 1$ . Equivalently, the parent of a vertex at index  
$i$  is stored at  
$i/2$  (integer division).

# build tree
The procedure for constructing the Segment Tree from a given array  
$a[]$  looks like this: it is a recursive function with the parameters  
$a[]$  (the input array),  
$v$  (the index of the current vertex), and the boundaries  
$tl$  and  
$tr$  of the current segment. In the main program this function will be called with the parameters of the root vertex:  
$v = 1$ ,  
$tl = 0$ , and  
$tr = n - 1$ .
```c++
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}
```

# update tree
```c++
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}
```

# query tree
Further the function for answering sum queries is also a recursive function, which receives as parameters information about the current vertex/segment (i.e. the index  
$v$  and the boundaries  
$tl$  and  
$tr$ ) and also the information about the boundaries of the query,  
$l$  and  
$r$ . In order to simplify the code, this function always does two recursive calls, even if only one is necessary - in that case the superfluous recursive call will have  
$l > r$ , and this can easily be caught using an additional check at the beginning of the function.
```c++
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}
```

# Reference
* https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
* https://cp-algorithms.com/data_structures/segment_tree.html

