// maxSumSubmatrix.cpp
// leetcode
//
// Created by  Song Ding on 10/13/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxSumSubmatrix {
/*
// TODO: copy problem statement here
 363. Max Sum of Rectangle No Larger Than K
 Hard

 494

 36

 Favorite

 Share
 Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

 Example:

 Input: matrix = [[1,0,1],[0,-2,3]], k = 2
 Output: 2
 Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
              and 2 is the max number no larger than k (k = 2).
 Note:

 The rectangle inside the matrix must have an area > 0.
 What if the number of rows is much larger than the number of columns?
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int row = matrix.size();
        if (row <= 0) {
            return 0;
        }
        int column = matrix[0].size();
        if (column <= 0) {
            return 0;
        }
        
        int res = INT_MIN;
        for (int i = 0; i < row; ++i) {
            vector<int> sums(column, 0);
            for (int j = i; j < row; ++j) {
                int sum = 0;
                for (int c = 0; c < column; ++c) {
                    sum += matrix[j][c];
                    sums[c] += sum;
                    if (sums[c] < k && sums[c] > res) {
                        res = sums[c];
                    }
                    
                }
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
        vector<vector<int>> matrix;
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,0,1},{0,-2,3}}, 2},
    };

    vector< int > answers {
        2,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxSumSubmatrix::Solution().maxSumSubmatrix(dp.matrix, dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
