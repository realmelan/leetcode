// countNumbersWithUniqueDigits.cpp
// leetcode
//
// Created by  Song Ding on 10/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace countNumbersWithUniqueDigits {
/*
// TODO: copy problem statement here
 357. Count Numbers with Unique Digits
 Medium

 290

 695

 Favorite

 Share
 Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10^n.

 Example:

 Input: 2
 Output: 91
 Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100,
              excluding 11,22,33,44,55,66,77,88,99
 */

class Solution {
public:
    /**
     * the first position has 9 choices, and next has 9, and the next has 8, ...
     * and there is no need to go up to n=11
     */
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }
        int res = 9;
        int b = 9;
        for (int i = 1; i < min(n,10); ++i) {
            b *= 10 - i;
            res += b;
        }
        return res + 1; // plus 0
    }

private:
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
        {}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = countNumbersWithUniqueDigits::Solution().countNumbersWithUniqueDigits(dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
