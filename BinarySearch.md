# How to write correct binary search code
Correct binary search has below 3 qualifications:
* gives right answer at termination
* it terminates
* handles special cases gracefully with simple code

# steps to write correct binary search code:
* identify the range for binary search, like [0, size-1] or [0, size], etc, depends on the problem statements. For example,
if the problem requires finding an insertion position, then a valid range might be [0,size], instead of [0, size-1], as we might need to
insert a number at the very end of the array.
* have loop invariant in mind, using the range, that the target position is in current range. During comparison of array elements
against target, consider how to change the lower bound and upper bound of current range, so that the invariant stays true.
* make sure the either lower bound or upper bound change at least by 1, so that current range would shrink at each iteration.
* determine whether to use lower < upper or lower <= upper as loop terminiation condition. This depends on how range is set up in step 1
and the invariant. For example, if the target position always exists, then lower < upper might be used, and result would be lower or upper
at loop termination; but if position might not exist, then lower <= upper seems a valid termination condition.

# code exmaple
Use below code example by Mike Taylor in "Writing correct code" to understand how to apply the steps in binary search
```c
int binary_search(const int a[], const int size, const int val) {
        int lower = 0;
        int upper = size-1;
        
        /* invariant: if a[i]==val for any i, then lower <= i <= upper */
        /* bound function: upper-lower+1 */
        while (lower <= upper) {
            int i = lower + (upper-lower)/2;
            if (val == a[i]) {
                return i;
            } else if (val < a[i]) {
                upper = i-1;
            } else { /* val > a[i] */
                lower = i+1;
            }
        }
        return -1;
    }
```

# reference
* https://reprog.wordpress.com/2010/04/25/writing-correct-code-part-1-invariants-binary-search-part-4a/
* https://zhu45.org/posts/2018/Jan/12/how-to-write-binary-search-correctly/
