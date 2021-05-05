//
//  findTargetSumWays.cpp
//  leetcode
//
//  Created by Song Ding on 9/8/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace findTargetSumWays {
/*
// TODO: copy problem statement here
 494. Target Sum
 Medium

 2958

 120

 Add to List

 Share
 You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

 Find out how many ways to assign symbols to make sum of integers equal to target S.

 Example 1:

 Input: nums is [1, 1, 1, 1, 1], S is 3.
 Output: 5
 Explanation:

 -1+1+1+1+1 = 3
 +1-1+1+1+1 = 3
 +1+1-1+1+1 = 3
 +1+1+1-1+1 = 3
 +1+1+1+1-1 = 3

 There are 5 ways to assign symbols to make the sum of nums be target 3.
  

 Constraints:

 The length of the given array is positive and will not exceed 20.
 The sum of elements in the given array will not exceed 1000.
 Your output answer is guaranteed to be fitted in a 32-bit integer.
*/
class Solution {
public:
    // TODO: copy function signature here
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size();
        vector<unordered_map<int,int>> dp(n+1);
        return dfs(S, n-1, nums, dp);
        
    }
    int dfs(long s, int i, vector<int>& nums, vector<unordered_map<int,int>>& dp) {
        if (dp[i].count(s)) {
            return dp[i][s];
        } else if (i == 0) {
            return (s == nums[0] ? 1 : 0) + (-s == nums[0] ? 1 : 0);
        }
        int res = dfs(s+nums[i], i-1, nums, dp) + dfs(s-nums[i], i-1, nums, dp);
        dp[i][s] = res;
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nums;
        int S;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{1,1,1,1,1},3},
        {{0,0,0,0,0,0,0,0,1},1}
    };
    // TODO: provide expected results here
    vector<int> answers {
        5,
        256
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findTargetSumWays::Solution().findTargetSumWays(dp.nums, dp.S);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
