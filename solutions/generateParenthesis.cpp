// generateParenthesis.cpp
// leetcode
//
// Created by  Song Ding on 11/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace generateParenthesis {
/*
// TODO: copy problem statement here
 22. Generate Parentheses
 Medium

 3524

 207

 Favorite

 Share
 Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 For example, given n = 3, a solution set is:

 [
   "((()))",
   "(()())",
   "(())()",
   "()(())",
   "()()()"
 ]
 */

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        dfs("", n, n, res);
        return res;
    }
    void dfs(string s, int ln, int rn, vector<string>& res) {
        if (ln == 0 && rn == 0) {
            res.push_back(s);
            return;
        }
        if (ln > 0) {
            dfs(s+"(", ln-1, rn, res);
        }
        if (ln < rn) {
            dfs(s+")", ln, rn-1, res);
        }
    }
    /**
     * use a counter to keep track the difference between # of '(' and # of ')'.
     * at each iteration, add 0 to diff ')' before adding another '('.
     */
    vector<string> generateParenthesis3(int n) {
        vector<string> res;
        dfs3("", 0, n, res);
        return res;
    }

private:
    void dfs3(string cur, int diff, int cnt, vector<string>& res) {
        if (cnt == 0) {
            for (int i = 0; i < diff; ++i) {
                cur.push_back(')');
            }
            res.push_back(cur);
        } else {
            for (int i = 0; i <= diff; ++i) {
                string t(cur);
                t.push_back('(');
                dfs3(t, diff-i+1, cnt-1, res);
                cur.push_back(')');
            }
        }
    }
public:
    vector<string> generateParenthesis2(int n) {
        vector<string> res;
        string s;
        dfs2("(", n-1, n, res);
        return res;
    }
    void dfs2(string s, int ln, int rn, vector<string>& res) {
        if (ln <= 0) {
            res.push_back(s);
            for (int i = 0; i < rn; ++i) {
                res.back().push_back(')');
            }
            return;
        }
        if (ln < rn) {
            string t(s);
            t.push_back(')');
            dfs2(t, ln, rn-1, res);
        }
        for (int i = 1; i <= ln; ++i) {
            s.push_back('(');
            string t(s);
            t.push_back(')');
            dfs2(t, ln-i, rn-1, res);
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {3},
    };

    vector< vector<string> > answers {
        {
          "((()))",
          "(()())",
          "(())()",
          "()(())",
          "()()()"
        },
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = generateParenthesis::Solution().generateParenthesis(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
