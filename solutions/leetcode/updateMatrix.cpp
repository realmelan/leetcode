//
//  updateMatrix.cpp
//  leetcode
//
//  Created by  Song Ding on 12/25/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace updateMatrix {
    class Solution {
    public:
        /**
         This looks like disjoint set problem, using recursive call of
         parent().
         */
        vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
            vector<vector<int>> res;
            int row = matrix.size();
            if (row <= 0) {
                return res;
            }
            int column = matrix[0].size();
            if (column <= 0) {
                return res;
            }
            res.resize(row);
            for (auto& v : res) {
                v.resize(column, -1);
            }
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    if (matrix[i][j] == 0) {
                        res[i][j] = 0;
                    }
                }
            }
            while (true) {
                int updated = 0;
                for (int i = 0; i < row; ++i) {
                    for (int j = 0; j < column; ++j) {
                        if (res[i][j] >= 0) {
                            if (j - 1 >= 0 && (res[i][j - 1] < 0 || res[i][j - 1] > res[i][j] + 1)) {
                                res[i][j - 1] = res[i][j] + 1;
                                ++updated;
                            }
                            if (i - 1 >= 0 && (res[i - 1][j] < 0 || res[i - 1][j] > res[i][j] + 1)) {
                                res[i - 1][j] = res[i][j] + 1;
                                ++updated;
                            }
                            if (i + 1 < row && (res[i + 1][j] < 0 || res[i + 1][j] > res[i][j] + 1)) {
                                res[i + 1][j] = res[i][j] + 1;
                                ++updated;
                            }
                            if (j + 1 < column && (res[i][j + 1] < 0 || res[i][j + 1] > res[i][j] + 1)) {
                                res[i][j + 1] = res[i][j] + 1;
                                ++updated;
                            }
                        }
                    }
                }
                if (updated == 0) {
                    break;
                }
            }
            return res;
        }
    };
}

/*
int main() {
    vector<vector<int>> matrix{
        {1, 0, 1, 1, 0, 0, 1, 0, 0, 1}, {0, 1, 1, 0, 1, 0, 1, 0, 1, 1}, {0, 0, 1, 0, 1, 0, 0, 1, 0, 0}, {1, 0, 1, 0, 1, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 1, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 1, 1, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1, 0, 0, 1, 1}, {1, 0, 0, 0, 1, 1, 1, 1, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 0, 1, 0}, {1, 1, 1, 1, 0, 1, 0, 0, 1, 1}
    };
    
    vector<vector<int>> res = updateMatrix::Solution().updateMatrix(matrix);
    for (const auto&v : res) {
        cout << "[";
        for (auto i : v) {
            cout << i << ",";
        }
        cout << "]" << endl;
    }
    return 0;
}
 */
