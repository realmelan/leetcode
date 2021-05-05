// hitBricks.cpp
// leetcode
//
// Created by  Song Ding on 8/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace hitBricks {
/*
// TODO: copy problem statement here
 803. Bricks Falling When Hit
 Hard
 
 314
 
 95
 
 Favorite
 
 Share
 We have a grid of 1s and 0s; the 1s in a cell represent bricks.  A brick will not drop if and only if it is directly connected to the top of the grid, or at least one of its (4-way) adjacent bricks will not drop.
 
 We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j), the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.
 
 Return an array representing the number of bricks that will drop after each erasure in sequence.
 
 Example 1:
 Input:
 grid = [[1,0,0,0],[1,1,1,0]]
 hits = [[1,0]]
 Output: [2]
 Explanation:
 If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.
 Example 2:
 Input:
 grid = [[1,0,0,0],[1,1,0,0]]
 hits = [[1,1],[1,0]]
 Output: [0,0]
 Explanation:
 When we erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to the last move. So each erasure will cause no bricks dropping.  Note that the erased brick (1, 0) will not be counted as a dropped brick.
 
 
 Note:
 
 The number of rows and columns in the grid will be in the range [1, 200].
 The number of erasures will not exceed the area of the grid.
 It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
 An erasure may refer to a location with no brick - if it does, no bricks drop.
 */

class Solution {
public:
    /**
     * Iterative union-find for each erasure and see the leftover bricks, not efficient.
     *
     * But we can reversely add back the bricks in hits and again see how many bricks will not
     * fall. Note that when adding back a brick, most of the union-find will stop early.
     */
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int row = grid.size();
        int col = grid[0].size();
        
        vector<int> res(hits.size(), 0);
        
        vector<int> original;
        original.reserve(hits.size());
        // first, mark all hits as 0, and see how many bricks are hanging
        for (auto& h : hits) {
            original.push_back(grid[h[0]][h[1]]);
            grid[h[0]][h[1]] = 0;
        }
        
        vector<int> p(row * col, -1);
        vector<int> cnts(row * col, 0);
        int idx = 0;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j, ++idx) {
                if (grid[i][j]) {
                    p[idx] = idx;
                    cnts[idx] = 1;
                }
            }
        }
        
        const static vector<vector<int>> move {{-1,0},{0,-1},{0,1},{1,0}};
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }
                
                int cid = id(i, j, col);
                for (auto& m : move) {
                    int ni = i + m[0];
                    int nj = j + m[1];
                    if (ni >= 0 && ni < row && nj >= 0 && nj < col && grid[ni][nj]) {
                        int nid = id(ni, nj, col);
                        int pid = find(cid, p);
                        int npid = find(nid, p);
                        if (pid > npid) {
                            p[pid] = npid;
                            cnts[npid] += cnts[pid];
                            //cnts[pid] = 0;
                        } else if (pid < npid) {
                            p[npid] = pid;
                            cnts[pid] += cnts[npid];
                            //cnts[npid] = 0;
                        }
                    }
                }
            }
        }
        int cnt = 0;
        for (int j = 0; j < col; ++j) {
            if (p[j] == j) {
                cnt += cnts[j];
            }
        }
        
        
        for (int hi = hits.size() - 1; hi >= 0; --hi) {
            const auto& h = hits[hi];
            if (original[hi]) {
                int hid = id(h[0],h[1],col);
                grid[h[0]][h[1]] = 1;
                cnts[hid] = 1;
                p[hid] = hid;
            
                // DO union-find & count how many bricks are there
                
                for (auto& m : move) {
                    int ni = h[0] + m[0];
                    int nj = h[1] + m[1];
                    if (ni >= 0 && ni < row && nj >= 0 && nj < col && grid[ni][nj]) {
                        int nid = id(ni, nj, col);
                        int pid = find(hid, p);
                        int npid = find(nid, p);
                        if (pid > npid) {
                            p[pid] = npid;
                            cnts[npid] += cnts[pid];
                            //cnts[pid] = 0;
                        } else if (pid < npid) {
                            p[npid] = pid;
                            cnts[pid] += cnts[npid];
                            //cnts[npid] = 0;
                        }
                    }
                }
                
                
                int ncnt = 0;
                for (int j = 0; j < col; ++j) {
                    if (p[j] == j) {
                        ncnt += cnts[j];
                    }
                }
                //int drops = max(ncnt - cnt - 1, 0);
                int drops = ncnt - cnt;
                int pid = find(hid, p);
                if (pid < col) {
                    --drops;
                }
                res[hi] = drops;
                cnt = ncnt;
            }
        }
        return res;
    }
    
private:
    int find(int i, vector<int>& p) {
        /*
        if (p[i] != i) {
            p[i] = find(p[i], p);
        }
         */
        while (p[i] != i) {
            p[i] = p[p[i]];
            i = p[i];
        }
        return i;
    }
    int id(int i, int j, int col) {
        return i * col + j;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> grid;
        vector<vector<int>> hits;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,0,0},{1,0,0},{1,1,1},{1,0,1},{1,1,1}}, {{0,0}}},
        {{{1,1,1},{0,1,0},{0,0,0}},{{0,2},{2,0},{0,1},{1,2}}},
        {{{1,0,0,0},{1,1,1,0}},{{1,0}}},
        {{{1,0,0,0},{1,1,0,0}},{{1,1},{1,0}}},
        {{{1},{1},{1},{1},{1}},{{3,0},{4,0},{1,0},{2,0},{0,0}}},
        {{{1,0,1},{1,1,1}}, {{0,0},{0,2},{1,1}}},
        {{{0,1,1,1,1},{1,1,1,1,0},{1,1,1,1,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}},{{6,0},{1,0},{4,3},{1,2},{7,1},{6,3},{5,2},{5,1},{2,4},{4,4},{7,3}}},
        {{{0,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{0,0,0,1,0,0,1,1,1},{0,0,1,1,0,1,1,1,0},{0,0,0,0,0,1,1,1,1},{0,0,0,0,0,0,0,1,0}},{{1,8},{2,1},{1,4},{3,0},{3,4},{0,7},{1,6},{0,8},{2,5},{3,2},{2,0},{0,2},{0,5},{0,1},{4,8},{3,7},{0,6},{5,7},{5,3},{2,6},{2,2},{5,8},{2,8},{4,0},{3,3},{1,1},{0,0},{4,7},{0,3},{2,4},{3,1},{1,0},{5,2},{3,8},{4,2},{5,0},{1,2},{1,7},{3,6},{4,1},{5,6},{0,4},{5,5},{5,4},{1,5},{4,4},{3,5},{4,6},{2,3},{2,7}}},
        
    };

    vector< vector<int> > answers {
        {9},
        {0,0,1,0},
        {2},
        {0,0},
        {1,0,1,0,0},
        {0,3,0},
        {0,0,0,0,0,0,0,0,0,0,0}, // wrong=[0,1,0,4,0,0,0,0,0,0,0]
        {0,0,0,0,0,0,12,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = hitBricks::Solution().hitBricks(dp.grid, dp.hits);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
