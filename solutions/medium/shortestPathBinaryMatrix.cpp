// shortestPathBinaryMatrix.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestPathBinaryMatrix {
/*
// TODO: copy problem statement here
 1091. Shortest Path in Binary Matrix
 Medium
 
 42
 
 2
 
 Favorite
 
 Share
 In an N by N square grid, each cell is either empty (0) or blocked (1).
 
 A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:
 
 Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
 C_1 is at location (0, 0) (ie. has value grid[0][0])
 C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
 If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
 Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.
 
 
 
 Example 1:
 
 Input: [[0,1],[1,0]]
 Output: 2
 Example 2:
 
 Input: [[0,0,0],[1,1,0],[1,1,0]]
 Output: 4
 
 
 Note:
 
 1 <= grid.length == grid[0].length <= 100
 grid[r][c] is 0 or 1
 */

class Solution {
public:
    /**
     * BFS:
     */
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int res = 0;
        int n = grid.size();
        unordered_set<int> cur;
        if (grid[0][0] == 0) {
            ++res;
            cur.insert(0);
        }
        
        int tid = (n-1) * 101 + (n-1);
        unordered_set<int> visited(cur);
        
        const vector<vector<int>> moves {
            {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}
        };
        while (cur.size()) {
            ++res;
            unordered_set<int> next;
            for (auto p : cur) {
                int x = p / 101;
                int y = p % 101;
                for (const auto& m : moves) {
                    int nx = x + m[0];
                    int ny = y + m[1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                        int nid = p + m[0] * 101 + m[1];
                        if (nid == tid) {
                            return res;
                        }
                        if (visited.find(nid) == visited.end()) {
                            next.insert(nid);
                            visited.insert(nid);
                        }
                    }
                }
                
            }
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
        {{{0,1},{1,0}}},
        {{{0,0,0},{1,1,0},{1,1,0}}},
        {{{1,0,0},{1,1,0},{1,1,0}}},
        {{{0,0,1,0,0,0,0},{0,1,0,0,0,0,1},{0,0,1,0,1,0,0},{0,0,0,1,1,1,0},{1,0,0,1,1,0,0},{1,1,1,1,1,0,1},{0,0,1,0,0,0,0}}}
    };

    vector< int > answers {
        2,
        4,
        -1,
        10
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = shortestPathBinaryMatrix::Solution().shortestPathBinaryMatrix(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
