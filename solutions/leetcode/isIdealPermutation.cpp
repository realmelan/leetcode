// isIdealPermutation.cpp
// leetcode
//
// Created by  Song Ding on 6/10/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isIdealPermutation {

class Solution {
public:
    /**
     * there should be only local swaps in original sorted array,
     * and once a pair is swapped, no swap should touch it again.
     *
     * How to check:
     * for each position i, check whether current value is i.
     * if not, check whether a swap exists:
     *   1, if not exists, return false
     *   2, if exists, move onto i + 2 position
     */
    bool isIdealPermutation(vector<int>& A) {
        int n = A.size();
        int i = 0;
        while (i < n) {
            if (A[i] != i) {
                if (A[i] != i + 1 || A[i + 1] != i) {
                    return false;
                }
                ++i;
            }
            ++i;
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> A{
       1,0
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = isIdealPermutation::Solution().isIdealPermutation(A);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
