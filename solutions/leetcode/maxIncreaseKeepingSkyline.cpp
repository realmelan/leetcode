// maxIncreaseKeepingSkyline.cpp
// leetcode
//
// Created by  Song Ding on 5/8/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxIncreaseKeepingSkyline {

class Solution {
public:
    /**
     * Find the maximum height for each row and column.
     * then increase each position till the min(rowPeak,columnPeak)
     */
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int row = grid.size();
        if (row <= 0) {
            return 0;
        }
        int column = grid[0].size();
        if (column <= 0) {
            return 0;
        }
        
        vector<int> rowPeak(row, INT_MIN), columnPeak(column, INT_MIN);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                rowPeak[i] = max(rowPeak[i], grid[i][j]);
                columnPeak[j] = max(columnPeak[j], grid[i][j]);
            }
        }
        
        int res = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                res += min(rowPeak[i], columnPeak[j]) - grid[i][j];
            }
        }
        return res;
    }
private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> grid{{3,0,8,4},{2,4,5,7},{9,2,6,3},{0,3,1,0}};
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = maxIncreaseKeepingSkyline::Solution().maxIncreaseKeepingSkyline(grid);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
