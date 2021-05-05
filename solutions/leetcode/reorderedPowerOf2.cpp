// reorderedPowerOf2.cpp
// leetcode
//
// Created by  Song Ding on 5/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace reorderedPowerOf2 {
/*
// TODO: copy problem statement here
 869. Reordered Power of 2
 Medium
 
 120
 
 58
 
 Favorite
 
 Share
 Starting with a positive integer N, we reorder the digits in any order (including the original order) such that the leading digit is not zero.
 
 Return true if and only if we can do this in a way such that the resulting number is a power of 2.
 
 
 
 Example 1:
 
 Input: 1
 Output: true
 Example 2:
 
 Input: 10
 Output: false
 Example 3:
 
 Input: 16
 Output: true
 Example 4:
 
 Input: 24
 Output: false
 Example 5:
 
 Input: 46
 Output: true
 
 
 Note:
 
 1 <= N <= 10^9
 */

class Solution {
public:
    /**
     * there are only 31 kinds of powers of 2.
     * For each this power, get the digits, and compare N with the digits.
     */
    bool reorderedPowerOf2(int N) {
        vector<int> ndc(10);
        getDigits(N, ndc);
        
        long p = 1;
        while (N / p >= 10) {
            p <<= 1;
        }
        while (p / N < 10) {
            vector<int> dc(10);
            getDigits(p, dc);
            if (dc == ndc) {
                return true;
            }
            p <<= 1;
        }
        return false;
    }

private:
    void getDigits(int i, vector<int>& dc) {
        while (i > 0) {
            ++dc[i%10];
            i /= 10;
        }
    }
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
        {1},
        {10},
        {16},
        {24},
        {46},
        {271612776}
    };

    vector< bool > answers {
        true,
        false,
        true,
        false,
        true
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = reorderedPowerOf2::Solution().reorderedPowerOf2(dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
