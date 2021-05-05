// minAddToMakeValid.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minAddToMakeValid {
/*
// TODO: copy problem statement here
 921. Minimum Add to Make Parentheses Valid
 Medium
 
 256
 
 21
 
 Favorite
 
 Share
 Given a string S of '(' and ')' parentheses, we add the minimum number of parentheses ( '(' or ')', and in any positions ) so that the resulting parentheses string is valid.
 
 Formally, a parentheses string is valid if and only if:
 
 It is the empty string, or
 It can be written as AB (A concatenated with B), where A and B are valid strings, or
 It can be written as (A), where A is a valid string.
 Given a parentheses string, return the minimum number of parentheses we must add to make the resulting string valid.
 
 
 
 Example 1:
 
 Input: "())"
 Output: 1
 Example 2:
 
 Input: "((("
 Output: 3
 Example 3:
 
 Input: "()"
 Output: 0
 Example 4:
 
 Input: "()))(("
 Output: 4
 
 
 Note:
 
 S.length <= 1000
 S only consists of '(' and ')' characters.
 */

class Solution {
public:
    /**
     * use stack to pair '(' and ')'.
     * if current char is '(', push it to stack; else check whether
     * there is any '(' on the stack. If not, 1 extra '(' is needed and drop ')',
     * otherwise, pop '(' off stack.
     *
     * Add the # of '(' on stack to current result.
     */
    int minAddToMakeValid(string S) {
        int res = 0;
        stack<char> st;
        for (auto c : S) {
            if (c == '(') {
                st.push(c);
            } else {
                if (st.empty()) {
                    ++res;
                } else {
                    st.pop();
                }
            }
        }
        
        return res + st.size();
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
        {"())"},
        {"((("},
        {"()"},
        {"()))(("}
        
    };

    vector< int > answers {
        1,
        3,
        0,
        4
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minAddToMakeValid::Solution().minAddToMakeValid(dp.S);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
