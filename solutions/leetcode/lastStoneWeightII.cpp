// lastStoneWeightII.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace lastStoneWeightII {
/*
// TODO: copy problem statement here
 1049. Last Stone Weight II
 Medium
 
 132
 
 3
 
 Favorite
 
 Share
 We have a collection of rocks, each rock has a positive integer weight.
 
 Each turn, we choose any two rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:
 
 If x == y, both stones are totally destroyed;
 If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
 At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)
 
 
 
 Example 1:
 
 Input: [2,7,4,1,8,1]
 Output: 1
 Explanation:
 We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
 we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
 we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
 we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.
 
 
 Note:
 
 1 <= stones.length <= 30
 1 <= stones[i] <= 100
 */

class Solution {
public:
    /**
     * This is equal to dividing the stones into two halves,
     * with the minimum different of sum of weights.
     *
     * Note, the upper bound of the minimum difference is max(stones).
     * let dp[i][j] = true if for stones[0..i] differce of j can be achieved.
     * note, different of j may be sum of stones[0..i
     *
     * then result is the minimum j if dp[n-1][j] is true.
     */
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sum = 0;
        vector<vector<bool>> dp(n);
        for (auto i : stones) {
            sum += i;
        }
        for (auto& v : dp) {
            v.resize(sum+1, false);
        }
        dp[0][stones[0]] = true;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= sum; ++j) {
                if (dp[i-1][j]) {
                    if (j > stones[i]) {
                        dp[i][j - stones[i]] = true;
                    } else {
                        dp[i][stones[i] - j] = true;
                    }
                    dp[i][stones[i] + j] = true;
                }
            }
        }
        for (int i = 0; i <= sum; ++i) {
            if (dp[n-1][i]) {
                return i;
            }
        }
        return sum;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> stones;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{2,7,4,1,8,1}}
    };

    vector< int > answers {
        1
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = lastStoneWeightII::Solution().lastStoneWeightII(dp.stones);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
