// minimumMoves.cpp
// leetcode
//
// Created by  Song Ding on 10/10/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace minimumMoves {
/*
// TODO: copy problem statement here
 1210. Minimum Moves to Reach Target with Rotations
 Hard

 63

 14

 Favorite

 Share
 In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).

 In one move the snake can:

 Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
 Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
 Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).

 Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).

 Return the minimum number of moves to reach the target.

 If there is no way to reach the target, return -1.

  

 Example 1:



 Input: grid = [[0,0,0,0,0,1],
                [1,1,0,0,1,0],
                [0,0,0,0,1,1],
                [0,0,1,0,1,0],
                [0,1,1,0,0,0],
                [0,1,1,0,0,0]]
 Output: 11
 Explanation:
 One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
 Example 2:

 Input: grid = [[0,0,1,1,1,1],
                [0,0,0,0,1,1],
                [1,1,0,0,0,1],
                [1,1,1,0,0,1],
                [1,1,1,0,0,1],
                [1,1,1,0,0,0]]
 Output: 9
  

 Constraints:

 2 <= n <= 100
 0 <= grid[i][j] <= 1
 It is guaranteed that the snake starts at empty cells.
 */

class Solution {
public:
    /**
     * BFS:
     * use (tail position,direction) as state
     */
    int minimumMoves(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        static const vector<vector<int>> moves {{0,1},{1,0}};
        vector<vector<vector<bool>>> visited(row);
        for (auto& v1 : visited) {
            v1.resize(col, vector<bool>{false,false});
        }
        // st => (x,y,dir)
        // dir 0 => horizontal (head right)
        // dir 1 => vertical (head down)
        vector<vector<int>> cur{{0,0,0}};
        visited[0][0][0] = true;
        int res = 0;
        while (cur.size()) {
            ++res;
            vector<vector<int>> next;
            for (auto& st : cur) {
                int x = st[0];
                int y = st[1];
                int dir = st[2];
                // test all possible moves
                if (dir == 0) {
                    // right
                    if (y+2 < col && grid[x][y+2] == 0 && !visited[x][y+1][0]) {
                        if (x == row-1 && y+2 == col-1) {
                            return res;
                        } else {
                            next.push_back({x,y+1,0});
                            visited[x][y+1][0] = true;
                        }
                    }
                    if (x+1 < row && grid[x+1][y] == 0 && grid[x+1][y+1] == 0) {
                        if (x+1 == row-1 && y+1 == col-1) {
                            return res;
                        } else {
                            if (!visited[x+1][y][0]) { // move down
                                next.push_back({x+1,y,dir});
                                visited[x+1][y][0] = true;
                            }
                            if (!visited[x][y][1]){ // rotate clockwise
                                next.push_back({x,y,1});
                                visited[x][y][1] = true;
                            }
                        }
                    }
                } else {
                    if (x+2 < row && grid[x+2][y] == 0 && !visited[x+1][y][1]) {
                        next.push_back({x+1,y,1});
                        visited[x+1][y][1] = true;
                    }
                    if (y+1 < col && grid[x][y+1] == 0 && grid[x+1][y+1] == 0) {
                        if (!visited[x][y+1][1]) { // move right
                            next.push_back({x,y+1,1});
                            visited[x][y+1][1] = true;
                        }
                        if (!visited[x][y][0]) { // rotate counterclockwise
                            next.push_back({x,y,0});
                            visited[x][y][0] = true;
                        }
                    }
                } // end dir=1
            }// end for cur
            cur.swap(next);
        }
        return -1;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> grid;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            {0,0,0,0,0,1},
            {1,1,0,0,1,0},
            {0,0,0,0,1,1},
            {0,0,1,0,1,0},
            {0,1,1,0,0,0},
            {0,1,1,0,0,0}
        }},
        {{
            {0,0,1,1,1,1},
            {0,0,0,0,1,1},
            {1,1,0,0,0,1},
            {1,1,1,0,0,1},
            {1,1,1,0,0,1},
            {1,1,1,0,0,0}
        }},
    };

    vector< int > answers {
        11,
        9,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minimumMoves::Solution().minimumMoves(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
