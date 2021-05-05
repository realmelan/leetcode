//
//  uniquePath2.cpp
//  leetcode
//
//  Created by  Song Ding on 12/27/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace uniquePath2 {
    class Solution {
    public:
        /**
         DP, but do some special processing when grid is 1.
         u(i,j) = {u(i-1, j) if o(i-1,j) != 1} + {u(i, j-1) if o(u,j-1) != 1}
         */
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
            int row = obstacleGrid.size();
            if (row <= 0) {
                return 0;
            }
            int column = obstacleGrid[0].size();
            if (column <= 0) {
                return 0;
            }
            if (obstacleGrid[0][0] == 1 || obstacleGrid[row - 1][column - 1] == 1) {
                return 0;
            }
            
            vector<int> row1;
            bool blocked = false;
            for (auto i : obstacleGrid[0]) {
                if (i == 1) {
                    blocked = true;
                }
                row1.push_back(blocked ? 0 : 1);
            }
            vector<int> row2(column);
            for (int i = 1; i < row; ++i) {
                row2.resize(column, 0);
                if (row1[0] != 0) {
                    row2[0] = 1 - obstacleGrid[i][0];
                }
                for (int j = 1; j < column; ++j) {
                    if (obstacleGrid[i][j] == 0) {
                        int t = 0;
                        if (obstacleGrid[i - 1][j] != 1) {
                            t += row1[j];
                        }
                        if (obstacleGrid[i][j - 1] != 1) {
                            t += row2[j - 1];
                        }
                        row2[j] = t;
                    } else {
                        row2[j] = 0;
                    }
                }
                row1.swap(row2);
            }
            
            return row1[column - 1];
        }
    };
}
/*
int main() {
    vector<vector<int>> grid{
        {0,0},
        {1,1},
        {0,0}
    };
    cout << uniquePath2::Solution().uniquePathsWithObstacles(grid) << endl;
    return 0;
}
 */
