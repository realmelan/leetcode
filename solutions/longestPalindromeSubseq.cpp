// longestPalindromeSubseq.cpp
// leetcode
//
// Created by  Song Ding on 10/23/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestPalindromeSubseq {
/*
// TODO: copy problem statement here
 516. Longest Palindromic Subsequence
 Medium

 1163

 144

 Favorite

 Share
 Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

 Example 1:
 Input:

 "bbbab"
 Output:
 4
 One possible longest palindromic subsequence is "bbbb".
 Example 2:
 Input:

 "cbbd"
 Output:
 2
 One possible longest palindromic subsequence is "bb".
 */

class Solution {
public:
    /**
     * let dp[i][j] = # of longest palindrome sequence for substring of length i starting at j
     * then dp[i][j] = max(dp[i-2][j+1] +2 if s[j]=s[j+i-1], dp[i-1][j], dp[i-1][j+1])
     */
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n+1);
        dp[0].resize(n+1, 0);
        dp[1].resize(n, 1);
        for (int k = 2; k <= n; ++k) {
            dp[k].resize(n-k+1);
            for (int i = 0; i <= n-k; ++i) {
                dp[k][i] = max(dp[k-1][i], dp[k-1][i+1]);
                if (s[i] == s[i+k-1]) {
                    dp[k][i] = max(dp[k][i], dp[k-2][i+1]+2);
                }
            }
        }
        return dp[n][0];
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string s;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"bbbab"},
        {"cbbd"},
    };

    vector< int > answers {
        4,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = longestPalindromeSubseq::Solution().longestPalindromeSubseq(dp.s);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
