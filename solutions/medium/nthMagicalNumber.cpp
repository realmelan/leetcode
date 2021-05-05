// nthMagicalNumber.cpp
// leetcode
//
// Created by  Song Ding on 7/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace nthMagicalNumber {
/*
// TODO: copy problem statement here
 878. Nth Magical Number
 Hard
 
 113
 
 39
 
 Favorite
 
 Share
 A positive integer is magical if it is divisible by either A or B.
 
 Return the N-th magical number.  Since the answer may be very large, return it modulo 10^9 + 7.
 
 
 
 Example 1:
 
 Input: N = 1, A = 2, B = 3
 Output: 2
 Example 2:
 
 Input: N = 4, A = 2, B = 3
 Output: 6
 Example 3:
 
 Input: N = 5, A = 2, B = 4
 Output: 10
 Example 4:
 
 Input: N = 3, A = 6, B = 4
 Output: 8
 
 
 Note:
 
 1 <= N <= 10^9
 2 <= A <= 40000
 2 <= B <= 40000
 */

class Solution {
public:
    /**
     * Find the least common multiple, lcm, then
     * with a increase of lcm, #of (A) increased = lcm/A,
     * # of (B) increased = lcm/B, and total # increased is
     * inc_lcm = lcm/A + lcm/B - 1.
     *
     * let k = N % inc_lcm, then we only need to know the ordering within
     * one lcm, to arrive at the N-th.
     */
    int nthMagicalNumber(int N, int A, int B) {
        long lcm = (long)A * B / gcd(A, B);
        
        
        int inc_lcm = lcm/A + lcm/B - 1;
        int round = N / inc_lcm;
        int cnt = N % inc_lcm;
        
        vector<int> nth;
        nth.reserve(inc_lcm);
        int a = A;
        while (a <= lcm) {
            nth.push_back(a);
            a += A;
        }
        int b = B;
        while (b < lcm) {
            nth.push_back(b);
            b += B;
        }
        
        long res = lcm * round;
        if (cnt > 0) {
            nth_element(nth.begin(), nth.begin() + cnt-1, nth.end());
            res += nth[cnt-1];
        }
        
        return res % 1000000007;
    }

private:
    int gcd(int A, int B) {
        int a = A;
        int b = B;
        if (a > b) {
            swap(a, b);
        }
        
        while (b%a) {
            int t = b % a;
            b = a;
            a = t;
        }
        return a;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int N;
        int A;
        int B;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{1,2,3},
        {4,2,3},
        {5,2,4},
        {3,6,4}
    };

    vector< int > answers {
        2,
        6,
        10,
        8
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = nthMagicalNumber::Solution().nthMagicalNumber(dp.N, dp.A, dp.B);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
