// colorBorder.cpp
// leetcode
//
// Created by  Song Ding on 6/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace colorBorder {
/*
// TODO: copy problem statement here
 1034. Coloring A Border
 Medium
 
 43
 
 100
 
 Favorite
 
 Share
 Given a 2-dimensional grid of integers, each value in the grid represents the color of the grid square at that location.
 
 Two squares belong to the same connected component if and only if they have the same color and are next to each other in any of the 4 directions.
 
 The border of a connected component is all the squares in the connected component that are either 4-directionally adjacent to a square not in the component, or on the boundary of the grid (the first or last row or column).
 
 Given a square at location (r0, c0) in the grid and a color, color the border of the connected component of that square with the given color, and return the final grid.
 
 
 
 Example 1:
 
 Input: grid = [[1,1],[1,2]], r0 = 0, c0 = 0, color = 3
 Output: [[3, 3], [3, 2]]
 Example 2:
 
 Input: grid = [[1,2,2],[2,3,2]], r0 = 0, c0 = 1, color = 3
 Output: [[1, 3, 3], [2, 3, 3]]
 Example 3:
 
 Input: grid = [[1,1,1],[1,1,1],[1,1,1]], r0 = 1, c0 = 1, color = 2
 Output: [[2, 2, 2], [2, 1, 2], [2, 2, 2]]
 
 
 Note:
 
 1 <= grid.length <= 50
 1 <= grid[0].length <= 50
 1 <= grid[i][j] <= 1000
 0 <= r0 < grid.length
 0 <= c0 < grid[0].length
 1 <= color <= 1000
 */

class Solution {
public:
    /**
     * expand from r0, c0. For a grid, only if one of its
     */
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
        int r = grid.size();
        int c = grid[0].size();
        
        int oc = grid[r0][c0];
        vector<vector<int>> res(grid);
        
        const vector<vector<int>> steps {
            {0,1},{0,-1},{1,0},{-1,0}
        };
        unordered_set<vector<int>, vhash> border;
        unordered_set<vector<int>, vhash> cur{{r0,c0}};
        unordered_set<vector<int>, vhash> visited(cur);
        while (cur.size()) {
            unordered_set<vector<int>, vhash> next;
            for (const auto& p : cur) {
                if (atBoundary(p[0], p[1], r, c)) {
                    border.insert(p);
                }
                
                for (const auto& st : steps) {
                    int x = p[0] + st[0];
                    int y = p[1] + st[1];
                    if (withinBoundary(x, y, r, c)) {
                        if (grid[x][y] != oc) {
                            border.insert(p);
                        } else if (visited.find({x,y}) == visited.end()) {
                            visited.insert({x,y});
                            next.insert({x,y});
                        }
                    }
                }
            }
            cur.swap(next);
        }
        for (auto& p : border) {
            res[p[0]][p[1]] = color;
        }
        return res;
    }

private:
    struct vhash {
        size_t operator()(const vector<int>& p) const {
            return p[0] * 50 + p[1];
        }
    };
    bool atBoundary(int x, int y, int r, int c) {
        return x <= 0 || x >= r-1 || y <= 0 || y >= c-1;
    }
    bool withinBoundary(int x, int y, int r, int c) {
        return (x >= 0 && x < r) && (y >= 0 && y < c);
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> grid;
        int r0;
        int c0;
        int color;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,1},{1,2}}, 0, 0, 3},
        {{{1,2,2},{2,3,2}}, 0, 1, 3},
        {{{1,1,1},{1,1,1},{1,1,1}}, 1, 1, 2}
    };

    vector< vector<vector<int>> > answers {
        {{3, 3}, {3, 2}},
        {{1, 3, 3}, {2, 3, 3}},
        {{2, 2, 2}, {2, 1, 2}, {2, 2, 2}}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = colorBorder::Solution().colorBorder(dp.grid, dp.r0, dp.c0, dp.color);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
