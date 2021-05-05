// numEnclaves.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace numEnclaves {
/*
// TODO: copy problem statement here
 1020. Number of Enclaves
 Medium
 
 79
 
 11
 
 Favorite
 
 Share
 Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)
 
 A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.
 
 Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.
 
 
 
 Example 1:
 
 Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
 Output: 3
 Explanation:
 There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
 Example 2:
 
 Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
 Output: 0
 Explanation:
 All 1s are either on the boundary or can reach the boundary.
 
 
 Note:
 
 1 <= A.length <= 500
 1 <= A[i].length <= 500
 0 <= A[i][j] <= 1
 All rows have the same size.
 */

class Solution {
public:
    /**
     * union-find algorithm
     * DFS search is faster.
     */
    int numEnclaves(vector<vector<int>>& A) {
        int res = 0;
        int r = A.size();
        int c = A[0].size();
        unordered_map<int, int> roots;
        roots.insert(make_pair(INT_MAX, INT_MAX));
        int cid = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++cid) {
                if (A[i][j] == 1) {
                    roots[cid] = cid;
                    if ((i == 0) || (j == 0) || (i == (r-1)) || (j == (c-1))) {
                        roots[cid] = INT_MAX;
                    }
                }
            }
        }
        
        const vector<vector<int>> steps {
            {0,1},{0,-1},{1,0},{-1,0}
        };
        cid = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++cid) {
                if (A[i][j] == 1) {
                    for (const auto& step : steps) {
                        int ni = i + step[0];
                        int nj = j + step[1];
                        if (ni >= 0 && ni < r && nj >= 0 && nj < c && A[ni][nj] == 1) {
                            int nid = cid + c * step[0] + step[1];
                            int cpid = find(cid, roots);
                            int npid = find(nid, roots);
                            if (cpid < npid) {
                                roots[cpid] = npid;
                            } else {
                                roots[npid] = cpid;
                            }
                        }
                    }
                }
            }
        }
        cid = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++cid) {
                if (A[i][j] == 1) {
                    find(cid, roots);
                }
            }
        }
        
        cid = 0;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++cid) {
                if (A[i][j] == 1 && roots[cid] != INT_MAX) {
                    ++res;
                }
            }
        }
        return res;
    }

private:
    int find(int id, unordered_map<int, int>& roots) {
        if (roots[id] != id) {
            roots[id] = find(roots[id], roots);
        }
        return roots[id];
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0}}},
        {{{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}}},
        {{{0,0,0,1,1,1,0,1,0,0},{1,1,0,0,0,1,0,1,1,1},{0,0,0,1,1,1,0,1,0,0},{0,1,1,0,0,0,1,0,1,0},{0,1,1,1,1,1,0,0,1,0},{0,0,1,0,1,1,1,1,0,1},{0,1,1,0,0,0,1,1,1,1},{0,0,1,0,0,1,0,1,0,1},{1,0,1,0,1,1,0,0,0,0},{0,0,0,0,1,1,0,0,0,1}}}
    };

    vector< int > answers {
        3,
        0,
        3
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = numEnclaves::Solution().numEnclaves(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
