// shortestCommonSupersequence.cpp
// leetcode
//
// Created by  Song Ding on 9/15/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestCommonSupersequence {
/*
// TODO: copy problem statement here
 1092. Shortest Common Supersequence
 Hard
 
 176
 
 6
 
 Favorite
 
 Share
 Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.  If multiple answers exist, you may return any of them.
 
 (A string S is a subsequence of string T if deleting some number of characters from T (possibly 0, and the characters are chosen anywhere from T) results in the string S.)
 
 
 
 Example 1:
 
 Input: str1 = "abac", str2 = "cab"
 Output: "cabac"
 Explanation:
 str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
 str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
 The answer provided is the shortest such string that satisfies these properties.
 
 
 Note:
 
 1 <= str1.length, str2.length <= 1000
 str1 and str2 consist of lowercase English letters.
 */

class Solution {
public:
    /**
     * https://leetcode.com/problems/shortest-common-supersequence/discuss/312710/C%2B%2BPython-Find-the-LCS
     *
     * first find longest common sequence, then copy characters form A and B that are not in common sequence!
     */
    string shortestCommonSupersequence(string& A, string& B) {
        int i = 0, j = 0;
        string res = "";
        for (char c : lcs(A, B)) {
            while (A[i] != c)
                res += A[i++];
            while (B[j] != c)
                res += B[j++];
            res += c, i++, j++;
        }
        return res + A.substr(i) + B.substr(j);
    }
    
    string lcs(string& A, string& B) {
        int n = A.size(), m = B.size();
        vector<vector<string>> dp(n + 1, vector<string>(m + 1, ""));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (A[i] == B[j])
                    dp[i + 1][j + 1] = dp[i][j] + A[i];
                else
                    dp[i + 1][j + 1] = dp[i + 1][j].size() > dp[i][j + 1].size() ?  dp[i + 1][j] : dp[i][j + 1];
        return dp[n][m];
    }
    /**
     * let dp(i,j) = set of shortest super string for str1(0..i) and str2(0..j).
     * then dp(i,j) = dp(i-1,j-1)+str1[i] if str1[i]==str2[j]
     *  or dp(i,j) = shorter of dp(i,j-1)+str2[j] and dp(i-1,j)+str1[i]
     *
     * however string computation would be time consuming, should construct result
     * based on integer state.
     */
    string shortestCommonSupersequence1(string str1, string str2) {
        // intermost vector: 0=>len, 1=>which string contributes the char(0=>str1, 1=>str2, 2=>both)
        struct st {
            int len;
            int who;
            int idx;
        };
        int n1 = str1.size();
        int n2 = str2.size();
        vector<vector<struct st>> dp(n1+1, vector<struct st>(n2+1));
        for (int i = 1; i <= n2; ++i) {
            dp[0][i] = {i,1,i-1};
        }
        for (int i = 1; i <= n1; ++i) {
            dp[i][0] = {i,0,i-1};
        }
        dp[0][0] = {0,-1,-1};
        
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (str1[i-1] == str2[j-1]) {
                    dp[i][j] = {dp[i-1][j-1].len+1,2,i-1};
                } else {
                    int len1 = dp[i-1][j].len;
                    int len2 = dp[i][j-1].len;
                    if (len1 <= len2) {
                        dp[i][j] = {len1+1, 0, i-1};
                    } else {
                        dp[i][j] = {len2+1, 1, j-1};
                    }
                }
            }
        }
        
        string res;
        int i = n1;
        int j = n2;
        int who = dp[i][j].who;
        int idx = dp[i][j].idx;
        while (idx >= 0) {
            if (who == 2 || who == 0) {
                res.push_back(str1[idx]);
                --i;
                if (who == 2) {
                    --j;
                }
            } else {
                res.push_back(str2[idx]);
                --j;
            }
            who = dp[i][j].who;
            idx = dp[i][j].idx;
        }
        reverse(res.begin(), res.end());
        return res;
    }
    
    /**
     * let dp(i,j) = set of shortest super string for str1(0..i) and str2(0..j).
     * then dp(i,j) = dp(i-1,j-1)+str1[i] if str1[i]==str2[j]
     *  or dp(i,j) = shorter of dp(i,j-1)+str2[j] and dp(i-1,j)+str1[i]
     *
     * however string computation would be time consuming, should construct result
     * based on integer state.
     */
    string shortestCommonSupersequence2(string str1, string str2) {
        int n1 = str1.size();
        int n2 = str2.size();
        vector<vector<unordered_set<string>>> dp(n1+1, vector<unordered_set<string>>(n2+1));
        dp[0][0].insert("");
        for (int i = 1; i <= n2; ++i) {
            dp[0][i].insert(str2.substr(0, i));
        }
        for (int i = 1; i <= n1; ++i) {
            dp[i][0].insert(str1.substr(0, i));
        }
        
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (str1[i-1] == str2[j-1]) {
                    for (auto s : dp[i-1][j-1]) {
                        s.push_back(str1[i-1]);
                        dp[i][j].insert(s);
                    }
                } else {
                    int len1 = dp[i-1][j].begin()->size();
                    int len2 = dp[i][j-1].begin()->size();
                    if (len1 <= len2) {
                        for (auto s : dp[i-1][j]) {
                            s.push_back(str1[i-1]);
                            dp[i][j].insert(s);
                        }
                    }
                    if (len2 <= len1) {
                        for (auto s : dp[i][j-1]) {
                            s.push_back(str2[j-1]);
                            dp[i][j].insert(s);
                        }
                    }
                }
            }
        }
        return *(dp[n1][n2].begin());
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string str1;
        string str2;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"abac", "cab"},
        {"aaaaaaaa","aaaaaaaa"},
        {"bcaaacbbbcbdcaddadcacbdddcdcccdadadcbabaccbccdcdcbcaccacbbdcbabb", "dddbbdcbccaccbababaacbcbacdddcdabadcacddbacadabdabcdbaaabaccbdaa"}
    };

    vector< string > answers {
        "cabac"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = shortestCommonSupersequence::Solution().shortestCommonSupersequence(dp.str1, dp.str2);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
