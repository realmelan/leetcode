//
//  numWays.cpp
//  leetcode
//
//  Created by Song Ding on 9/11/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace numWays {
/*
// TODO: copy problem statement here
 1269. Number of Ways to Stay in the Same Place After Some Steps
 Hard

 275

 17

 Add to List

 Share
 You have a pointer at index 0 in an array of size arrLen. At each step, you can move 1 position to the left, 1 position to the right in the array or stay in the same place  (The pointer should not be placed outside the array at any time).

 Given two integers steps and arrLen, return the number of ways such that your pointer still at index 0 after exactly steps steps.

 Since the answer may be too large, return it modulo 10^9 + 7.

  

 Example 1:

 Input: steps = 3, arrLen = 2
 Output: 4
 Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
 Right, Left, Stay
 Stay, Right, Left
 Right, Stay, Left
 Stay, Stay, Stay
 Example 2:

 Input: steps = 2, arrLen = 4
 Output: 2
 Explanation: There are 2 differents ways to stay at index 0 after 2 steps
 Right, Left
 Stay, Stay
 Example 3:

 Input: steps = 4, arrLen = 2
 Output: 8
  

 Constraints:

 1 <= steps <= 500
 1 <= arrLen <= 10^6
*/
class Solution {
public:
    // TODO: copy function signature here
    int numWays(int steps, int arrLen) {
        vector<long> ways(2, 0);
        ways[1] = 1;
        for (int k = 0; k < steps; ++k) {
            vector<long> nways(min((int)ways.size()+1, arrLen+1));
            for (int i = min((int)ways.size(), arrLen); i>= 1; --i) {
                nways[i] = (ways[i-1] + (i<ways.size() ? ways[i]:0) + (i<ways.size()-1 ? ways[i+1]:0))%1000000007;
            }
            ways.swap(nways);
        }
        return ways[1];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        int steps;
        int arrLen;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {3,2},
        {2,4},
        {4,2},
        {434,291270}
    };
    // TODO: provide expected results here
    vector<int> answers {
        4,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numWays::Solution().numWays(dp.steps, dp.arrLen);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
