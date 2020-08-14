# Sliding window
There are 2 different types of problems:
* Find a maximum, minimum  or nearest larger/smaller within a bounded range
* longest or shortest subarray/substring that matches certain constraints.

## Type 1, Monotonic queue
For type 1, Monotonic queue can be used, which achieves O(n) efficiency. 
A monotonic queue provides benefit that farther away useless elements are discarded
as they are inferior to the element that's closer to current position.

### Leetcode 1425. Constrained Subsequence Sum
Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.

A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.

```c++
int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        // g(i): max seq sum up to i, containing nums[i]
        // g(i) = max(g[i-k..i-1]) + nums[i]
        // monotonic queue is able to find max(g[i-k..i-1]) in O(1).
        // f(i): max seq sum up to i, not necessarily containing nums[i]
        vector<int> f(n, 0), g(n, 0);
        g[0] = nums[0];
        f[0] = g[0];
        deque<pair<int,int>> q;
        q.emplace_back(g[0], 0);
        for (int i = 1; i < n; ++i) {
            while (q.size() && i - q.front().second > k) {
                q.pop_front();
            }
            g[i] = nums[i];
            if (q.size() && q.front().first > 0) {
                g[i] += q.front().first;
            }
            while (q.size() && q.back().first <= g[i]) {
                q.pop_back();
            }
            q.emplace_back(g[i], i);
            f[i] = max(g[i], f[i-1]);
        }
        return f[n-1];
    }
```

## Type 2, Two pointer
For type 2, use two pointer technique, right pointer to add counters and left pointer
to decrease counter. When conditions are met, left/right pointers form a valid range.

### Leetcode 1248, Count Number of Nice Subarrays
Given an array of integers nums and an integer k. A subarray is called nice if there are k odd numbers on it.
Return the number of nice sub-arrays.
```c++
int numberOfSubarrays(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k-1);
    }
    int atMost(vector<int>& nums, int K) {
        int n = nums.size();
        int l = 0, r = 0, k = 0, res = 0;
        while (r < n) {
            if (nums[r++] &1) {
                ++k;
            }
            while (k > K) {
                if (nums[l++] &1) {
                    --k;
                }
            }
            res += r - l;
        }
        return res;
    }
```

# Reference
* https://leetcode.com/problems/subarrays-with-k-different-integers/discuss/523136/JavaC%2B%2BPython-Sliding-Window
* https://github.com/xiaoylu/leetcode_category/blob/master/MonotonicQueue/Readme.md
