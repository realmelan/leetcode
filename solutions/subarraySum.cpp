// subarraySum.cpp
// leetcode
//
// Created by  Song Ding on 10/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace subarraySum {
/*
// TODO: copy problem statement here
 560. Subarray Sum Equals K
 Medium

 2623

 72

 Favorite

 Share
 Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

 Example 1:
 Input:nums = [1,1,1], k = 2
 Output: 2
 Note:
 The length of the array is in range [1, 20,000].
 The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].
 */

class Solution {
public:
    int subarraySum2(vector<int>& nums, int k) {
        int n = nums.size();
        int res = 0;
        
        vector<int> sum(n+1,0);
        unordered_map<int, int> cnt;
        ++cnt[0];
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1]+nums[i-1];
            int t = sum[i] - k;
            res += cnt[t];
            ++cnt[sum[i]];
        }
        return res;
    }
    
    /**
     * find accumulative sums of nums, and then for each accumulative sum,
     * check whether asum+k exists.
     *
     * Or: we can check asum-k as it already exists in accumulative sums.
     */
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sum(n+1,0);
        unordered_map<int, int> cnt;
        ++cnt[0];
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1]+nums[i-1];
            ++cnt[sum[i]];
        }
        int res = 0;
        for (int i = 0; i <= n; ++i) {
            --cnt[sum[i]];
            int t = sum[i] + k;
            res += cnt[t];
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,1,1},2}
    };

    vector< int > answers {
        2,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = subarraySum::Solution().subarraySum2(dp.nums, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
