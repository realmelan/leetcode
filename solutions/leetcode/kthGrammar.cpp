// kthGrammar.cpp
// leetcode
//
// Created by  Song Ding on 9/5/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace kthGrammar {

class Solution {
public:
    /**
     * There is this rule regarding the number on the row N:
     *  row(N) = row(N-1) + row(N-1)^
     *
     * So if K is the second half of row N, then it must be the
     * xor of the correspondent first half of row N.
     * This can be recursively down to the first row.
     */
    int kthGrammar(int N, int K) {
        if (N == 1) {
            return 0;
        }
        
        int half = 1 << (N - 2);
        if (K > half) {
            return 1 - kthGrammar(N - 1, K - half);
        } else {
            return kthGrammar(N - 1, K);
        }
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    int N = 4;
    int K = 5;

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = kthGrammar::Solution().kthGrammar(N, K);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
