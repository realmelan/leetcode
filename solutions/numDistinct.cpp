//
//  numDistinct.cpp
//  leetcode
//
//  Created by Song Ding on 9/3/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace numDistinct {
/*
// TODO: copy problem statement here
 115. Distinct Subsequences
 Hard

 1399

 57

 Add to List

 Share
 Given a string S and a string T, count the number of distinct subsequences of S which equals T.

 A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

 It's guaranteed the answer fits on a 32-bit signed integer.

 Example 1:

 Input: S = "rabbbit", T = "rabbit"
 Output: 3
 Explanation:
 As shown below, there are 3 ways you can generate "rabbit" from S.
 (The caret symbol ^ means the chosen letters)

 rabbbit
 ^^^^ ^^
 rabbbit
 ^^ ^^^^
 rabbbit
 ^^^ ^^^
 Example 2:

 Input: S = "babgbag", T = "bag"
 Output: 5
 Explanation:
 As shown below, there are 5 ways you can generate "bag" from S.
 (The caret symbol ^ means the chosen letters)

 babgbag
 ^^ ^
 babgbag
 ^^    ^
 babgbag
 ^    ^^
 babgbag
   ^  ^^
 babgbag
     ^^^
*/
class Solution {
public:
    // TODO: copy function signature here
    int numDistinct(string s, string t) {
        int n1 = s.size(), n2 = t.size();
        vector<vector<int>> dp(n2+1, vector<int>(n1+1, 0));
        for (int i = 0; i <= n1; ++i) {
            dp[0][i] = 1;
        }
        for (int i = 0; i < n2; ++i) {
            for (int j = i; j < n1; ++j) {
                dp[i+1][j+1] = dp[i+1][j];
                if (t[i] == s[j]) {
                    dp[i+1][j+1] += dp[i][j];
                }
            }
        }
        return dp[n2][n1];
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string s;
        string t;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"rabbbit", "rabbit"},
        {"babgbag", "bag"},
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
        5,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numDistinct::Solution().numDistinct(dp.s, dp.t);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
