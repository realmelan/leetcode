Fenwick Tree, a.k.a. Binary Index Tree, is a data structure for prefix sum of an array.

Fenwick Tree provides O(lgn) update of array element and O(lgn) of prefix sum of array[1..i].

A Fenwick Tree can be implemented using C++ like below:
```C++
#define LSB(x) (x)&(-(x))

class FenwickTree {
public:
    FenwickTree(int n) : arr(n) {}
    void update(int i, int x) {
        while (i < arr.size()) {
            arr[i] += x;
            i += LSB(i);
        }
    }
    int query(int i) {
        int res = 0;
        while (i > 0) {
            res += arr[i];
            i -= LSB(i);
        }
        return res;
    }
private:
    vector<int> arr;
}
```
# problems
* https://leetcode.com/problems/reverse-pairs/
  * solution: https://leetcode.com/problems/reverse-pairs/discuss/283504/C%2B%2B-O(nlgn)-solution-using-Fenwick-Tree(Binary-Indexed-Tree)-with-discretization

# Reference
https://en.wikipedia.org/wiki/Fenwick_tree
