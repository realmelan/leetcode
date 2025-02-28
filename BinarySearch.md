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

# How to choose pivot element
Say we want to find media number of a list of large sparse number array stored on different machines. Given a number m, we can ask these machines the # of elements smaller than m, and if the count is smaller than n/2, then we should consider ranges larger than m. So, the search space would be [min, max] of all the numbers on these machines, and the time cost is O(lg(max-min)).

If these numbers are very sparse, meaning # of total numbers << (max-min), how can we reduce the # of searches?

The problem with plain mid value of m = (l+r)/2 is that m might not be an existing element of the array. If we can find an existing pivot element between l and r, then the search space would be \# of array elements. One simple way to get such pivot elements would be random element between l and r.

# problems
## peak finder
* https://leetcode.com/problems/find-peak-element/submissions/
```c++
int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1;
        // invariant: nums[l-1] < nums[l] && nums[r] > nums[r+1]
        // when l=r, l(or r) is a peak.
        while (l < r) {
            int m = l + (r-l) / 2;
            if (nums[m] < nums[m+1]) {
                l = m+1;
            } else {
                r = m;
            }
        }
        return l;
    }
```

# reference
* https://reprog.wordpress.com/2010/04/25/writing-correct-code-part-1-invariants-binary-search-part-4a/
* https://zhu45.org/posts/2018/Jan/12/how-to-write-binary-search-correctly/
* https://liuzhenglaichn.gitbook.io/algorithm/binary-search
