// spiralMatrixIII.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace spiralMatrixIII {
/*
// TODO: copy problem statement here
 885. Spiral Matrix III
 Medium
 
 95
 
 147
 
 Favorite
 
 Share
 On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing east.
 
 Here, the north-west corner of the grid is at the first row and column, and the south-east corner of the grid is at the last row and column.
 
 Now, we walk in a clockwise spiral shape to visit every position in this grid.
 
 Whenever we would move outside the boundary of the grid, we continue our walk outside the grid (but may return to the grid boundary later.)
 
 Eventually, we reach all R * C spaces of the grid.
 
 Return a list of coordinates representing the positions of the grid in the order they were visited.
 
 
 
 Example 1:
 
 Input: R = 1, C = 4, r0 = 0, c0 = 0
 Output: [[0,0],[0,1],[0,2],[0,3]]
 
 
 
 
 Example 2:
 
 Input: R = 5, C = 6, r0 = 1, c0 = 4
 Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
 
 
 
 
 Note:
 
 1 <= R <= 100
 1 <= C <= 100
 0 <= r0 < R
 0 <= c0 < C
 */

class Solution {
public:
    /**
     * 
     */
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        vector<vector<int>> res{{r0,c0}};
        const vector<vector<int>> dir{
            {0,1},{1,0},{0,-1},{-1,0}
        };
        const int total = R * C;
        int di = 0;
        int dist = 1;
        vector<int> last{r0,c0};
        while (res.size() != total) {
            int x = last[0] + dir[di][0];
            int y = last[1] + dir[di][1];
            if (x >= 0 && x < R && y >= 0 && y < C) {
                res.push_back({x,y});
            }
            last[0] = x;
            last[1] = y;
            
            int d = abs(x-r0) + abs(y-c0);
            if (d == dist) {
                if (di == 0 || di == 3) {
                    ++dist;
                }
                ++di;
                di %= 4;
                
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
        int R;
        int C;
        int r0;
        int c0;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {1,4,0,0},
        {5,6,1,4}
    };

    vector< vector<vector<int>> > answers {
        {{0,0},{0,1},{0,2},{0,3}},
        {{1,4},{1,5},{2,5},{2,4},{2,3},{1,3},{0,3},{0,4},{0,5},{3,5},{3,4},{3,3},{3,2},{2,2},{1,2},{0,2},{4,5},{4,4},{4,3},{4,2},{4,1},{3,1},{2,1},{1,1},{0,1},{4,0},{3,0},{2,0},{1,0},{0,0}}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = spiralMatrixIII::Solution().spiralMatrixIII(dp.R, dp.C, dp.r0, dp.c0);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
