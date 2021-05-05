// pacificAtlantic.cpp
// leetcode
//
// Created by  Song Ding on 6/12/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace pacificAtlantic {
/*
 417. Pacific Atlantic Water Flow
 Medium

 964

 180

 Add to List

 Share
 Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

 Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

 Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

 Note:

 The order of returned grid coordinates does not matter.
 Both m and n are less than 150.
  

 Example:

 Given the following 5x5 matrix:

   Pacific ~   ~   ~   ~   ~
        ~  1   2   2   3  (5) *
        ~  3   2   3  (4) (4) *
        ~  2   4  (5)  3   1  *
        ~ (6) (7)  1   4   5  *
        ~ (5)  1   1   2   4  *
           *   *   *   *   * Atlantic

 Return:

 [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
 */
class Solution {
public:
    /**
     * For each cell, determine whether it can flow to pacific or altantic.
     * To compute pacific flow status, starting from the first row and first column
     * and move towards last row last column.
     *
     */
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> res;
        int row = matrix.size();
        if (row <= 0) {
            return res;
        }
        int column = matrix[0].size();
        if (column <= 0) {
            return res;
        }
        
        vector<vector<int>> pac(row);
        pac[0].resize(column, 1);
        for (int r = 1; r < row; ++r) {
            pac[r].push_back(1);
            for (int c = 1; c < column; ++c) {
                pac[r].push_back(0);
            }
        }
        // recursively find all status
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < column; ++c) {
                if (pac[r][c] > 0) {
                    populate(r, c, matrix, pac);
                }
            }
        }
        
        vector<vector<int>> atl(row);
        for (int r = 0; r < row - 1; ++r) {
            for (int c = 0; c < column - 1; ++c) {
                atl[r].push_back(0);
            }
            atl[r].push_back(1);
        }
        atl[row - 1].resize(column, 1);
        for (int r = row - 1; r >= 0; --r) {
            for (int c = column - 1; c >= 0; --c) {
                if (atl[r][c] > 0) {
                    populate(r, c, matrix, atl);
                }
            }
        }
        
        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < column; ++c) {
                if (pac[r][c] == 1 && atl[r][c] == 1) {
                    res.push_back(make_pair(r, c));
                }
            }
        }
        return res;
    }
    /**
     * 0 = uninitialized
     * 1 = able to reach
     */
    void populate(int r, int c, const vector<vector<int>>& m, vector<vector<int>>& memo) {
        int row = m.size();
        int column = m[0].size();
        int steps[] = {-1, 1};
        for (auto step : steps) {
            int nr = r + step;
            if (nr >= 0 && nr < row && m[nr][c] >= m[r][c] && memo[nr][c] == 0) {
                memo[nr][c] = 1;
                populate(nr, c, m, memo);
            }
            
            int nc = c + step;
            if (nc >= 0 && nc < column && m[r][nc] >= m[r][c] && memo[r][nc] == 0) {
                memo[r][nc] = 1;
                populate(r, nc, m, memo);
            }
        } // end for
    }
    
    vector<vector<int>> pacificAtlantic2(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return {};
        }
        static const vector<vector<int>> dirs{{1,0},{0,1},{-1,0},{0,-1}};
        int r = matrix.size(), c = matrix[0].size();
        vector<vector<int>> res, mark(r, vector<int>(c, 0));
        set<vector<int>> cur;
        for (int i = 0; i < c; ++i) {
            cur.insert({0, i});
            mark[0][i] |= 1;
        }
        for (int i = 1; i < r; ++i) {
            cur.insert({i,0});
            mark[i][0] |= 1;
        }
        while (cur.size()) {
            set<vector<int>> next;
            for (auto& v : cur) {
                for (auto& m : dirs) {
                    int x = v[0] + m[0];
                    int y = v[1] + m[1];
                    if (x >= 0 && x < r && y >= 0 && y < c && matrix[x][y] >= matrix[v[0]][v[1]] && !(mark[x][y]&1)) {
                        mark[x][y] |= 1;
                        next.insert({x,y});
                    }
                }
            }
            cur.swap(next);
        }
        
        cur.clear();
        for (int i = 0; i < r; ++i) {
            cur.insert({i, c-1});
            mark[i][c-1] |= 2;
        }
        for (int i = 0; i < c-1; ++i) {
            cur.insert({r-1,i});
            mark[r-1][i] |= 2;
        }
        while (cur.size()) {
            set<vector<int>> next;
            for (auto& v : cur) {
                for (auto& m : dirs) {
                    int x = v[0] + m[0];
                    int y = v[1] + m[1];
                    if (x >= 0 && x < r && y >= 0 && y < c && matrix[x][y] >= matrix[v[0]][v[1]] && !(mark[x][y]&2)) {
                        mark[x][y] |= 2;
                        next.insert({x,y});
                    }
                }
            }
            cur.swap(next);
        }
        
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (mark[i][j] == 3) {
                    res.push_back({i,j});
                }
            }
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> matrix {
       {1,2,3},{8,9,4},{7,6,5} //{12,7,7,14,6,17,12,17,8,18,9,5},{6,8,12,5,3,6,2,14,19,6,18,13},{0,6,3,8,8,10,8,17,13,13,13,12},{5,6,8,8,15,16,19,14,7,11,2,3},{7,18,2,7,10,10,3,14,13,15,15,7},{18,6,19,4,12,3,3,2,6,6,19,6},{3,18,5,16,19,6,3,12,6,0,14,11},{9,10,17,12,10,11,11,9,0,0,12,0},{4,13,3,0,4,12,9,5,6,17,10,11},{18,3,5,0,8,19,18,4,8,19,1,3},{16,2,14,6,4,14,7,2,9,7,13,18},{0,16,19,16,16,4,15,19,7,0,3,16},{13,8,12,8,2,3,5,18,6,15,18,6},{4,10,8,1,16,0,6,0,14,10,11,8},{7,1,3,4,11,12,9,0,6,2,17,5},{1,16,6,1,0,19,11,1,5,7,8,2},{4,1,14,13,14,7,3,7,1,9,15,18},{14,11,6,14,14,14,4,0,11,17,1,9},{3,14,2,10,3,1,9,16,1,13,0,15},{8,9,13,5,5,7,10,1,4,5,0,9},{13,16,15,5,17,6,16,13,5,7,3,15},{5,1,12,19,3,13,0,0,3,10,6,13},{12,17,9,16,16,6,2,6,12,15,14,16},{7,7,0,6,4,15,1,7,17,5,2,12},{3,17,0,2,4,5,11,7,16,16,16,13},{3,7,16,11,2,16,14,9,16,17,10,3},{12,18,17,17,5,15,1,2,12,12,5,7},{11,10,10,0,11,7,17,14,5,15,2,16},{7,19,14,7,6,2,4,16,11,19,14,14},{6,17,6,6,6,15,9,12,8,13,1,7},{16,3,15,0,18,17,0,11,3,16,11,12},{15,12,4,6,19,15,17,7,3,9,2,11}
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = pacificAtlantic::Solution().pacificAtlantic2(matrix);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
