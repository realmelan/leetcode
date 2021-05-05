// numTilings.cpp
// leetcode
//
// Created by  Song Ding on 6/10/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numTilings {

class Solution {
public:
    static const int modulo = 1000000007;
    /**
     * DP
     * let f(i, j) = # of solutions to tile (i squares in row 1 and
     * j squares in row 2).
     * f(i, i) = f(i - 1, i - 1) + f(i - 2, i - 2) + f(i - 2, i - 1) + f(i - 1, i - 2)
     * f(i, i-1) = f(i-2,i-1) + f(i-2,i-2);
     * f(i, i+1) = f(i, i-1) + f(i-1,i-1);
     *
     * f(0,0) = 1
     * f(1,1) = 1
     * f(2,1) = 1
     * f(1,2) = 1
     * f(2,2) = 2
     *
     */
    int numTilings(int N) {
        unordered_map<int, int> memo;
        long res = tile(N, N, N, memo);
        return (int)res;
    }

private:
    long tile(int i, int j, int N, unordered_map<int, int>& memo) {
        if (i == 0 && j == 0) {
            return 1;
        } else if (j == 0 || i == 0) {
            return 0;
        } else if (i == 1 || j == 1) {
            return 1;
        } else {
            int id = i * N + j;
            auto it = memo.find(id);
            if (it != memo.end()) {
                return it->second;
            }
            long res = 0;
            int gap = i - j;
            if (gap == 0) {
                res = tile(i-1, i-1, N, memo) + tile(i-2, i-2, N, memo)
                    + tile(i-1, i-2, N, memo) + tile(i-2, i-1, N, memo);
            } else if (gap == 1) {
                res = tile(i-2, i-1, N, memo) + tile(i-2, i-2, N, memo);
            } else { // gap = -1
                res = tile(i, i-1, N, memo) + tile(i-1, i-1, N, memo);
            }
            if (res > modulo) {
                res = res % modulo;
            }
            memo.insert(make_pair(id, res));
            return res;
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 1000;
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = numTilings::Solution().numTilings(N);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
