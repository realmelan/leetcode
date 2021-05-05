// smallestFactorization.cpp
// leetcode
//
// Created by  Song Ding on 10/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace smallestFactorization {
/*
// TODO: copy problem statement here
 625. Minimum Factorization

 Given a positive integer a, find the smallest positive integer b whose multiplication of each digit equals to a.

 If there is no answer or the answer is not fit in 32-bit signed integer, then return 0.

 Example 1
 Input:

 48
 Output:
 68
 Example 2
 Input:

 15
 Output:
 35
 */

class Solution {
public:
    /**
     * starting from 9 to 1, find the largest digit k, that is divisible by a
     * and then recursively find result for a/k
     */
    int smallestFactorization(int a) {
        if (a < 10) {
            return a;
        } else {
            for (int i = 9; i > 1; --i) {
                if (a%i == 0) {
                    int t = smallestFactorization(a/i);
                    if (t > 0) {
                        return t*10 + i;
                    }
                }
            }
        }
        return 0;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int a;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {48},
        {15},
    };

    vector< int > answers {
        68,
        35,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = smallestFactorization::Solution().smallestFactorization(dp.a);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
