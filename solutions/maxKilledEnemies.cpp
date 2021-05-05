// maxKilledEnemies.cpp
// leetcode
//
// Created by  Song Ding on 10/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxKilledEnemies {
/*
// TODO: copy problem statement here
 361. Bomb Enemy

 Given a 2D grid, each cell is either a wall \'W\', an enemy \'E\' or empty \'0\' (the number zero), return the maximum enemies you can kill using one bomb.
 The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
 Note that you can only put the bomb at an empty cell.

 Example:

 For the given grid

 0 E 0 0
 E 0 W E
 0 E 0 0

 return 3. (Placing a bomb at (1,1) kills 3 enemies)
 Credits:
 Special thanks to @memoryless for adding this problem and creating all test cases.
 */

class Solution {
public:
    /**
     * go row to row and for each row:
     *  count # of E's until a W is met at a certain column, k
     *  if a 'W' is met, reset cole[j].
     *  for each column from previous start to k:
     *    if # of E found in cole[j]:
     *      use that value
     *    else:
     *      count # of E's in that column until a W is met and record in cole[j]
     *
     */
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int res = 0;
        // -1 means uninitialized;
        vector<int> cole(m, -1);
        for (int i = 0; i < n; ++i) {
            int maxCole = 0;
            int rowCnt = 0;
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'W') {
                    cole[j] = -1;
                    res = max(res, rowCnt + maxCole);
                    rowCnt = 0;
                    maxCole = 0;
                } else {
                    if (cole[j] == -1) {
                        // count E at column j
                        cole[j] = 0;
                        for (int k = i; k < n && grid[k][j] != 'W'; ++k) {
                            if (grid[k][j] == 'E') {
                                ++cole[j];
                            }
                        }
                    }
                    if (grid[i][j] == '0') {
                        maxCole = max(maxCole, cole[j]);
                    } else {
                        ++rowCnt;
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
        vector<vector<char>> grid;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            {'0','E','0','0'},
            {'E','0','W','E'},
            {'0','E','0','0'},
        }}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxKilledEnemies::Solution().maxKilledEnemies(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
