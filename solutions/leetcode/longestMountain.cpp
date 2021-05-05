// longestMountain.cpp
// leetcode
//
// Created by  Song Ding on 6/5/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestMountain {

class Solution {
public:
    /**
     * For each position i in A, let linc[i] = # of increase
     * from left side, let rinc[i] = # of increase from right side.
     *
     * Now, for each position, res[i] = linc[i] + rinc[i] + 1.
     * fidn the longest.
     */
    int longestMountain(vector<int>& A) {
        
        int n = A.size();
        if (n < 3) {
            return 0;
        }
        vector<int> linc(n, 0), rinc(n, 0);
        int c = 0;
        for (int i = 1; i < n; ++i) {
            if (A[i] > A[i - 1]) {
                linc[i] = linc[i - 1] + 1;
            }
        }
        
        for (int i = n - 2; i >= 0; --i) {
            if (A[i] > A[i + 1]) {
                rinc[i] = rinc[i + 1] + 1;
            }
        }
        
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (res < linc[i] + rinc[i] + 1) {
                res = linc[i] + rinc[i] + 1;
            }
        }
        if (res < 3) {
            return 0;
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<int> A{2,1,4,7,3,2,5};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = longestMountain::Solution().longestMountain(A);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
