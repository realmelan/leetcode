// countPalindromicSubsequences.cpp
// leetcode
//
// Created by  Song Ding on 9/3/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace countPalindromicSubsequences {
/*
// TODO: copy problem statement here
 730. Count Different Palindromic Subsequences
 Hard
 
 337
 
 35
 
 Favorite
 
 Share
 Given a string S, find the number of different non-empty palindromic subsequences in S, and return that number modulo 10^9 + 7.
 
 A subsequence of a string S is obtained by deleting 0 or more characters from S.
 
 A sequence is palindromic if it is equal to the sequence reversed.
 
 Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.
 
 Example 1:
 Input:
 S = 'bccb'
 Output: 6
 Explanation:
 The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
 Note that 'bcb' is counted only once, even though it occurs twice.
 Example 2:
 Input:
 S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
 Output: 104860361
 Explanation:
 There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.
 Note:
 
 The length of S will be in the range [1, 1000].
 Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
 */

class Solution {
public:
    static constexpr int M = 1000000007;
    int countPalindromicSubsequences(string S) {
        int n = S.size();
        vector<vector<long>> dp(n, vector<long>(n, -1));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
            if (i+1<n) {
                dp[i][i+1] = 2;
            }
        }
        return dfs(0, n-1, S, dp);
    }
    long dfs(int i, int j, const string& s, vector<vector<long>>& dp) {
        if (i > j) {
            return 0;
        } else if (dp[i][j] != -1) {
            return dp[i][j];
        }
        long res = 0;
        if (s[i] == s[j]) {
            int p = i+1, q = j-1;
            while (p <= q && s[p] != s[i]) {
                ++p;
            }
            while (p <= q && s[q] != s[i]) {
                --q;
            }
            if (p > q) {
                res = (dfs(i+1,j-1, s, dp) * 2 + 2)%M; // 'a'....'a'
            } else if (p < q) {
                res = (dfs(i+1,j-1,s,dp) * 2 + M - dfs(p+1, q-1, s, dp)) % M; // 'a'...'a'xxx'a'...'a'
            } else {
                res = (dfs(i+1,j-1,s,dp) * 2 + 1) % M; // 'a'...'a'...'a'
            }
        } else {
            res = (dfs(i, j-1, s, dp) + dfs(i+1, j, s, dp) + M - dfs(i+1, j-1, s, dp))%M;
        }
        dp[i][j] = res;
        return res;
    }
    /**
     * let cnt(i,j,ch) = # of uniq palindromic sequences in S[i,j] with the outer most
     * character = ch.
     *  then cnt(i,j,ch) = cnt(i,j-1,ch) or cnt(i+1,j,ch) if S[i] != S[j] || S[i] != ch
     *  else (cnt(i,j,ch) = cnt(i+1,j-1,a)+cnt(i+1,j-1,b)+cnt(i+1,j-1,c)+cnt(i+1,j-1,d)
     *    note, add 2 to cnt(i,j,ch) for "ch", and "chch"
     *
     * see https://leetcode.com/problems/count-different-palindromic-subsequences/discuss/109507/Java-96ms-DP-Solution-with-Detailed-Explanation
     * the solution in the link doesn't require the condition of just 4 characters.
     * this solution TLE now.
     */
    int countPalindromicSubsequences2(string S) {
        int n = S.size();
        vector<vector<long>> cur(n, vector<long>(4, 0));
        for (int i = 0; i < n; ++i) {
            ++cur[i][S[i] - 'a'];
        }
        
        vector<vector<long>> prev(n, vector<long>(4, 0));
        for (int k = 2; k <= n; ++k) {
            vector<vector<long>> next(n-k+1, vector<long>(4, 0));
            for (int i = 0; i+k <= n; ++i) {
                char fc = S[i];
                char lc = S[i+k-1];
                if (fc != lc) {
                    for (int ci = 0; ci < 4; ++ci) {
                        next[i][ci] = cur[i][ci];
                    }
                    // handle lc
                    next[i][lc-'a'] = cur[i+1][lc-'a'];
                } else {
                    long sum = 0;
                    for (int ci = 0; ci < 4; ++ci) {
                        next[i][ci] = prev[i+1][ci];
                        sum += prev[i+1][ci];
                    }
                    // deal next[i][ch]
                    // as <fc>...<lc> has at least 3 characters, <fc> and <fc><fc> should be added separately.
                    next[i][fc-'a'] = (sum+2) % mod;
                }
            }
            
            prev.swap(cur);
            cur.swap(next);
        }
        long res = 0;
        for (int ci = 0; ci < 4; ++ci) {
            res += cur[0][ci];
        }
        return res % mod;
    }

private:
    const long mod = 1000000007;
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string S;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{"bccb"},
        {"aab"},
        {"abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"},
        {"a"},
    };

    vector< int > answers {
        6,
        3,
        104860361,
        
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = countPalindromicSubsequences::Solution().countPalindromicSubsequences(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
