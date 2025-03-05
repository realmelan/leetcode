# Segment Tree
Segment tree solves similar problems as [Fenwick Tree](FenwickTree.md), but applies to more problem categories like minimum/maximum, instead of just sums.
Time for update and query is similar to Fenwick tree, O(logN). However the constant factor is larger than Fenwick Tree.

The number of nodes(N) of a segment tree is predefined. Normally it is round up to the nearest power of 2.

# build tree
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

