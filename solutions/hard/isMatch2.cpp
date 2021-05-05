// isMatch2.cpp
// leetcode
//
// Created by  Song Ding on 7/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isMatch2 {
/*
// TODO: copy problem statement here
 10. Regular Expression Matching
 Hard
 
 2821
 
 543
 
 Favorite
 
 Share
 Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
 
 '.' Matches any single character.
 '*' Matches zero or more of the preceding element.
 The matching should cover the entire input string (not partial).
 
 Note:
 
 s could be empty and contains only lowercase letters a-z.
 p could be empty and contains only lowercase letters a-z, and characters like . or *.
 Example 1:
 
 Input:
 s = "aa"
 p = "a"
 Output: false
 Explanation: "a" does not match the entire string "aa".
 Example 2:
 
 Input:
 s = "aa"
 p = "a*"
 Output: true
 Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
 Example 3:
 
 Input:
 s = "ab"
 p = ".*"
 Output: true
 Explanation: ".*" means "zero or more (*) of any character (.)".
 Example 4:
 
 Input:
 s = "aab"
 p = "c*a*b"
 Output: true
 Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
 Example 5:
 
 Input:
 s = "mississippi"
 p = "mis*is*p*."
 Output: false
 */

class Solution {
public:
    /**
     * combine star with preceding character.
     *
     * DP:
     *  let match[i][j] = whether pattern[i] matches s[0..j]
     *  then
     *    match[i][j] = match[i-1][j] if p[i+1] = '*'
     *        || match[i][j-1] if p[i+1] = '*' && p[i] matches s[j]
     *    or match[i-1][j-1] if p[i] matches s[j].
     */
    bool isMatch(string s, string p) {
        int n = s.size();
        int np = p.size();
        if (n == 0) {
            // check whether p is "<char1>*..<char2>*" etc
            return matchEmpty(p);
        }
        vector<bool> cur(n+1, false);
        cur[0] = true;
        int i = 0;
        while (i < np) {
            vector<bool> next(n+1, false);
            if (i+1 < np && p[i+1] == '*') {
                next[0] = cur[0];
                for (int j = 0; j < n; ++j) {
                    next[j+1] = cur[j+1]; // p[i]* can match 0 character
                    if (!next[j+1]) {
                        if (p[i] == '.' || p[i] == s[j]) {
                            next[j+1] = next[j];
                        }
                    }
                }
                i += 2;
            } else {
                next[0] = false;
                for (int j = 0; j < n; ++j) {
                    if (p[i] == '.' || p[i] == s[j]) {
                        next[j+1] = cur[j];
                    }
                }
                ++i;
            }
            cur.swap(next);
        }
        return cur[n];
    }

private:
    bool matchEmpty(string p) {
        int n = p.size();
        if (n%2 == 0) {
            for (int i = 1; i < n; i+=2) {
                if (p[i] != '*') {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    
public:
    bool isMatch2(string s, string p) {
            int n1 = s.size(), n2 = p.size();
            vector<vector<int>> memo(n1+1, vector<int>(n2+1, 0));
            return dfs2(s, 0, p, 0, memo);
        }
    private:
        bool dfs2(string s, int i, string p, int j, vector<vector<int>>& memo) {
            int n1 = s.size(), n2 = p.size();
            if (i >= n1 && j >= n2) {
                return true;
            } else if (j >= n2) {
                return false;
            }
            if (memo[i][j]) {
                return memo[i][j] == 1;
            }
            char cp = p[j];
            char np = 0;
            if (j+1 < n2) {
                np = p[j+1];
            }
            if (np == '*') {
                if (dfs2(s, i, p, j+2, memo)) {
                    memo[i][j] = 1;
                    return true;
                }
                
                if (i < n1 && (s[i] == cp || cp == '.') && dfs2(s, i+1, p, j, memo)) {
                    memo[i][j] = 1;
                    return true;
                    
                }
                memo[i][j] = -1;
                return false;
            } else {
                if (i < n1 && (s[i] == cp || cp == '.') && dfs2(s, i+1, p, j+1, memo)) {
                    memo[i][j] = 1;
                } else {
                    memo[i][j] = -1;
                }
                return memo[i][j] == 1;
            }
        }
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
        {"",""},
        {"","a*"},
        {"aa","a"},
        {"aa","a*"},
        {"ab",".*"},
        {"ab",".*c"},
        {"aab", "c*a*b"},
        {"mississippi","mis*is*p*."}
    };

    vector< bool > answers {
        true,
        true,
        false,
        true,
        true,
        false,
        true,
        false
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isMatch2::Solution().isMatch2(dp.s, dp.p);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
