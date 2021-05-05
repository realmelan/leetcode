// scoreOfParentheses.cpp
// leetcode
//
// Created by  Song Ding on 5/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace scoreOfParentheses {
/*
// TODO: copy problem statement here
 856. Score of Parentheses
 Medium
 
 540
 
 22
 
 Favorite
 
 Share
 Given a balanced parentheses string S, compute the score of the string based on the following rule:
 
 () has score 1
 AB has score A + B, where A and B are balanced parentheses strings.
 (A) has score 2 * A, where A is a balanced parentheses string.
 
 
 Example 1:
 
 Input: "()"
 Output: 1
 Example 2:
 
 Input: "(())"
 Output: 2
 Example 3:
 
 Input: "()()"
 Output: 2
 Example 4:
 
 Input: "(()(()))"
 Output: 6
 
 
 Note:
 
 S is a balanced parentheses string, containing only ( and ).
 2 <= S.length <= 50
 */

class Solution {
public:
    /**
     * For each '(', maintain a vector to hold the numbers that fall
     * into this layer, so layers form a stack.
     *
     * when a ')' is encountered, pop the top vector and check it:
     *  if there is no number in the vector, push '1' onto the new top vector
     *  else add the numbers and then times 2, and push result onto the new top vector.
     */
    int scoreOfParentheses(string S) {
        stack<vector<int>> cs;
        cs.push({});
        for (auto i : S) {
            if (i == '(') {
                cs.push({});
            } else {
                vector<int> t;
                t.swap(cs.top());
                cs.pop();
                
                int res = 0;
                if (t.empty()) {
                    res = 1;
                } else {
                    for (auto i : t) {
                        res += i;
                    }
                    res <<= 1;
                }
                
                cs.top().push_back(res);
            }
        }
        int res = 0;
        for (auto i : cs.top()) {
            res += i;
        }
        return res;
    }
    int scoreOfParentheses2(string S) {
        int n = S.size();
        int cnt = 0, start = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            if (S[i] == '(') {
                ++cnt;
            } else {
                if (--cnt == 0) {
                    if (i == start + 1) {
                        res += 1;
                    } else {
                        res += 2 * scoreOfParentheses2(S.substr(start+1, i-start-1));
                    }
                    start = i+1;
                }
            }
        }
        return res;
    }
    int scoreOfParentheses3(string S) {
        int n = S.size();
        vector<vector<int>> layers(1);
        for (auto c : S) {
            if (c == '(') {
                layers.resize(layers.size() + 1);
            } else {
                int res = accumulate(begin(layers.back()), end(layers.back()), 0);
                layers.pop_back();
                layers.back().push_back(res ? res*2 : 1);
            }
        }
        
        return accumulate(begin(layers.back()), end(layers.back()), 0);
    }
private:
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
        {"()"},
        {"(())"},
        {"()()"},
        {"(()(()))"}
    };

    vector< int > answers {
        1,
        2,
        2,
        6
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = scoreOfParentheses::Solution().scoreOfParentheses(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
