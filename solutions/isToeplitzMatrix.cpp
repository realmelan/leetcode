//
//  isToeplitzMatrix.cpp
//  leetcode
//
//  Created by Song Ding on 2/20/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace isToeplitzMatrix {
/*
// TODO: copy problem statement here
 766. Toeplitz Matrix
 Easy

 817

 73

 Add to List

 Share
 A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

 Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
  

 Example 1:

 Input:
 matrix = [
   [1,2,3,4],
   [5,1,2,3],
   [9,5,1,2]
 ]
 Output: True
 Explanation:
 In the above grid, the diagonals are:
 "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
 In each diagonal all elements are the same, so the answer is True.
 Example 2:

 Input:
 matrix = [
   [1,2],
   [2,2]
 ]
 Output: False
 Explanation:
 The diagonal "[1, 2]" has different elements.

 Note:

 matrix will be a 2D array of integers.
 matrix will have a number of rows and columns in range [1, 20].
 matrix[i][j] will be integers in range [0, 99].

 Follow up:

 What if the matrix is stored on disk, and the memory is limited such that you can only load at most one row of the matrix into the memory at once?
 What if the matrix is so large that you can only load up a partial row into the memory at once?
*/
class Solution {
public:
    // TODO: copy function signature here
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // starting from top row
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m && (i+j) < n; ++i) {
                if (matrix[i][i+j] != matrix[0][j]) {
                    return false;
                }
            }
        }
        // starting from left column
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n && (i+j) < m; ++j) {
                if (matrix[i+j][j] != matrix[i][0]) {
                    return false;
                }
            }
        }
        return true;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> matrix;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{
            {1,2,3,4},
            {5,1,2,3},
            {9,5,1,2}
        }},
        {{
            {1,2},
            {2,2}
        }},
        {{
            {18},
            {66}
        }}
    };
    // TODO: provide expected results here
    vector<bool> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isToeplitzMatrix::Solution().isToeplitzMatrix(dp.matrix);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
