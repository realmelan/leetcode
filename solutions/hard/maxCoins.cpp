// maxCoins.cpp
// leetcode
//
// Created by  Song Ding on 9/24/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxCoins {
/*
// TODO: copy problem statement here
 312. Burst Balloons
 Hard
 
 1574
 
 49
 
 Favorite
 
 Share
 Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
 
 Find the maximum coins you can collect by bursting the balloons wisely.
 
 Note:
 
 You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
 Example:
 
 Input: [3,1,5,8]
 Output: 167
 Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
 coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
 */

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        return maxCoins_dp(nums);
        //return maxCoins_dp_slower(nums);
        //return maxCoins_dfs_slow(nums);
    }
    /**
     * let dp[i][j] = max coins collected to burst balloons i+1 to j-1,
     * i and j burst after all balloons from i+1 to j-1.
     *
     * then dp[i][j] = max(dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j]) for k in [i+1,j-1]
     *
     * and final result is dp[0][n-1], but we have to append 1 at both ends.
     * https://leetcode.com/problems/burst-balloons/discuss/76228/Share-some-analysis-and-explanations
     */
    int maxCoins_dp(vector<int>& nums) {
        int n = nums.size();
        vector<int> nv;
        nv.reserve(n+2);
        nv.push_back(1);
        for (auto i : nums) {
            if (i) {
                nv.push_back(i);
            }
        }
        nv.push_back(1);
        n = nv.size();
        
        vector<vector<int>> dp(n, vector<int>(n,0));
        for (int k = 3; k <= n; ++k) {
            for (int i = 0; i <= n-k; ++i) {
                for (int j = i+1; j < i+k-1; ++j) {
                    dp[i][i+k-1] = max(dp[i][i+k-1],
                                       nv[i]*nv[j]*nv[i+k-1]+dp[i][j]+dp[j][i+k-1]);
                }
            }
        }
        return dp[0][n-1];
    }
    
    int maxCoins_dp_slower(vector<int>& nums) {
        int n = nums.size();
        vector<int> nv;
        nv.reserve(n);
        for (auto i : nums) {
            if (i) {
                nv.push_back(i);
            }
        }
        n = nv.size();
        if (n <= 0) {
            return 0;
        }
        vector<vector<unordered_map<int,unordered_map<int, int>>>> dp(n);
        for(auto& v : dp) {
            v.resize(n);
        }
        vector<unordered_set<int>> left(n), right(n);
        left[0].insert(1);
        for (int i = 1; i < n; ++i) {
            left[i] = left[i-1];
            left[i].insert(nv[i-1]);
        }
        right[n-1].insert(1);
        for (int i = n-2; i >= 0; --i) {
            right[i] = right[i+1];
            right[i].insert(nv[i+1]);
        }
        for (int k = 1; k <= n; ++k) {
            for (int i = 0; i <= n-k; ++i) {
                int j = i+k-1;
                for (int e = i; e <= j; ++e) {
                    
                    for (auto ls : left[i]) {
                        for (auto rs : right[i]) {
                            int t = ls * rs * nv[e];
                            if (e > i) {
                                t += dp[i][e-1][ls][nv[e]];
                            }
                            if (e < j) {
                                t += dp[e+1][j][nv[e]][rs];
                            }
                            dp[i][j][ls][rs] = max(dp[i][j][ls][rs], t);
                        }
                    }
                }
            }
        }
        return dp[0][n-1][1][1];
    }
    /**
     * let dp[l][r][ls][rs] = max coins to burst l to r with ls at the left side(exclusive)
     * and rs at the right side(exclusive)
     * then
     *  dp[l][r][ls][rs] = max(dp[l][k-1][lb][k]+dp[k+1][r][k][rb]+ls*nums[k]*rs) for k in l to r.
     */
    int maxCoins_dfs_slow(vector<int>& nums) {
        int n = nums.size();
        vector<int> nv;
        nv.reserve(n);
        for (auto i : nums) {
            if (i) {
                nv.push_back(i);
            }
        }
        n = nv.size();
        if (n <= 0) {
            return 0;
        }
        vector<vector<unordered_map<int,unordered_map<int, int>>>> memo(n);
        for (auto& v : memo) {
            v.resize(n);
        }
        return dfs(0,n-1,1,1, nv, memo);
    }

private:
    int dfs(int l, int r, int ls, int rs, vector<int>& nums, vector<vector<unordered_map<int,unordered_map<int, int>>>>& memo) {
        if (memo[l][r][ls][rs] != 0) {
            return memo[l][r][ls][rs];
        }
        if (l == r) {
            return nums[l] * ls * rs;
        }
        int res = 0;
        // nums[k] is the last one to burst
        for (int k = l; k <= r; ++k) {
            int t = nums[k] * ls * rs;
            if (k-1 >= l) {
                t += dfs(l,k-1,ls,nums[k],nums, memo);
            }
            if (k+1 <= r) {
                t += dfs(k+1,r,nums[k],rs, nums, memo);
            }
            res = max(res, t);
        }
        memo[l][r][ls][rs] = res;
        return res;
    }
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
        {{}},
        {{3,1,5,8}},
        {{4,8,5,1,7,7,3,4,9,8,4,2,1,9,7,8,6,2,5,9,9,7,2,9,7,7,8,9,2,6,8,1,5,2,3,9,0,9,1,2,9,0,9,3,3,6,4}},
    };

    vector< int > answers {
        0,
        167,
        16250,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxCoins::Solution().maxCoins(dp.nums);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
