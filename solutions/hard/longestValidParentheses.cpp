// longestValidParentheses.cpp
// leetcode
//
// Created by  Song Ding on 8/19/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestValidParentheses {
/*
// TODO: copy problem statement here
 32. Longest Valid Parentheses
 Hard
 
 2144
 
 97
 
 Favorite
 
 Share
 Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 
 Example 1:
 
 Input: "(()"
 Output: 2
 Explanation: The longest valid parentheses substring is "()"
 Example 2:
 
 Input: ")()())"
 Output: 4
 Explanation: The longest valid parentheses substring is "()()"
 */

class Solution {
public:
    /**
     * DP:
     *
     * let vp(i) = length of longest valid substring ending at s[i], apparently
     * s[i] = ')'.
     *
     * For next ')' at k, check:
     *   if s[k-1] is ')', then vp(k) = vp(k-1) + 2 + vp(k-vp(k-1)-2) if there is a '(' at k-vp(k-1)-1
     *   each expansion.
     *   if s[k-1] is '(', then vp(k) = 2 + vp(k-2)
     */
    int longestValidParentheses(string s) {
        int n = s.size();
        int res = 0;
        vector<int> vp(n, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i] == '(') {
                continue;
            }
            
            if (s[i-1] == '(') {
                vp[i] = 2;
                if (i >=2 ) {
                    vp[i] += vp[i-2];
                }
            } else {
                int t = vp[i-1];
                if (i-t-1>= 0 && s[i-t-1] == '(') {
                    vp[i] = 2 + t;
                    
                    if (i-t-2>= 0) {
                        vp[i] += vp[i-t-2];
                    }
                }
            }
            
            res = max(res, vp[i]);
        }
        return res;
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
        {"(()"},
        {")()())"},
        {"()"},
        {"())(())(()(((((())()())()())()((()(((()()))())(((()()(((())())))()()))))(()))))))(((((((())))(())(())(()()((()))))))()((())))))(())))))("},
        {"()(())"}
    };

    vector< int > answers {
        2,
        4,
        2,
        18,
        6
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = longestValidParentheses::Solution().longestValidParentheses(dp.s);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
