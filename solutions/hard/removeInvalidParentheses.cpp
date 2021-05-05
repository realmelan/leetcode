// removeInvalidParentheses.cpp
// leetcode
//
// Created by  Song Ding on 9/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace removeInvalidParentheses {
/*
// TODO: copy problem statement here
 301. Remove Invalid Parentheses
 Hard
 
 1666
 
 71
 
 Favorite
 
 Share
 Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.
 
 Note: The input string may contain letters other than the parentheses ( and ).
 
 Example 1:
 
 Input: "()())()"
 Output: ["()()()", "(())()"]
 Example 2:
 
 Input: "(a)())()"
 Output: ["(a)()()", "(a())()"]
 Example 3:
 
 Input: ")("
 Output: [""]
 */

class Solution {
public:
    //
    vector<string> removeInvalidParentheses3(string s) {
        vector<string> res;
        remove(s, 0, 0, "()", res);
        return res;
    }
    void remove(const string& s, int last_i, int last_j, const string& cht, vector<string>& res) {
        int i = last_i, cnt = 0;
        while (i < s.size()) {
            if (s[i] == cht[0]) {
                ++cnt;
            } else if (s[i] == cht[1]){
                if (--cnt < 0) {
                    break;
                }
            }
            ++i;
        }
        if (i < s.size()) {
            for (int j = last_j; j <= i; ++j) {
                if (s[j] == cht[1] && (j == last_j || s[j-1] != cht[1])) {
                    string t = s.substr(0, j) + s.substr(j+1);
                    remove(t, i, j, cht, res);
                }
            }
            return;
        }
        string t(s);
        reverse(begin(t), end(t));
        if (cht[0] == '(') {
            remove(t, 0, 0, ")(", res);
        } else {
            res.push_back(t);
        }
    }
    /**
     * let gap(i) = # of '(' - # of ')'.
     * when gap(i) becomes 0, then should not remove any '(' before position i. if there
     * are continuous ')' after position i, which makes gap(i) becomes smaller, say until at
     * position j of '(', then it is ok to remove -gap(j-1) ')' (any position k) before
     * position j until gap(j-1) becomes 0. s[0..j-1] is one segment.
     *
     * The last segment is either positive or negative. If it is negative, then do as above
     * section.
     * Now, for say the last segment is positive, i.e. gap(n-1)=k, from position m. Then k '('
     * from m till n-1 sould be removed, however, after removing, no position should be negative.
     *
     * The above would provide minimum # of '(' and ')' to remove. Use recursive to find all
     * possible corrected strings.
     */
    vector<string> removeInvalidParentheses(string s) {
        int n = s.size();
        vector<string> res;
        
        vector<unordered_set<string>> segments;
        int ln = 0;
        int rn = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                ++ln;
            } else if (s[i] == ')') {
                if (ln <= 0) {
                    ++rn;
                } else {
                    --ln;
                }
            }
        }
        
        unordered_set<string> t;
        //removeParenthese(s, "", n-1, ln, rn, 0, t);
        string x;
        removeParenthese2(s, x, 0, ln, rn, 0, t);
        res.insert(res.end(), t.begin(), t.end());
        return res;
    }

private:
    // move backwards to remove ln '(' and rn ')'.
    // ln => # of '(' to remove
    // rn => # of ')' to remove
    // cnt => # of ')' from position i to n minus # of '(', meaning how many '(' can be kept from i till begining of s.
    void removeParenthese(const std::string& s, string t, int i, int ln, int rn, int cnt, unordered_set<string>& res) {
        if (ln == 0 && rn == 0) {
            for (int j = i; j >= 0; --j) {
                if (s[j] == ')') {
                    ++cnt;
                } else if (s[j] == '(') {
                    --cnt;
                    if (cnt < 0) {
                        return;
                    }
                }
                t.push_back(s[j]);
            }
            reverse(t.begin(), t.end());
            res.insert(t);
        } else {
            int j = i;
            while (j >= ln+rn-1 && (ln == 0 || s[j] != '(') && (rn == 0 || s[j] != ')')) {
                t.push_back(s[j]);
                if (s[j] == '(') {
                    if (--cnt < 0) {
                        return;
                    }
                } else if (s[j] == ')') {
                    ++cnt;
                }
                --j;
            }
            
            if (j >= ln+rn - 1) {
                if (s[j] == '(') {
                    removeParenthese(s, t, j-1, ln-1, rn, cnt, res);
                    if (cnt >= 1) {
                        t.push_back('(');
                        removeParenthese(s, t, j-1, ln, rn, cnt-1, res);
                    }
                } else {
                    removeParenthese(s, t, j-1, ln, rn-1, cnt, res);
                    t.push_back(')');
                    removeParenthese(s, t, j-1, ln, rn, cnt+1, res);
                }
            }
            
        }
    }
    /**
     remove parenthese from left
     */
    void removeParenthese2(const std::string& s, string& t, int i, int ln, int rn, int cnt, unordered_set<string>& res) {
        if (i == s.size()) {
            if (ln == 0 && rn == 0 && cnt == 0) {
                res.insert(t);
            }
        } else {
            if (s[i] == '(') {
                if (ln > 0) {
                    removeParenthese2(s, t, i+1, ln-1, rn, cnt, res);
                }
                t.push_back('(');
                removeParenthese2(s, t, i+1, ln, rn, cnt+1, res);
                t.pop_back();
            } else if (s[i] == ')') {
                if (rn > 0) {
                    removeParenthese2(s, t, i+1, ln, rn-1, cnt, res);
                }
                if (cnt > 0) {
                    t.push_back(')');
                    removeParenthese2(s, t, i+1, ln, rn, cnt-1, res);
                    t.pop_back();
                }
            } else {
                t.push_back(s[i]);
                removeParenthese2(s, t, i+1, ln, rn, cnt, res);
                t.pop_back();
            }
        }
    }
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
        {"()())()"},
        {"(a)())()"},
        {")("},
        {"((()()"},
        {")()))())))"},
        
    };

    vector< vector<string> > answers {
        {"()()()", "(())()"},
        {"(a)()()", "(a())()"},
        {""},
        {"(())","()()"},
        {"(())","()()"}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = removeInvalidParentheses::Solution().removeInvalidParentheses3(dp.s);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
