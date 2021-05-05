// maxAreaOfIsland.cpp
// leetcode
//
// Created by  Song Ding on 5/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxAreaOfIsland {
/*
// TODO: copy problem statement here
 695. Max Area of Island
 Medium
 
 1087
 
 62
 
 Favorite
 
 Share
 Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
 
 Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
 
 Example 1:
 
 [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.
 Example 2:
 
 [[0,0,0,0,0,0,0,0]]
 Given the above grid, return 0.
 Note: The length of each dimension in the given grid does not exceed 50.
 */

class Solution {
public:
    /**
     * Union-Find:
     */
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res = 0;
        int r = grid.size();
        if (r <= 0) {
            return res;
        }
        int c = grid[0].size();
        if (c <= 0) {
            return res;
        }
        
        int id = 0;
        vector<int> group(r*c, -1);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++id) {
                if (grid[i][j]) {
                    group[id] = id;
                }
            }
        }
        
        id = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++id) {
                if (grid[i][j] == 0) {
                    continue;
                }
                if (i+1 < r && grid[i+1][j]) {
                    int nid = id + c;
                    int pid = find(id, group);
                    int npid = find(nid, group);
                    if (pid < npid) {
                        group[npid] = pid;
                    } else {
                        group[pid] = npid;
                    }
                }
                
                if (j+1 < c && grid[i][j+1]) {
                    int nid = id + 1;
                    int pid = find(id, group);
                    int npid = find(nid, group);
                    if (pid < npid) {
                        group[npid] = pid;
                    } else {
                        group[pid] = npid;
                    }
                }
            }
        }
        id = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++id) {
                if (grid[i][j]) {
                    find(id, group);
                }
            }
        }
        
        unordered_map<int, int> count;
        for (auto i : group) {
            if (i >= 0) {
                ++count[i];
            }
        }
        for (const auto& p : count) {
            res = max(res, p.second);
        }
        return res;
    }
        

private:
    int find(int id, vector<int>& group) {
        if (group[id] != id) {
            group[id] = find(group[id], group);
        }
        return group[id];
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
        {{{0,0,1,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0}}},
        {{{0,0,0,0,0,0,0,0}}}
    };

    vector< int > answers {
        6,
        0
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxAreaOfIsland::Solution().maxAreaOfIsland(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
