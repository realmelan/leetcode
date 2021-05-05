// knightDialer.cpp
// leetcode
//
// Created by  Song Ding on 5/3/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace knightDialer {

class Solution {
public:
    /**
     * Let hop[i] = # of hops from posotion i.
     * then at each position, there will be hop[i] variations.
     *
     */
    int knightDialer(int N) {
        vector<vector<int>> hops = {
            {4,6},{6,8},{7,9},{4,8},{0,3,9},
            {}, {0,1,7},{2,6},{1,3},{2,4}
        };
        vector<int> cur(10, 1);
        for (int i = 1; i < N; ++i) {
            vector<int> next(10, 0);
            for (int j = 0; j < 10; ++j) {
                for (auto k : hops[j]) {
                    next[k] += cur[j];
                    next[k] %= mod;
                }
            }
            cur.swap(next);
        }
        int res = 0;
        for (auto i : cur) {
            res += i;
            res %= mod;
        }
        return res;
    }

private:
    const static int mod = 1000000007;
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> N {
        1,
        2,
        3,
    };

    vector<  int > answers {
        10,
        20,
        46
    };
    int i = 2;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = knightDialer::Solution().knightDialer(N[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
