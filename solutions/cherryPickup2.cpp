//
//  cherryPickup2.cpp
//  leetcode
//
//  Created by Song Ding on 8/20/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace cherryPickup2 {
/*
// TODO: copy problem statement here
 1463. Cherry Pickup II
 Hard

 242

 4

 Add to List

 Share
 Given a rows x cols matrix grid representing a field of cherries. Each cell in grid represents the number of cherries that you can collect.

 You have two robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) of the grid.

 Return the maximum number of cherries collection using both robots  by following the rules below:

 From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).
 When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).
 When both robots stay on the same cell, only one of them takes the cherries.
 Both robots cannot move outside of the grid at any moment.
 Both robots should reach the bottom row in the grid.
  

 Example 1:



 Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
 Output: 24
 Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
 Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
 Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
 Total of cherries: 12 + 12 = 24.
 Example 2:



 Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
 Output: 28
 Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
 Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
 Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
 Total of cherries: 17 + 11 = 28.
 Example 3:

 Input: grid = [[1,0,0,3],[0,0,0,3],[0,0,3,3],[9,0,3,3]]
 Output: 22
 Example 4:

 Input: grid = [[1,1],[1,1]]
 Output: 4
  

 Constraints:

 rows == grid.length
 cols == grid[i].length
 2 <= rows, cols <= 70
 0 <= grid[i][j] <= 100
*/
class Solution {
public:
    // TODO: copy function signature here
    int cherryPickup(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
        dp[1][n] = grid[0][0] + grid[0][n-1];
        for (int i = 1; i < m; ++i) {
            vector<vector<int>> next(n+2, vector<int>(n+2, 0));
            for (int j = 0; j <= min(i,n-1); ++j) { // robot 1 position
                for (int k = n-1; k >= max(0, n-1-i); --k) { // robot 2 position
                    next[j+1][k+1] = max({dp[j][k], dp[j][k+1], dp[j][k+2], dp[j+1][k], dp[j+1][k+1], dp[j+1][k+2], dp[j+2][k], dp[j+2][k+1], dp[j+2][k+2]});
                    next[j+1][k+1] += grid[i][j];
                    if (k != j) {
                        next[j+1][k+1] += grid[i][k];
                    }
                }
            }
            dp.swap(next);
        }
        int res = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> grid;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{3,1,1},{2,5,1},{1,5,5},{2,1,1}}},
        {{{1,0,0,0,0,0,1},{2,0,0,0,0,3,0},{2,0,9,0,0,0,0},{0,3,0,5,4,0,0},{1,0,2,3,0,0,6}}},
        {{{1,0,0,3},{0,0,0,3},{0,0,3,3},{9,0,3,3}}},
        {{{1,1},{1,1}}},
    };
    // TODO: provide expected results here
    vector<int> answers {
        24,
        28,
        22,
        4,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = cherryPickup2::Solution().cherryPickup(dp.grid);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
