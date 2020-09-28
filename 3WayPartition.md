Also known as Dutch National Flag problem, the algorithm partitions an array into 3 groups based on their relation with a given mid value:
array elements smaller than the mid value will be in the first range, followed by a subarray of mid value itself, followed by array
elements larger than the mid value.


```
The following pseudocode for three-way partitioning which assumes zero-based array indexing was proposed by Dijkstra himself.[2] It uses three indices i, j and k, maintaining the invariant that i ≤ j ≤ k.

Entries from 0 up to (but not including) i are values less than mid,
entries from i up to (but not including) j are values equal to mid,
entries from j up to (but not including) k are values not yet sorted, and
entries from k to the end of the array are values greater than mid.

procedure three-way-partition(A : array of values, mid : value):
    i ← 0
    j ← 0
    n ← size of A - 1

    while j ≤ n:
        if A[j] < mid:
            swap A[i] and A[j]
            i ← i + 1
            j ← j + 1
        else if A[j] > mid:
            swap A[j] and A[n]
            n ← n - 1
        else:
            j ← j + 1
```
j will be greater than i only if the mid is hit.


# Ref
* https://en.wikipedia.org/wiki/Dutch_national_flag_problem
