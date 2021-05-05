//
//  getLengthOfOptimalCompression.cpp
//  leetcode
//
//  Created by Song Ding on 3/25/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace getLengthOfOptimalCompression {
/*
// TODO: copy problem statement here
 1531. String Compression II My SubmissionsBack to Contest
 User Accepted: 112
 User Tried: 999
 Total Accepted: 121
 Total Submissions: 2563
 Difficulty: Hard
 Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".

 Notice that in this problem, we are not adding '1' after single characters.

 Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.

 Find the minimum length of the run-length encoded version of s after deleting at most k characters.

  

 Example 1:

 Input: s = "aaabcccd", k = 2
 Output: 4
 Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6. Deleting any of the characters 'a' or 'c' would at most decrease the length of the compressed string to 5, for instance delete 2 'a' then we will have s = "abcccd" which compressed is abc3d. Therefore, the optimal way is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of length 4.
 Example 2:

 Input: s = "aabbaa", k = 2
 Output: 2
 Explanation: If we delete both 'b' characters, the resulting compressed string would be "a4" of length 2.
 Example 3:

 Input: s = "aaaaaaaaaaa", k = 0
 Output: 3
 Explanation: Since k is zero, we cannot delete anything. The compressed string is "a11" of length 3.
  

 Constraints:

 1 <= s.length <= 100
 0 <= k <= s.length
 s contains only lowercase English letters.
*/
class Solution {
public:
    // TODO: copy function signature here
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(k+1,vector<int>(n,0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0, p = 0; j <= i+1; ++j) {
                if (j == i+1 || s[j] != s[p]) {
                    dp[0][i] += 1+len(j-p);
                    p = j;
                }
            }
        }
        for (int d = 1; d <= k; ++d) {
            for (int i = d; i < n; ++i) {
                dp[d][i] = min(dp[d-1][i], dp[d-1][i-1]);
                // skip 1 to d characters
                int j = i, cnt = d;
                while (j >= 0 && (s[j] == s[i] || cnt--)) {
                    dp[d][i] = min(dp[d][i], (j>=1?dp[cnt][j-1]:0)+1+len(i-j+1+cnt-d));
                    --j;
                }
            }
        }
        return dp[k][n-1];
    }
    int len(int x) {
        return x>=100 ? 3 : x>=10 ? 2 : x>=2 ? 1 : x>=1 ? 0 : -1;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string s;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"cbcaabbbbcbcb",6},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = getLengthOfOptimalCompression::Solution().getLengthOfOptimalCompression(dp.s, dp.k);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
