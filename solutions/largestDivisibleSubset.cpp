// largestDivisibleSubset.cpp
// leetcode
//
// Created by  Song Ding on 10/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace largestDivisibleSubset {
/*
// TODO: copy problem statement here
 368. Largest Divisible Subset
 Medium

 657

 32

 Favorite

 Share
 Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies:

 Si % Sj = 0 or Sj % Si = 0.

 If there are multiple solutions, return any subset is fine.

 Example 1:

 Input: [1,2,3]
 Output: [1,2] (of course, [1,3] will also be ok)
 Example 2:

 Input: [1,2,4,8]
 Output: [1,2,4,8]
 */

class Solution {
public:
    /**
     * if we order this kind of subset, then larger ones are multiples of smallers one,
     * that is, A[i] is a multiple of A[i-1].
     * then this likes walk down a tree from the possible root, and get the longest path.
     * however, there might be several roots, and some trees may share nodes, this memoization
     * or dp can be used.
     *  this is O(n^2).
     */
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        int resi = -1;
        vector<int> dp(n, 0);
        vector<int> next(n, -1);
        for (int i = n-1; i >= 0; --i) {
            for (int j = i+1; j < n; ++j) {
                if (nums[j]%nums[i] == 0) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j]+1;
                        next[i] = j;
                    }
                }
            }

            if (res < dp[i]) {
                res = dp[i];
                resi = i;
            }
        }
        // construct from next and resi
        vector<int> resv;
        int i = resi;
        while (i != -1) {
            resv.push_back(nums[i]);
            i = next[i];
        }
        return resv;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nums;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3}},
        {{1,2,4,8}},
    };

    vector< vector<int> > answers {
        {1,2},
        {1,2,4,8},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = largestDivisibleSubset::Solution().largestDivisibleSubset(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
