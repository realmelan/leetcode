// monotoneIncreasingDigits.cpp
// leetcode
//
// Created by  Song Ding on 6/18/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace monotoneIncreasingDigits {

class Solution {
public:
    /**
     * Starting from the most significant digit, check whether the
     * next digit is no smaller.
     *
     * If on position i, digit is smaller than digit on position i-1,
     * then decrease the previous number by 1, and append same number of
     * '9' for digits i to n.
     */
    int monotoneIncreasingDigits(int N) {
        vector<int> d;
        int t = N;
        while (t) {
            d.insert(d.begin(), t % 10);
            t /= 10;
        }
        int n = d.size();
        int i = 0;
        for (; i < n - 1; ++i) {
            if (d[i] > d[i+1]) {
                --d[i];
                while (i >= 1 && d[i] < d[i - 1]) {
                    --d[i-1];
                    --i;
                }
                break;
            }
        }
        int res = 0;
        if (i < n - 1) {
            res = d[0];
            int j = 1;
            for (; j <= i; ++j) {
                res *= 10;
                res += d[j];
            }
            for (; j < n; ++j) {
                res *= 10;
                res += 9;
            }
        } else {
            for (int i = 0; i < n; ++i) {
                res *= 10;
                res += d[i];
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
    int N = 456619;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = monotoneIncreasingDigits::Solution().monotoneIncreasingDigits(N);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
