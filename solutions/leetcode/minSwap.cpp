// minSwap.cpp
// leetcode
//
// Created by  Song Ding on 5/7/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minSwap {

class Solution {
public:
    /**
     * Let s[i][0] = # of swaps to make A[0..i] and B[0..i] strictly increasing, without
     * swapping A[i] and B[i], s[i][1] = # of swaps to make A[0..i] and B[0..i] strictly
     * increasing, with swapping A[i] and B[i].
     * then:
     *   if A[i-1] < A[i] && B[i-1] < B[i]:
     *       s[i][0] = min(s[i][0], s[i-1][0])
     *       s[i][1] = min(s[i][1], s[i-1][1] + 1)
     *   if A[i-1] < B[i] && B[i-1] < A[i]
     *       s[i][0] = min(s[i][0], s[i-1][1])
     *       s[i][1] = min(s[i][1], s[i-1][0] + 1)
     */
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        if (n < 2) {
            return 0;
        }
        
        vector<vector<int>> res(n);
        for (auto& v : res) {
            v.resize(2, INT_MAX);
        }
        
        res[0][0] = 0;
        res[0][1] = 1;
        
        for (int i = 1; i < n; ++i) {
            if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
                res[i][0] = min(res[i][0], res[i - 1][0]);
                res[i][1] = min(res[i][1], res[i - 1][1] + 1);
            }
            
            if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
                res[i][0] = min(res[i][0], res[i - 1][1]);
                res[i][1] = min(res[i][1], res[i - 1][0] + 1);
            }
        }
        
        return min(res[n - 1][0], res[n - 1][1]);
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> A{1,3,5,4};
    vector<int> B{1,2,3,7};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = minSwap::Solution().minSwap(A, B);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
