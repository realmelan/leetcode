# Median
In statistics and probability theory, a median is a value separating the higher half from the lower half of a data sample, a population, or a probability distribution. For a data set, it may be thought of as "the middle" value. 

# P1: Median of two sorted array
It means we need to divide each array into left and right halves, say L1, R1, L2, R2, such that L1 <= R2 and L2 <= R1 and #L1 + #L2 is about half of the total # of elements of the two arrays.
Now since the total # of elements of L1 + L2 is fixed, given a divide, L1, in the first array, we are able to determine L2 in the second array.

Then we can use binary search to locate L1, say currebt divide is l1, and L1 > R2, it means l1 should be move left; if L2 > R1 then l1 should be move right; else we found the right divide point.
```c++
int median(vector<int>& arr1, vector<int>& arr2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if (n1 > n2) {
            swap(nums1,nums2);
            swap(n1, n2);
        }
        int k = (n1+n2) / 2;
        int l = 0, r = n1;
        while (l <= r) {
            int m = l + (r-l) / 2;
            int m2 = k - m;
            int l1 = m > 0 ? nums1[m-1] : INT_MIN;
            int r1 = m < n1 ? nums1[m] : INT_MAX;
            int l2 = m2 > 0 ? nums2[m2-1] : INT_MIN;
            int r2 = m2 < n2 ? nums2[m2] : INT_MAX;
            if (l1 > r2) {
                r = m - 1;
            } else if (l2 > r1) {
                l = m + 1;
            } else {
                if ((n1+n2)&1) {
                    return min(r1,r2);
                } else {
                    return (max(l1,l2)+min(r1,r2))/2.0;
                }
            }
        }
        return -1;
}
```


# P2: Median of a large data cluster
Say we want to find media number of a list of large sparse number array stored on different machines. Given a number m, we can ask these machines the # of elements smaller than m, and if the count is smaller than n/2, then we should consider ranges larger than m. So, the search space would be [min, max] of all the numbers on these machines, and the time cost is O(lg(max-min)).

If these numbers are very sparse, meaning # of total numbers << (max-min), how can we reduce the # of searches?

The problem with plain mid value of m = (l+r)/2 is that m might not be an existing element of the array. If we can find an existing pivot element between l and r, then the search space would be # of array elements. One simple way to get such pivot elements would be random element between l and r.

# Problems:
* https://leetcode.com/problems/median-of-two-sorted-arrays/
