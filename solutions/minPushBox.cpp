//
//  minPushBox.cpp
//  leetcode
//
//  Created by Song Ding on 7/9/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minPushBox {
/*
// TODO: copy problem statement here
 1263. Minimum Moves to Move a Box to Their Target Location
 Hard

 198

 8

 Add to List

 Share
 Storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.

 The game is represented by a grid of size m x n, where each element is a wall, floor, or a box.

 Your task is move the box 'B' to the target position 'T' under the following rules:

 Player is represented by character 'S' and can move up, down, left, right in the grid if it is a floor (empy cell).
 Floor is represented by character '.' that means free cell to walk.
 Wall is represented by character '#' that means obstacle  (impossible to walk there).
 There is only one box 'B' and one target cell 'T' in the grid.
 The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
 The player cannot walk through the box.
 Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.

  

 Example 1:



 Input: grid = [["#","#","#","#","#","#"],
                ["#","T","#","#","#","#"],
                ["#",".",".","B",".","#"],
                ["#",".","#","#",".","#"],
                ["#",".",".",".","S","#"],
                ["#","#","#","#","#","#"]]
 Output: 3
 Explanation: We return only the number of times the box is pushed.
 Example 2:

 Input: grid = [["#","#","#","#","#","#"],
                ["#","T","#","#","#","#"],
                ["#",".",".","B",".","#"],
                ["#","#","#","#",".","#"],
                ["#",".",".",".","S","#"],
                ["#","#","#","#","#","#"]]
 Output: -1
 Example 3:

 Input: grid = [["#","#","#","#","#","#"],
                ["#","T",".",".","#","#"],
                ["#",".","#","B",".","#"],
                ["#",".",".",".",".","#"],
                ["#",".",".",".","S","#"],
                ["#","#","#","#","#","#"]]
 Output: 5
 Explanation:  push the box down, left, left, up and up.
 Example 4:

 Input: grid = [["#","#","#","#","#","#","#"],
                ["#","S","#",".","B","T","#"],
                ["#","#","#","#","#","#","#"]]
 Output: -1
  

 Constraints:

 m == grid.length
 n == grid[i].length
 1 <= m <= 20
 1 <= n <= 20
 grid contains only characters '.', '#',  'S' , 'T', or 'B'.
 There is only one character 'S', 'B' and 'T' in the grid.
*/
class Solution {
public:
    // TODO: copy function signature here
    int minPushBox(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        int r = grid.size(), c = grid[0].size();
        int tx = 0, ty = 0, bx = 0, by = 0, px = 0, py = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j] == 'B') {
                    bx = i; by = j;
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'T') {
                    tx = i; ty = j;
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'S') {
                    px = i; py = j;
                    grid[i][j] = '.';
                }
            }
        }
        queue<tuple<int,int,int,int>> q;
        q.emplace(bx, by, px, py);
        const vector<vector<int>> dirs{{0,1},{0,-1},{1,0},{-1,0}};
        set<tuple<int,int,int,int>> visited;
        visited.emplace(bx, by, px, py);
        int res = 0;
        while (q.size()) {
            ++res;
            int s = q.size();
            for (int i = 0; i < s; ++i) {
                auto [x, y, cx, cy] = q.front(); q.pop();
                for (const auto& d : dirs) {
                    int nx = x + d[0];
                    int ny = y + d[1];
                    int px = x * 2 - nx;
                    int py = y * 2 - ny;
                    if (nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] == '.'
                        && px >= 0 && px < r && py >= 0 && py < c && grid[px][py] == '.'
                        && !visited.count(make_tuple(nx, ny, px, py))
                        && reachable(grid, px, py, cx, cy, x, y)) {
                        if (nx == tx && ny == ty) {
                            return res;
                        }
                        visited.emplace(nx, ny, px, py);
                        q.emplace(nx, ny, px, py);
                    }
                }
            }
        }
        return -1;
    }
    bool reachable(vector<vector<char>>& grid, int tx, int ty, int cx, int cy, int bx, int by) {
        const vector<vector<int>> dirs{{0,1},{0,-1},{1,0},{-1,0}};
        int r = grid.size(), c = grid[0].size();
        queue<tuple<int,int>> q;
        set<tuple<int,int>> visited;
        visited.emplace(cx, cy);
        q.emplace(cx, cy);
        while (q.size()) {
            int s = q.size();
            for (int i = 0; i < s; ++i) {
                auto [x, y] = q.front(); q.pop();
                for (const auto& d : dirs) {
                    int nx = x + d[0];
                    int ny = y + d[1];
                    if ((nx != bx || ny != by) && nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] == '.' && !visited.count(make_tuple(nx, ny))) {
                        if (nx == tx && ny == ty) {
                            return true;
                        }
                        visited.emplace(nx, ny);
                        q.emplace(nx, ny);
                    }
                }
            }
        }
        return false;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<char>> grid;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {
            {{'#','#','#','#','#','#'},
            {'#','T','#','#','#','#'},
            {'#','.','.','B','.','#'},
            {'#','.','#','#','.','#'},
            {'#','.','.','.','S','#'},
            {'#','#','#','#','#','#'}}
        },
        {

            {{'#','#','#','#','#','#'},
                    {'#','T','#','#','#','#'},
                    {'#','.','.','B','.','#'},
                    {'#','#','#','#','.','#'},
                    {'#','.','.','.','S','#'},
                    {'#','#','#','#','#','#'}}
        },
        {
            {{'#','#','#','#','#','#'},
            {'#','T','.','.','#','#'},
            {'#','.','#','B','.','#'},
            {'#','.','.','.','.','#'},
            {'#','.','.','.','S','#'},
            {'#','#','#','#','#','#'}}
        },
        {
            {{'#','#','#','#','#','#','#'},
            {'#','S','#','.','B','T','#'},
            {'#','#','#','#','#','#','#'}}
        },
        {
            {   {'#','.','.','#','#','#','#','#'},
                {'#','.','.','T','#','.','.','#'},
                {'#','.','.','.','#','B','.','#'},
                {'#','.','.','.','.','.','.','#'},
                {'#','.','.','.','#','.','S','#'},
                {'#','.','.','#','#','#','#','#'}}
        }
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
        -1,
        5,
        -1,
        7
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minPushBox::Solution().minPushBox(dp.grid);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
