//
//  minimumOneBitOperations.cpp
//  leetcode
//
//  Created by Song Ding on 3/4/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minimumOneBitOperations {
/*
// TODO: copy problem statement here
 1611. Minimum One Bit Operations to Make Integers Zero My SubmissionsBack to Contest
 User Accepted: 291
 User Tried: 632
 Total Accepted: 312
 Total Submissions: 1142
 Difficulty: Hard
 Given an integer n, you must transform it into 0 using the following operations any number of times:

 Change the rightmost (0th) bit in the binary representation of n.
 Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0.
 Return the minimum number of operations to transform n into 0.

  

 Example 1:

 Input: n = 0
 Output: 0
 Example 2:

 Input: n = 3
 Output: 2
 Explanation: The binary representation of 3 is "11".
 "11" -> "01" with the 2nd operation since the 0th bit is 1.
 "01" -> "00" with the 1st operation.
 Example 3:

 Input: n = 6
 Output: 4
 Explanation: The binary representation of 6 is "110".
 "110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
 "010" -> "011" with the 1st operation.
 "011" -> "001" with the 2nd operation since the 0th bit is 1.
 "001" -> "000" with the 1st operation.
 Example 4:

 Input: n = 9
 Output: 14
 Example 5:

 Input: n = 333
 Output: 393
  

 Constraints:

 0 <= n <= 109
*/
class Solution {
public:
    // TODO: copy function signature here
    int minimumOneBitOperations(int n) {
        bitset<32> src(n);
        unordered_map<bitset<32>, unordered_map<bitset<32>,int>> memo;
        return dfs(src, 0, memo);
    }
    // dst is 1000000..000 or just 0
    int dfs(bitset<32> src, bitset<32> dst, unordered_map<bitset<32>,unordered_map<bitset<32>,int>>& memo) {
        if (memo.count(src) && memo[src].count(dst)) {
            return memo[src][dst];
        }
        int res = 0, i = 31;
        for (; i >= 0 && src[i] == dst[i]; --i) {
        }
        if (i<0) {
            res = 0;
        } else if (i == 0) {
            res = 1;
        } else {
            // src[i] = 1, dst[i] = 0
            if (src[i]) {
                bitset<32> ns(src), nd(0);
                ns <<= 32-i;
                ns >>= 32-i;
                nd[i-1] = 1;
                res = dfs(ns, nd, memo) + 1 + dfs(nd, 0, memo);
            } else { // src[i] = 0 && dst[i] = 1, then dst[i-1..0] = 0
                bitset<32> ns(src), nd(0);
                ns <<= 32-i;
                ns >>= 32-i;
                nd[i-1] = 1;
                res = dfs(src, nd, memo) + 1 + dfs(nd, 0, memo);
            }
        }
        return memo[src][dst] = res;
        
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        int n;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {333},
    };
    // TODO: provide expected results here
    vector<int> answers {
        393,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minimumOneBitOperations::Solution().minimumOneBitOperations(dp.n);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
