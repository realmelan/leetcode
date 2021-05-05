// preimageSizeFZF.cpp
// leetcode
//
// Created by  Song Ding on 10/16/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace preimageSizeFZF {

class Solution {
public:
    /**
     * The number of 5 in multipliers determines # of 0's.
     * For any 5*K, the # of 5's f(K) = K + K/5 + K/25 + K/125 + ...
     *
     * let f(5*n) = K, n is about K * 4 / 5.
     *
     * Answer would be either 5 or 0, as add 5 would increase # of 0.
     */
    int preimageSizeFZF(int K) {
        long i = K;
        i *= 4;
        i /= 5;
        for (; i <= K; ++i) {
            long r = count(i);
            if (r == K) {
                cout << i << endl;
                return 5;
            } else if (r > K) {
                break;
            }
        }
        return 0;
    }

private:
    int count(long k) {
        int res = 0;
        while (k) {
            res += k;
            k /= 5;
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    //int K = 0;
    int K = 1000000000;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = preimageSizeFZF::Solution().preimageSizeFZF(K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
