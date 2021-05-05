// minFallingPathSum.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minFallingPathSum {
/*
// TODO: copy problem statement here
 931. Minimum Falling Path Sum
 Medium
 
 251
 
 31
 
 Favorite
 
 Share
 Given a square array of integers A, we want the minimum sum of a falling path through A.
 
 A falling path starts at any element in the first row, and chooses one element from each row.  The next row's choice must be in a column that is different from the previous row's column by at most one.
 
 
 
 Example 1:
 
 Input: [[1,2,3],[4,5,6],[7,8,9]]
 Output: 12
 Explanation:
 The possible falling paths are:
 [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
 [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
 [3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]
 The falling path with the smallest sum is [1,4,7], so the answer is 12.
 
 
 
 Note:
 
 1 <= A.length == A[0].length <= 100
 -100 <= A[i][j] <= 100
 */

class Solution {
public:
    /**
     * DP:
     * let fsum(i,j) = min falling path sum at row i and column j.
     * then fsum(i,j) = min(fsum(i-1,j+1), fsum(i-1,j), fsum(i-1,j-1)) + A[i][j]
     */
    int minFallingPathSum(vector<vector<int>>& A) {
        int r = A.size();
        int c = A[0].size();
        vector<int> fsum(A[0]);
        for (int i = 1; i < r; ++i) {
            vector<int> next(A[i]);
            for (int j = 0; j < c; ++j) {
                int t = fsum[j];
                if (j-1 >= 0) {
                    t = min(t, fsum[j-1]);
                }
                if (j+1 < c) {
                    t = min(t, fsum[j+1]);
                }
                next[j] += t;
            }
            fsum.swap(next);
        }
        int res = INT_MAX;
        for (int i = 0; i < c; ++i) {
            res = min(res, fsum[i]);
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
        vector<vector<int>> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,2,3},{4,5,6},{7,8,9}}}
    };

    vector<int  > answers {
        12
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minFallingPathSum::Solution().minFallingPathSum(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
