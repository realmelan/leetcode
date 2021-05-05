//
//  numberOfIslands.cpp
//  leetcode
//
//  Created by  Song Ding on 12/13/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace numberOfIslands {
    class Solution {
    public:
        /**
         shrink each land to one 1 in the grid.
         How to shrink:
         
         using disjoint set data structure or union-find
         algorithm.
         */
        int numIslands(vector<vector<char>>& grid) {
            // initialize parents
            int row = grid.size();
            if (row <= 0) {
                return 0;
            }
            int column = grid[0].size();
            if (column <= 0) {
                return 0;
            }
            
            // init parent
            parents.resize(row * column, 0);
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    int id = i * column + j;
                    parents[id] = id;
                }
            }
            
            // merge set
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    if (grid[i][j] == '1') {
                        int id = i * column + j;
                        if (i + 1 < row && grid[i + 1][j] == '1') {
                            merge(id, id + column);
                        }
                        if (i - 1 >= 0 && grid[i - 1][j] == '1') {
                            merge(id - column, id);
                        }
                        if (j + 1 < column && grid[i][j + 1] == '1') {
                            merge(id, id + 1);
                        }
                        if (j - 1 >= 0 && grid[i][j - 1] == '1') {
                            merge(id - 1, id);
                        }
                    }
                }
            }
            
            // count (parent[id] = id && grid[i][j] == 1)
            int count = 0;
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    int id = i * column + j;
                    if (grid[i][j] == '1' && parents[id] == id) {
                        ++count;
                    }
                }
            }
            return count;
        }
        
        int numIslands2(vector<vector<char>>& grid) {
            if (grid.empty() || grid[0].empty()) {
                return 0;
            }
            const vector<vector<int>> dirs {{0,-1},{0,1},{1,0},{-1,0}};
            
            int r = grid.size(), c = grid[0].size();
            auto id = [=](int x, int y) {
                return x * c + y;
            };
            int nid = 0;
            unordered_map<int, int> p;
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j, ++nid) {
                    if (grid[i][j] == '1') {
                        p[nid] = nid;
                    }
                }
            }
            function<int(int)> find = [&](int x) {
                if (p[x] != x) {
                    p[x] = find(p[x]);
                }
                return p[x];
            };
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    if (grid[i][j] != '1') {
                        continue;
                    }
                    for (const auto& d : dirs) {
                        int x = i + d[0];
                        int y = j + d[1];
                        if (x >= 0 && x < r && y >= 0 && y < c && grid[x][y] == '1') {
                            int pid = find(id(i,j));
                            int npid = find(id(x, y));
                            if (npid < pid) {
                                p[pid] = npid;
                            } else {
                                p[npid] = pid;
                            }
                        }
                    }
                }
            }
            int res = 0;
            nid = 0;
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j, ++nid) {
                    if (grid[i][j] == '1' && find(nid) == nid) {
                        ++res;
                    }
                }
            }
            
            return res;
        }
        
    private:
        vector<int> parents;
        
        int find(int i) {
            if (parents[i] != i) {
                parents[i] = find(parents[i]);
            }
            return parents[i];
        }
        void merge(int i, int j) {
            int pi = find(i);
            int pj = find(j);
            if (pi != pj) {
                parents[pj] = pi;
            }
        }
    };
}
/*
int main() {
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}
    };
    cout << numberOfIslands::Solution().numIslands2(grid) << endl;
    
    return 0;
}
 //*/
