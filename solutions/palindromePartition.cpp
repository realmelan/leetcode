//
//  palindromePartition.cpp
//  leetcode
//
//  Created by Song Ding on 9/12/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace palindromePartition {
/*
// TODO: copy problem statement here
 1278. Palindrome Partitioning III
 Hard

 307

 5

 Add to List

 Share
 You are given a string s containing lowercase letters and an integer k. You need to :

 First, change some characters of s to other lowercase English letters.
 Then divide s into k non-empty disjoint substrings such that each substring is palindrome.
 Return the minimal number of characters that you need to change to divide the string.

  

 Example 1:

 Input: s = "abc", k = 2
 Output: 1
 Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
 Example 2:

 Input: s = "aabbc", k = 3
 Output: 0
 Explanation: You can split the string into "aa", "bb" and "c", all of them are palindrome.
 Example 3:

 Input: s = "leetcode", k = 8
 Output: 0
  

 Constraints:

 1 <= k <= s.length <= 100.
 s only contains lowercase English letters.
*/
class Solution {
public:
    // TODO: copy function signature here
    int palindromePartition(string s, int k) {
        int n = s.size();
        // changes[i][j] = # of operations to change s[i..j] to palindrome
        vector<vector<int>> changes(n, vector<int>(n));
        for (int l = 1; l <= n; ++l) {
            for (int i = 0; i+l<=n; ++i) {
                int j = i+l-1;
                changes[i][j] = (s[i]==s[j] ? 0 : 1) + (i+1<j-1? changes[i+1][j-1] : 0);
            }
        }
        
        // dp[i] = # of operations to make s[0..i] to k palindromes.
        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            dp[i] = changes[0][i];
        }
        for (int ki = 2; ki <= k; ++ki) {
            vector<int> next(n, INT_MAX);
            for (int i = ki-1; i < n; ++i) {
                for (int j = i; j >= ki-1; --j) {
                    next[i] = min(next[i], dp[j-1]+changes[j][i]);
                }
            }
            dp.swap(next);
        }
        return dp.back();
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
        {"abc",2},
        {"aabbc",3},
        {"leetcode",8},
    };
    // TODO: provide expected results here
    vector<int> answers {
        1,
        0,
        0
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = palindromePartition::Solution().palindromePartition(dp.s, dp.k);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
