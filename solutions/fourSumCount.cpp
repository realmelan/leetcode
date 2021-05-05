// fourSumCount.cpp
// leetcode
//
// Created by  Song Ding on 10/28/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace fourSumCount {
/*
// TODO: copy problem statement here
 454. 4Sum II
 Medium

 823

 62

 Favorite

 Share
 Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.

 To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in the range of -2^28 to 2^28 - 1 and the result is guaranteed to be at most 2^31 - 1.

 Example:

 Input:
 A = [ 1, 2]
 B = [-2,-1]
 C = [-1, 2]
 D = [ 0, 2]

 Output:
 2

 Explanation:
 The two tuples are:
 1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
 2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
 */

class Solution {
public:
    /**
     * compute C[i]+D[j] and store result in hash
     * for each A[i], B[j] pair,  check whether -(A[i]+B[j]) is in hash or not and add the count into final result.
     * Computation cost is O(n^2).
     */
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int n = A.size();
        unordered_map<int, int> sumCount;
        for (int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                ++sumCount[C[i]+D[j]];
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                res += sumCount[-(A[i]+B[j])];
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
        vector<int> B;
        vector<int> C;
        vector<int> D;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1, 2},{-2,-1},{-1, 2},{ 0, 2}}
    };

    vector< int > answers {
        2,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = fourSumCount::Solution().fourSumCount(dp.A, dp.B, dp.C, dp.D);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
