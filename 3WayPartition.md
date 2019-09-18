Also known as Dutch National Flag problem, the algorithm partitions an array into 3 groups based on their relation with a given mid value:
array elements smaller than the mid value will be in the first range, followed by a subarray of mid value itself, followed by array
elements larger than the mid value.


```
# The following pseudocode for three-way partitioning assumes zero-based array indexing. 
# It uses three indices i, j and n, maintaining the invariant that i ≤ j.

# n holds the lower boundary of numbers greater than mid.

# j is the position of the number under consideration. And i is the boundary for
# the numbers less than the mid value.

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



# Ref
* https://en.wikipedia.org/wiki/Dutch_national_flag_problem
