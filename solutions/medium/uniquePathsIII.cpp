// uniquePathsIII.cpp
// leetcode
//
// Created by  Song Ding on 9/22/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace uniquePathsIII {
/*
// TODO: copy problem statement here
 980. Unique Paths III
 Hard
 
 250
 
 38
 
 Favorite
 
 Share
 On a 2-dimensional grid, there are 4 types of squares:
 
 1 represents the starting square.  There is exactly one starting square.
 2 represents the ending square.  There is exactly one ending square.
 0 represents empty squares we can walk over.
 -1 represents obstacles that we cannot walk over.
 Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
 
 
 
 Example 1:
 
 Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
 Output: 2
 Explanation: We have the following two paths:
 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
 Example 2:
 
 Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
 Output: 4
 Explanation: We have the following four paths:
 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
 Example 3:
 
 Input: [[0,1],[2,0]]
 Output: 0
 Explanation:
 There is no path that walks over every empty square exactly once.
 Note that the starting and ending square can be anywhere in the grid.
 
 
 Note:
 
 1 <= grid.length * grid[0].length <= 20
 */

class Solution {
public:
    
    int uniquePathsIII(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        int n = r*c;
        int sid = 0, sx = 0, sy = 0, tid = 0, tst = 0;
        for (int i = 0, id = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++id) {
                if (grid[i][j] == 1) {
                    sx = i;
                    sy = j;
                    sid = id;
                    tst |= 1 << id;
                } else if (grid[i][j] == 2) {
                    tid = id;
                    tst |= 1 << id;
                    grid[i][j] = 0;
                } else if (grid[i][j] == 0) {
                    tst |= 1 << id;
                }
            }
        }
        const vector<int> dirs{0,1,0,-1,0};
        vector<vector<int>> cnt(1<<n, vector<int>(n, 0));
        queue<tuple<int,int,int>> q;
        cnt[1<<sid][sid] = 1;
        q.emplace(sx, sy, 1<<sid);
        while (q.size()) {
            int qn = q.size();
            while (qn--) {
                auto [x,y, st] = q.front();
                q.pop();
                int id = x*c+y;
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i];
                    int ny = y + dirs[i+1];
                    int nid = nx*c+ny;
                    if (nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] == 0
                       && (st & (1<<nid)) == 0) {
                        int nst = st | (1<<nid);
                        if (!cnt[nst][nid]) {
                            q.emplace(nx,ny,nst);
                        }
                        cnt[nst][nid] += cnt[st][id];
                    }
                }
            }
        }
        return cnt[tst][tid];
    }
    
    /**
     * simple DFS, and using grid itself to mark a visited node to -1.
     */
    int uniquePathsIII_dfs(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        int target = 0;
        int srcx = 0, srcy = 0;
        int dstx = 0, dsty = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] == 0) {
                    ++target;
                } else if (grid[i][j] == 1) {
                    srcx = i;
                    srcy = j;
                } else if (grid[i][j] == 2) {
                    dstx = i;
                    dsty = j;
                }
            }
        }
        
        int res = 0;
        dfs(grid, srcx, srcy, dstx, dsty, 0, target, res);
        return res;
    }

private:
    void dfs(vector<vector<int>>& grid, int cx, int cy, int dstx, int dsty, int cv, int t, int& res) {
        static const vector<vector<int>> adjs {{-1,0},{1,0},{0,-1},{0,1}};
        if (cv <= t) {
            int row = grid.size();
            int col = grid[0].size();
            for (auto& adj : adjs) {
                int x = cx+adj[0];
                int y = cy+adj[1];
                if (x >= 0 && x < row && y >= 0 && y < col) {
                    if (grid[x][y] == 0) {
                        grid[x][y] = 3;
                        dfs(grid, x, y, dstx, dsty, cv + 1, t, res);
                        grid[x][y] = 0;
                    } else if (grid[x][y] == 2 && cv == t) {
                        ++res;
                    }
                }
            }
        }
    }
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
        {{{1,0,0,0},{0,0,0,0},{0,0,2,-1}}},
        {{{1,0,0,0},{0,0,0,0},{0,0,0,2}}},
        {{{0,1},{2,0}}},
        {{{-1,-1,0,-1},{1,0,0,0},{0,-1,0,0},{-1,-1,0,-1},{2,0,0,-1}}},
    };

    vector< int > answers {
        2,
        4,
        0,
        0,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = uniquePathsIII::Solution().uniquePathsIII_dfs(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
