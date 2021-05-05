//
//  calculate.cpp
//  leetcode
//
//  Created by Song Ding on 11/24/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace calculate {
/*
// TODO: copy problem statement here
  Basic Calculator II
 Implement a basic calculator to evaluate a simple expression string.

 The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

 Example 1:

 Input: "3+2*2"
 Output: 7
 Example 2:

 Input: " 3/2 "
 Output: 1
 Example 3:

 Input: " 3+5 / 2 "
 Output: 5
 Note:

 You may assume that the given expression is always valid.
 Do not use the eval built-in library function.
*/
class Solution {
public:
    // TODO: copy function signature here
    int calculate(string s) {
        int res = 0;
        int m1 = 1, m2 = 0;
        bool isMulti = true;
        for (auto c : s) {
            if (c == '+') {
                res += (isMulti ? m1*m2 : m1/m2);
                m1 = 1;
                m2 = 0;
                isMulti = true;
            } else if (c == '-') {
                res += (isMulti ? m1*m2 : m1/m2);
                m1 = -1;
                m2 = 0;
                isMulti = true;
            } else if (c == '*') {
                if (isMulti) {
                    m1 *= m2;
                } else {
                    m1 /= m2;
                }
                m2 = 0;
                isMulti = true;
            } else if (c == '/') {
                if (isMulti) {
                    m1 *= m2;
                } else {
                    m1 /= m2;
                }
                m2 = 0;
                isMulti = false;
            } else if (c != ' ') {
                m2 *= 10;
                m2 += c - '0';
            }
        }
        return res + (isMulti?m1*m2:m1/m2);
    }
    
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        string s;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {"3+2*2"},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = calculate::Solution().calculate(dp.s);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
