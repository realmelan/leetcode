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

# implementation
## build tree
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

## update tree
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

## query tree
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

# lazy propogation
To update a range, you may have to update one position of the range at a time, and potential runtime is about O(N).
Lazy propogation requires an additional lazy array as a backup storage, same size as original tree node array. During range update, if a node is completely covered by the range, it just update current node and stops, but leaving a non-zero value in the lazy array for its children nodes. Whenever a node is visited (for update or query), and if there is pending lazy update, apply update to current node and leaving lazy update  for its children nodes.
During query, when returning a node values, if there is pending update, apply the lazy update.

```c++

int a[];
int lazy[];
int update(int v, int tl, int tr, int l, int r, int val) {
    if lazy[v] != 0 {
        a[v] += (tr-tl+1)*lazy[v]
        if tr != tl {
            lazy[v*2] += lazy[v]
            lazy[v*2+1] += lazy[v]
        }
        lazy[v] = 0
    }
    if tr < tl || l > tr || r < tl {
        return
    }
    if l <= tl && tr <= r {
        a[v] += (tr-tl+1)*val
        if tr != tl {
            lazy[v*2] += lazy[v]
            lazy[v*2+1] += lazy[v]
        }
        return
    }
    int tm = (tl + tr) / 2
    update(v*2, tl, tm, l, r, val)
    update(v*2+1, tm+1, tr, l, r, val)
    a[v] = a[v*2] + a[v*2+1]
}

int sum(int v, int tl, int tr, int l, int r) {
    if lazy[v] != 0 {
        a[v] += (tr-tl+1)*lazy[v]
        if tr != tl {
            lazy[v*2] += lazy[v]
            lazy[v*2+1] += lazy[v]
        }
        lazy[v] = 0
    }
    if tr < tl || l > tr || r < tl {
        return 0
    }
    if l <= tl && tr <= r {
        return a[v]
    }
    int tm = (tl + tr) / 2
    return sum(v*2, tl, tm, l, r) + sum(v*2+1, tm+1, tr, l, r)
}

```

# Segment Tree vs Fenwick Tree
| Segment Tree | Fenwick Tree |
| ---- | ---- |
| use up to 4*N nodes, internal nodes for ranges  | use N nodes, each node is for one point in range |
| even both support O(logN) update and query, segment tree has high cost factor | lower cost factor, thus more efficient |
| support other types of queries like mininal/maximal values | only support sum query |



# Reference
* https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
* https://cp-algorithms.com/data_structures/segment_tree.html
* https://dev.to/wengao/fenwick-tree-vs-segment-tree-1edk
