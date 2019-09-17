Fenwick Tree, a.k.a. Binary Index Tree, is a data structure for prefix sum of an array.

Fenwick Tree provides O(lgn) update of array element and O(lgn) of prefix sum of array[1..i]. A node i of Fenwick Tree has sum of subarray of length = value of its least significant bit set, up to i. For example, when i=14, the least significant bit set is 2, so there are 2 elements in the subarray up to i (inclusive). Note, the Fenwick tree is 1-based.

To get sum of array[1..i], find out all bits that are set in i, iteratively remove the least significant bit in i and add the value at i to sum, until i becomes 0. For example, sum of subarray[1..14] = ft[14] + ft[12] + ft[8].

To update an element, all Fenwick tree nodes that contains the element should be updated. These nodes can be found out by iteratively adding the least significant bit to i, until the last element. For example, to update 10, then it should update ft[10], ft[10+2=12], ft[12+4=16], ft[16+16=32], etc, up to n (inclusive).

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
* https://en.wikipedia.org/wiki/Fenwick_tree
* https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
