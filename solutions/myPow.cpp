// myPow.cpp
// leetcode
//
// Created by  Song Ding on 11/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace myPow {
/*
// TODO: copy problem statement here
 50. Pow(x, n)
 Medium

 1017

 2446

 Favorite

 Share
 Implement pow(x, n), which calculates x raised to the power n (xn).

 Example 1:

 Input: 2.00000, 10
 Output: 1024.00000
 Example 2:

 Input: 2.10000, 3
 Output: 9.26100
 Example 3:

 Input: 2.00000, -2
 Output: 0.25000
 Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25
 Note:

 -100.0 < x < 100.0
 n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]
 */

class Solution {
public:
    /**
     * Recursive!
     * Note: n might INT_MIN, such that -n exceeds INT_MAX.
     */
    double myPow(double x, int n) {
        if (n < 0) {
            return 1.0/myPow(x, -n-1) / x;
        } else if (x < 0){
            int sign = n%2 ? -1 : 1;
            return sign * myPow(-x, n);
        } else if (x == 1) {
            return 1;
        } else {
            if (n == 0) {
                return 1;
            } else {
                double half = myPow(x, n/2);
                if (n%2) {
                    return x * half * half;
                } else {
                    return half * half;
                }
            }
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        double x;
        int n;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {2.00000, 10},
        {2.10000, 3},
        {2.00000, -2}
    };

    vector< double > answers {
        1024.00000,
        9.26100,
        0.25000,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = myPow::Solution().myPow(dp.x, dp.n);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
