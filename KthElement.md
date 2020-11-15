# K-th Element from unsorted array

## sort
sort the array and then pick the k-th element. Runtime is O(nlogn).

## priority_queue
use priority_queue to maintain a size K heap. Runtime is O(nlogK)

## nth_element
use C++ std library function partial_sort or nth_element directly.

Average runtime is O(n), worst is O(n^2).

## manual nth element implementation
```C++
int nth(vector<int>& array, int K) {
    int l = 0, r = array.size() - 1;
    while (l < r) {
        int mid = partition(array, l, r);
        if (mid == K) {
            l = mid;
            break;
        } else if (mid > K) {
            r = mid-1;
        } else {
            l = mid+1;
        }
    }
    return array[l];
}
// this looks like dutch flag problem.
int partition(vector<int>& array, int l, int r) {
    int pivot = array[r];
    for (int i = l; i < r; ++i) {
        if (array[i] < pivot) {
            swap(array[l++], array[i]);
        }
    }
    swap(array[l], array[r]);
    return l;
}
```
