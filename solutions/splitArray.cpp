//
//  splitArray.cpp
//  leetcode
//
//  Created by Song Ding on 9/12/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace splitArray {
/*
// TODO: copy problem statement here
 410. Split Array Largest Sum
 Hard

 2001

 78

 Add to List

 Share
 Given an array nums which consists of non-negative integers and an integer m, you can split the array into m non-empty continuous subarrays.

 Write an algorithm to minimize the largest sum among these m subarrays.

  

 Example 1:

 Input: nums = [7,2,5,10,8], m = 2
 Output: 18
 Explanation:
 There are four ways to split nums into two subarrays.
 The best way is to split it into [7,2,5] and [10,8],
 where the largest sum among the two subarrays is only 18.
 Example 2:

 Input: nums = [1,2,3,4,5], m = 2
 Output: 9
 Example 3:

 Input: nums = [1,4,4], m = 3
 Output: 4
  

 Constraints:

 1 <= nums.length <= 1000
 0 <= nums[i] <= 106
 1 <= m <= min(50, nums.length)
*/
class Solution {
public:
    // TODO: copy function signature here
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<int> dp(n, INT_MAX);
        for (int k = 1; k <= m; ++k) {
            vector<int> next(n, INT_MAX);
            for (int i = k-1; i < n; ++i) {
                int sum = 0;
                for (int j = i; j >= k-1; --j) {
                    sum += nums[j];
                    next[i] = min(next[i], max((j>=1 ? dp[j-1] : 0), sum));
                }
            }
            dp.swap(next);
        }
        return dp.back();
    }
    
    int splitArray2(vector<int>& nums, int m) {
        // invariant: result is in (l, r], and if we split nums into subarrays whose sum does not exceed
        // l, then # of subarrays will be >m; if we split nums int osubarrays whose sum doesn't exceed
        // r, then # of subarrys will be <=m;
        // so, final answer is r and exit condition is l+1=r
        int l = *max_element(begin(nums), end(nums))-1, r = accumulate(begin(nums), end(nums), 0);
        while (r-l > 1) {
            int mid = l + (r-l) / 2;
            int cnt = 1, t = 0;
            for (auto num : nums) {
                if (t + num > mid) {
                    ++cnt;
                    t = 0;
                }
                t += num;
            }
            if (cnt > m) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return r;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums;
        int m;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{7,2,5,10,8},2},
        {{1,2,3,4,5},2},
        {{1,4,4},3},
    };
    // TODO: provide expected results here
    vector<int> answers {
        18,
        9,
        4
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = splitArray::Solution().splitArray2(dp.nums, dp.m);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
