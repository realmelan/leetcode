// consecutiveNumbersSum.cpp
// leetcode
//
// Created by  Song Ding on 5/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace consecutiveNumbersSum {

class Solution {
public:
    /**
     * Let N = sum of k consecutive numbers, with a being the first number.
     * then 2*N = k * (2*a + k - 1)
     *
     * For all divisor of 2*N(to be k), check whether a exists or not.
     */
    int consecutiveNumbersSum(int N) {
        N <<= 1;
        int sq = sqrt(N);
        int res = 1;
        for (int i = 2; i <= sq; ++i) {
            if (N % i == 0) {
                int k = i;
                int t = N / k + 1 - k;
                if (t > 0 && t % 2 == 0) {
                    ++res;
                }
                
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 5;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = consecutiveNumbersSum::Solution().consecutiveNumbersSum(N);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
