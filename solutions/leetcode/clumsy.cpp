// clumsy.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace clumsy {
/*
// TODO: copy problem statement here
 1006. Clumsy Factorial
 Medium
 
 36
 
 80
 
 Favorite
 
 Share
 Normally, the factorial of a positive integer n is the product of all positive integers less than or equal to n.  For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.
 
 We instead make a clumsy factorial: using the integers in decreasing order, we swap out the multiply operations for a fixed rotation of operations: multiply (*), divide (/), add (+) and subtract (-) in this order.
 
 For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.  However, these operations are still applied using the usual order of operations of arithmetic: we do all multiplication and division steps before any addition or subtraction steps, and multiplication and division steps are processed left to right.
 
 Additionally, the division that we use is floor division such that 10 * 9 / 8 equals 11.  This guarantees the result is an integer.
 
 Implement the clumsy function as defined above: given an integer N, it returns the clumsy factorial of N.
 
 
 
 Example 1:
 
 Input: 4
 Output: 7
 Explanation: 7 = 4 * 3 / 2 + 1
 Example 2:
 
 Input: 10
 Output: 12
 Explanation: 12 = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1
 
 
 Note:
 
 1 <= N <= 10000
 -2^31 <= answer <= 2^31 - 1  (The answer is guaranteed to fit within a 32-bit integer.)
 */

class Solution {
public:
    /**
     * Divide the N by 4, and each group of 4 contributes to the final
     * result, and each group does same operation, "-N*(N-1)/(N-2)+N-3".
     * However, for the 1st group, there is no '-', so the result of the 1st
     * group is an addition to the final result.
     *
     */
    int clumsy(int N) {
        int res = 0;
        int g = N>>2;
        int t = N%4;
        int last = 0;
        if (t == 1) {
            last = 1;
        } else if (t == 2) {
            last = 2;
        } else if (t == 3) {
            last = 6;
        }
        
        int k = t + 4;
        for (int i = 0; i < g; ++i, k+=4) {
            res -= last;
            last = k * (k-1) / (k-2) - (k-3);
        }
        if (g >= 1) {
            res += last + ((k - 7) << 1);
        } else {
            res += last;
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
        {4},
        {10},
        {1}
    };

    vector< int > answers {
        7,
        12
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = clumsy::Solution().clumsy(dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
