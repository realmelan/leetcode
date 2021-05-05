// setZeros.cpp
// leetcode
//
// Created by  Song Ding on 10/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace setZeros {
/*
// TODO: copy problem statement here
 73. Set Matrix Zeroes
 Medium

 1318

 230

 Favorite

 Share
 Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

 Example 1:

 Input:
 [
   [1,1,1],
   [1,0,1],
   [1,1,1]
 ]
 Output:
 [
   [1,0,1],
   [0,0,0],
   [1,0,1]
 ]
 Example 2:

 Input:
 [
   [0,1,2,0],
   [3,4,5,2],
   [1,3,1,5]
 ]
 Output:
 [
   [0,0,0,0],
   [0,4,5,0],
   [0,3,1,0]
 ]
 Follow up:

 A straight forward solution using O(mn) space is probably a bad idea.
 A simple improvement uses O(m + n) space, but still not the best solution.
 Could you devise a constant space solution?
 */

class Solution {
public:
    /**
     * https://leetcode.com/problems/set-matrix-zeroes/discuss/26014/Any-shorter-O(1)-space-solution
     * use the first column as marker to tell whether the row should be zeroed.
     * However, we need first mark whether the 1st row should be zeroed using an additional variable.
     * then loop through all rows (from row 1) and zero it if there is a cell is zero, then zero the row.
     */
    void setZeroes(vector<vector<int>>& matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        bool col0 = 0; // whether col0 should be zeroed.
        for (int i = 0; i < row; ++i) {
            if (matrix[i][0] == 0) {
                col0 = true;
            }
            for (int j = 1; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        
        // mark each row
        for (int i = row-1; i >= 0; --i) {
            for (int j = col-1; j > 0; --j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
            if (col0) {
                matrix[i][0] = 0;
            }
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> matrix;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            {1,1,2,4},
            {0,4,5,2},
            {3,3,1,0},
        }}
    };

    vector< vector<vector<int>> > answers {
        {
            {0,0,0,0},
            {0,4,5,0},
            {0,3,1,0},
        }
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        setZeros::Solution().setZeroes(dp.matrix);
        cout << dp.matrix << endl;
        cout << clock() - tstart << endl;
    }
    return 0;
}
//*/
