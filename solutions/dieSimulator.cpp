//
//  dieSimulator.cpp
//  leetcode
//
//  Created by Song Ding on 9/14/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace dieSimulator {
/*
// TODO: copy problem statement here
 1223. Dice Roll Simulation
 Medium

 373

 120

 Add to List

 Share
 A die simulator generates a random number from 1 to 6 for each roll. You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times.

 Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls.

 Two sequences are considered different if at least one element differs from each other. Since the answer may be too large, return it modulo 10^9 + 7.

  

 Example 1:

 Input: n = 2, rollMax = [1,1,2,2,2,3]
 Output: 34
 Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.
 Example 2:

 Input: n = 2, rollMax = [1,1,1,1,1,1]
 Output: 30
 Example 3:

 Input: n = 3, rollMax = [1,1,1,2,2,3]
 Output: 181
  

 Constraints:

 1 <= n <= 5000
 rollMax.length == 6
 1 <= rollMax[i] <= 15
*/
class Solution {
public:
    // TODO: copy function signature here
    // https://leetcode.com/problems/dice-roll-simulation/discuss/403756/Java-Share-my-DP-solution
    int dieSimulator(int n, vector<int>& rollMax) {
        constexpr int M = 1000000007;
        // dp[i][j] = # of sequnces of length i and last number is j
        // then dp[i][j] = dp[i-1][0..5] - dp[i-rollMax[j]-1][0..5-j]
        vector<vector<long>> dp(n+1, vector<long>(7, 0));
        for (int i = 0; i < 6; ++i) {
            dp[1][i] = 1;
        }
        dp[1][6] = 6;
    
        for (int i = 2; i <= n; ++i) {
            long sum = 0;
            for (int j = 0; j < 6; ++j) {
                dp[i][j] = dp[i-1][6];
                if (i >= rollMax[j]+1) {
                    dp[i][j] -= (i > rollMax[j]+1) ? (dp[i-rollMax[j]-1][6]+M-dp[i-rollMax[j]-1][j])%M : 1;
                    dp[i][j] = (dp[i][j]+M)%M;
                }
                sum += dp[i][j];
                sum %= M;
            }
            dp[i][6] = sum;
        }
        return dp[n][6];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        int n;
        vector<int> rollMax;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {2,{1,1,2,2,2,3}},
        {2,{1,1,1,1,1,1}},
        {3,{1,1,1,2,2,3}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        34,
        30,
        181,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = dieSimulator::Solution().dieSimulator(dp.n, dp.rollMax);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
