# Difference Array

Given an array of numbers, we can construct a new array by replacing each element by the difference between itself and the previous element, except for the first element, which we simply ignore. This is called the difference array, because it contains the first differences of the original array. We will denote the difference array of array A by D(A). For example, the difference array of A = [9, 2, 6, 3, 1, 5, 0, 7] is D(A) = [2-9, 6-2, 3-6, 1-3, 5-1, 0-5, 7-0], or [-7, 4, -3, -2, 4, -5, 7].

We see that the difference array can be computed in linear time from the original array, and is shorter than the original array by one element. Here are implementations in C and Haskell. (Note that the Haskell implementation actually takes a list, but returns an array.)

```c++
// D must have enough space for n-1 ints
void difference_array(int* A, int n, int* D)
{
    for (int i = 0; i < n-1; i++)
        D[i] = A[i+1] - A[i];
}
```

## How difference array can be used
Difference array can solve range update problems. For example, for an array A, if there are k range updates, each being [i,j,val], to add val to A[i] to A[j]. Now we need to know the final result array.

Naive solution would be loop from A[i] to A[j] and add val to the array elements. This takes O(n) steps, and total cost would be O(kn).

But if we maintain a difference array, D[i] = A[i]-A[i-1], then the update(i,j,val) can be done in O(1) time, that is D[i]+=val, D[j+1]-=val. To get final result array, a loop from D[0] to D[n-1] is need. So total cost would be O(n+k).


### Implict use of difference array
Normally there will not be such direct use of difference array. But there are cases, range update is expressed in different ways. for instance:
* class starts at time a, ends at time b. How many classrooms are needed?
* an interval starts at a, ends at b. What's max overlap?
* a rotation at position i of array A changes score at one or two boundary. Which position gives largest score?

## Problems:
* https://leetcode.com/problems/minimum-moves-to-make-array-complementary/
* https://leetcode.com/problems/smallest-rotation-with-highest-score/


