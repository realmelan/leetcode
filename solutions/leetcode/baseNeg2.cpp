// baseNeg2.cpp
// leetcode
//
// Created by  Song Ding on 5/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace baseNeg2 {
/*
// TODO: copy problem statement here
 1017. Convert to Base -2
 Medium
 
 59
 
 87
 
 Favorite
 
 Share
 Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).
 
 The returned string must have no leading zeroes, unless the string is "0".
 
 
 
 Example 1:
 
 Input: 2
 Output: "110"
 Explantion: (-2) ^ 2 + (-2) ^ 1 = 2
 Example 2:
 
 Input: 3
 Output: "111"
 Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3
 Example 3:
 
 Input: 4
 Output: "100"
 Explantion: (-2) ^ 2 = 4
 
 
 Note:
 
 0 <= N <= 10^9
 */

class Solution {
public:
    /**
     * still use 2 as base, but alternate the signs of current position of 1,
     * and adjust the leftover value.
     */
    string baseNeg2(int N) {
        string res;
        int t = N;
        int sign = 1;
        while (t) {
            int e = t & 1;
            char c = '0' + e;
            res.insert(res.begin(), c);
            t = (t - e * sign) >> 1;
            sign *= -1;
        }
        if (res.empty()) {
            return "0";
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
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {2},
        {3},
        {4},
        {0}
    };

    vector< string > answers {
        "110",
        "111",
        "100"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = baseNeg2::Solution().baseNeg2(dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
