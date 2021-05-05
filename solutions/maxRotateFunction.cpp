// maxRotateFunction.cpp
// leetcode
//
// Created by  Song Ding on 10/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxRotateFunction {
/*
// TODO: copy problem statement here
 396. Rotate Function
 Medium

 305

 98

 Favorite

 Share
 Given an array of integers A and let n to be its length.

 Assume Bk to be an array obtained by rotating the array A k positions clock-wise, we define a "rotation function" F on A as follow:

 F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].

 Calculate the maximum value of F(0), F(1), ..., F(n-1).

 Note:
 n is guaranteed to be less than 105.

 Example:

 A = [4, 3, 2, 6]

 F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
 F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
 F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
 F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26

 So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.
 */

class Solution {
public:
    /**
     * diff between rotation(i) and rotation(i+1) is, sum(A) - n*A[n-i];
     * this can determine which rotation gives maximum value
     */
    int maxRotateFunction(vector<int>& A) {
        int n = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);
        int f = 0;
        for (int i = 0; i < n; ++i) {
            f += i * A[i];
        }
        int maxr = f;
        for (int i = 1; i < n; ++i) {
            f += sum - n * A[n-i];
            maxr = max(maxr, f);
        }
        return maxr;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{4,3,2,6}},
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxRotateFunction::Solution().maxRotateFunction(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
