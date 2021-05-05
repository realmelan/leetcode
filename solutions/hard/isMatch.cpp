// isMatch.cpp
// leetcode
//
// Created by  Song Ding on 7/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isMatch {
/*
// TODO: copy problem statement here
 44. Wildcard Matching
 Hard
 
 1115
 
 77
 
 Favorite
 
 Share
 Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.
 
 '?' Matches any single character.
 '*' Matches any sequence of characters (including the empty sequence).
 The matching should cover the entire input string (not partial).
 
 Note:
 
 s could be empty and contains only lowercase letters a-z.
 p could be empty and contains only lowercase letters a-z, and characters like ? or *.
 Example 1:
 
 Input:
 s = "aa"
 p = "a"
 Output: false
 Explanation: "a" does not match the entire string "aa".
 Example 2:
 
 Input:
 s = "aa"
 p = "*"
 Output: true
 Explanation: '*' matches any sequence.
 Example 3:
 
 Input:
 s = "cb"
 p = "?a"
 Output: false
 Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
 Example 4:
 
 Input:
 s = "adceb"
 p = "*a*b"
 Output: true
 Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
 Example 5:
 
 Input:
 s = "acdcb"
 p = "a*c?b"
 Output: false
 */

class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatch_dfs(s, p);
    }
    bool isMatch_dfs(string s, string p) {
        int n1 = s.size(), n2 = p.size();
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, 0));
        dp[n1][n2] = 1;
        return dfs(s, 0, p, 0, dp) == 1;
    }
    int dfs(const string& s, int i, const string& p, int j, vector<vector<int>>& dp) {
        if (dp[i][j]) {
            return dp[i][j];
        }
        if (i >= s.size()) {
            int k = j;
            while (j < p.size() && p[j] == '*') {
                ++j;
            }
            dp[i][k] = (j == p.size() ? 1 : -1);
            return dp[i][k];
        } else if (j >= p.size()) {
            return -1;
        }
        dp[i][j] = -1;
        if (p[j] == '*') {
            dp[i][j] = dfs(s, i, p, j+1, dp) || dfs(s, i+1, p, j, dp);
        } else {
            dp[i][j] = (p[j] == '?' || p[j] == s[i]) ? dfs(s, i+1, p, j+1, dp) : -1;
        }
        return dp[i][j];
    }
    /**
     * Let match[i][j] = whether s[0..j] matches p[0..i].
     * then match[i][j] =
     *  1, match[i-1][j-1] if s[j] == p[i] or p[i] = '?'
     *  2, false if s[j] != p[i] and p[i] != '*';
     *  3, true if match[i-1][j] or match[i][j-1] is true
     *
     * Note, * matches empty sequence...
     */
    bool isMatch_DP(string s, string p) {
        int ns = s.size();
        int np = p.size();
        
        if (np <= 0) {
            return ns <= 0;
        }
        vector<int> cnt(26, 0);
        for (char c : s) {
            ++cnt[c-'a'];
        }
    
        int n = ns;
        for (char c : p) {
            if (c != '*') {
                if (--n < 0) {
                    return false;
                }
                if (c >= 'a' && c <= 'z') {
                    if (--cnt[c-'a'] < 0) {
                        return false;
                    }
                }
            }
        }
        
        vector<bool> match(ns+1, false);
        if (p[0] == '*') {
            for (int j = 0; j <= ns; ++j) {
                match[j] = true;
            }
        } else if (p[0] == '?' || p[0] == s[0]) {
            match[1] = true;
        }
        
        
        for (int i = 1; i < np; ++i) {
            vector<bool> next(ns+1, false);
            if (p[i] == '*') {
                next[0] = match[0];
            }
            for (int j = 1; j <= ns; ++j) {
                if (p[i] == '?' || p[i] == s[j-1]) {
                    next[j] = match[j-1];
                } else if (p[i] == '*') {
                    next[j] = next[j-1] || match[j];
                } else {
                    next[j] = false;
                }
            }
            match.swap(next);
            
        }
        return match[ns];
    }
    /**
     * Divide pattern p into a list of smaller patterns, each smaller
     * pattern ends at a specific character or '?'.
     *
     * Then do DFS search.
     *
     * MLE or TLE
     */
    struct pc {
        char end;
        bool star;
        
        pc(char e, bool s) : end(e), star(s) {};
    };
    struct phash {
        size_t operator()(const pair<int,int>& p) const {
            static hash<string> sh;
            std::ostringstream oss;
            oss << p.first << "," << p.second;
            return sh(oss.str());
        }
    };
    bool isMatch_DFS(string s, string p) {
        // count unique characters in s and p, and total non * characters
        int n = s.size();
        vector<int> cnt(26, 0);
        for (char c : s) {
            ++cnt[c-'a'];
        }
        
        s.push_back('$');
        p.push_back('$');
        vector<pc> ps;
        bool prevstar = false;
        for (char c : p) {
            if (c != '*') {
                ps.push_back(pc(c, prevstar));
                prevstar = false;
                if (--n < 0) {
                    return false;
                }
                if (c >= 'a' && c <= 'z') {
                    if (--cnt[c-'a'] < 0) {
                        return false;
                    }
                }
            } else {
                prevstar = true;
            }
        }
        
        unordered_map<pair<int,int>, bool, phash> memo;
        return dfs(s, 0, ps, 0, memo);
        
    }
    
    bool dfs(string s, int si, vector<pc>& ps, int pi, unordered_map<pair<int,int>, bool, phash>& memo) {
        auto it = memo.find(make_pair(si, pi));
        if (it != memo.end()) {
            return it->second;
        }
        int n = s.size();
        int np = ps.size();
        if (si >= n) {
            return pi >= ps.size();
        } else {
            if (n - si + 1 < np - pi + 1) {
                return false;
            }
        }
        
        bool res = false;
        const pc& p = ps[pi];
        // pc.end == '?'
        if (p.end == '?') {
            if (!p.star) {
                res = dfs(s, si+1, ps, pi+1, memo);
            } else {
                int i = si+1;
                for (; i < n && (n-i+1 >= np-pi); ++i) {
                    if (dfs(s, i, ps, pi+1, memo)) {
                        res = true;
                        break;
                    }
                }
            }
        } else {
            if (!p.star) {
                if (s[si] != p.end) {
                    res = false;
                } else {
                    res = dfs(s, si+1, ps, pi+1, memo);
                }
            } else {
                int i = si;
                for (; i < n && (n-i+1 >= np-pi+1); ++i) {
                    if (s[i] != p.end) {
                        continue;
                    }
                    if (dfs(s, i+1, ps, pi+1, memo)) {
                        res = true;
                        break;
                    }
                }
            }
        }
        memo[make_pair(si, pi)] = res;
        return res;
    }
    
public:
    

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string s;
        string p;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{"",""},
        //{"aa","a"},
        //{"cb","?a"},
        //{"adceb","*a*b"},
        {"acdcb","a*c?b"},
        {"aa","*"},
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*"}
    };

    vector< bool > answers {
        true,
        false,
        false,
        true,
        false,
        true,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isMatch::Solution().isMatch(dp.s, dp.p);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
