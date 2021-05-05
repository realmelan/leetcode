// cherryPickup.cpp
// leetcode
//
// Created by  Song Ding on 12/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;
/**
 741. Cherry Pickup
 Hard

 523

 39

 Favorite

 Share
 In a N x N grid representing a field of cherries, each cell is one of three possible integers.

  

 0 means the cell is empty, so you can pass through;
 1 means the cell contains a cherry, that you can pick up and pass through;
 -1 means the cell contains a thorn that blocks your way.
  

 Your task is to collect maximum number of cherries possible by following the rules below:

  

 Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through valid path cells (cells with value 0 or 1);
 After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
 When passing through a path cell containing a cherry, you pick it up and the cell becomes an empty cell (0);
 If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
  

  

 Example 1:

 Input: grid =
 [[0, 1, -1],
  [1, 0, -1],
  [1, 1,  1]]
 Output: 5
 Explanation:
 The player started at (0, 0) and went down, down, right right to reach (2, 2).
 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
 Then, the player went left, up, up, left to return home, picking up one more cherry.
 The total number of cherries picked up is 5, and this is the maximum possible.
  

 Note:

 grid is an N by N 2D array, with 1 <= N <= 50.
 Each grid[i][j] is an integer in the set {-1, 0, 1}.
 It is guaranteed that grid[0][0] and grid[N-1][N-1] are not -1.
 */
namespace cherryPickup {

class Solution {
public:
    /**
     * Let S(i,j,k,l) = # of cherries picked along any two paths starting from
     * (0,0) to (i,j) and (0,0) to (k,l).
     * Note, we are only interested in solutions that i+j=k+l;
     *
     * Now let n=i+j, then S(i,j,k,l) = S(i, n-i, k, n-k) = T(n, i, k).
     * also, let k >= i
     */
    int cherryPickup(vector<vector<int>>& grid) {
        int r = grid.size();
        if (r <= 0) {
            return 0;
        }
        int c = grid[0].size();
        if (c <= 0) {
            return 0;
        }
        
        vector<vector<int>> cur(1);
        cur[0].push_back(grid[0][0]);
        for (int n = 1; n < r + c - 1; ++n) {
            vector<vector<int>> next(n+1);
            for (int i = 0; i <= n && i < r; ++i) {
                if (n - i >= c) {
                    continue;
                }
                next[i].resize(n+1, -1);
                if (grid[i][n-i] < 0) {
                    continue;
                }
                for (int k = i; k <= n && k < r; ++k) {
                    if (n - k >= c) {
                        continue;
                    }
                    if (grid[k][n-k] >= 0) {
                        int s = grid[i][n-i];
                        if (k != i) {
                            s += grid[k][n-k];
                        }
                        
                        // there are 4 cases from cur to next[i]
                        // 1, (i-1, n-i) from up, (k-1, n-k), from up
                        // 2, (i, n-1-i) from left, (k-1, n-k) from up
                        // 3, (i-1, n-i) from up, (k, n-1-k) from left
                        // 4, (i, n-1-i) from left, (k, n-1-k) from left
                        int m = -1;
                        if (i > 0) {
                            if (k > 0 && cur[i-1][k-1] > m) {
                                m =  cur[i-1][k-1];
                            }
                            if (k < n && cur[i-1][k] > m) {
                                m = cur[i-1][k];
                            }
                        }
                        if (i < n) {
                            if (k > 0 && cur[i][k-1] > m) {
                                m = cur[i][k-1];
                            }
                            if (k < n && cur[i][k] > m) {
                                m = cur[i][k];
                            }
                        }
                        
                        if (m < 0) {
                            next[i][k] = -1;
                        } else {
                            next[i][k] = m + s;
                        }
                    }
                }
            }
            cur.swap(next);
        }
        if (cur[r-1][c-1] >= 0) {
            return cur[r-1][c-1];
        }
        return 0;
    }
    /**
     * Let S(i,j,k,l) = # of cherries picked along any two paths starting from
     * (0,0) to (i,j) and (0,0) to (k,l).
     *
     * We can expand (i,j,k,l) to (i+1,j,k,l), (i,j+1,k,l), (i,j, k+1, l) or (i,j,k,l+1).
     * BFS can be used to expand by 1 each time, starting from (0,0,0,0).
     *
     * This will timeout.
     */
    int cherryPickup2(vector<vector<int>>& grid) {
        int r = grid.size();
        if (r <= 0) {
            return 0;
        }
        int c = grid[0].size();
        if (c <= 0) {
            return 0;
        }
        
        vector<vector<int>> steps {
            {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}
        };
        // (i,j,k,l)=> set of points on the paths from (0,0) to (i,j) and (k,l).
        // point (i,j) will be presented as integer i*r+j.
        unordered_map<int, unordered_set<int>> cur;
        cur[0] = {};
        if (grid[0][0] > 0) {
            cur[0].insert(0);
        }
        int stepi = 0;
        int total_step = (r << 1) + (c << 1) - 4;
        while (stepi++ < total_step && cur.size()) {
            unordered_map<int, unordered_set<int>> next;
            for (const auto& p : cur) {
                int pid = p.first;
                int r1, c1, r2, c2;
                
                grid_points(pid, r1, c1, r2, c2);
                const auto& s = p.second;
                for (const auto& step : steps) {
                    int r1n = r1 + step[0];
                    int c1n = c1 + step[1];
                    int r2n = r2 + step[2];
                    int c2n = c2 + step[3];
                    
                    
                    int rn = r1n;
                    int cn = c1n;
                    if (step[2] + step[3] > 0) {
                        rn = r2n;
                        cn = c2n;
                    }
                    int npid = pair_id(r1n, c1n, r2n, c2n);
                    int nid = point_id(rn, cn);
                    if (r1n < r && c1n < c && r2n < r && c2n < c && grid[rn][cn] >= 0) {
                        unordered_set<int> pos_path(s);
                        if (grid[rn][cn] > 0) {
                            pos_path.insert(nid);
                        }
                        auto it = next.find(npid);
                        if (it != next.end()) {
                            if (it->second.size() < pos_path.size()) {
                                it->second.swap(pos_path);
                            }
                        } else {
                            next[npid] = pos_path;
                        }
                    }
                }
            }
            cur.swap(next);
        } // end while
        int rpid = (((r-1) * MC + c-1) * MC + r-1) * MC + c-1;
        auto it = cur.find(rpid);
        if (it != cur.end()) {
            return it->second.size();
        }
        return 0;
        
    }
private:
    const int MC = 50;
    int pair_id(int i, int j, int k, int l) {
        if (i < k) {
            std::swap(i, k);
            std::swap(j, l);
        } else if (i == k && j < l) {
            std::swap(j, l);
        }
        return ((i * MC + j) * MC + k) * MC + l;
    }
    void grid_points(int pid, int& i, int& j, int& k, int& l) {
        l = pid % MC; pid /= MC;
        k = pid % MC; pid /= MC;
        j = pid % MC; pid /= MC;
        i = pid;
    }
    int point_id(int i, int j) {
        return i * MC + j;
    }

};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<vector<int>> > grid {
        {{0, 1, -1},{1, 0, -1},{1, 1, 1}},
        {{0,1,1,0,0},{1,1,1,1,0},{-1,1,1,1,-1},{0,1,1,1,0},{1,0,-1,0,0}},
        {{1,1,1,1,0,0,0},{0,0,0,1,0,0,0},{0,0,0,1,0,0,1},{1,0,0,1,0,0,0},{0,0,0,1,0,0,0},{0,0,0,1,0,0,0},{0,0,0,1,1,1,1}}, // our solution doesn't solve this.
        {{1,1,1,0,1,1,0,1,0,1,0,0,0,1,0,-1,0,1,-1,0,0,1,0,1,1,0,1,1,0,0},{0,0,1,0,1,0,1,0,0,-1,0,0,-1,-1,0,1,1,0,-1,1,-1,1,0,0,0,1,0,1,1,-1},{1,0,1,0,0,0,1,-1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1},{0,1,0,1,0,1,-1,1,1,0,0,1,1,0,0,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1},{-1,1,0,-1,1,1,0,0,-1,0,0,0,1,0,-1,0,-1,1,1,-1,1,0,1,-1,-1,0,1,0,1,-1},{0,1,0,0,0,1,0,-1,-1,1,-1,1,-1,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,1,1},{1,0,-1,0,1,0,1,1,-1,0,1,0,1,-1,0,0,0,-1,0,0,0,0,1,0,-1,1,1,0,0,-1},{0,0,1,-1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,0,1,1,0},{1,1,0,0,1,1,1,1,1,0,0,0,1,0,0,1,0,1,1,1,0,1,0,1,0,-1,1,1,0,1},{1,-1,0,1,0,1,0,0,1,1,1,1,-1,1,-1,1,0,0,1,0,1,0,-1,-1,0,0,1,1,0,0},{0,0,-1,1,1,0,1,0,-1,0,0,0,0,0,0,-1,1,0,1,0,0,1,-1,-1,0,1,0,-1,0,1},{1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,0,1,-1,0,1,0,1},{0,0,0,-1,1,0,1,1,0,1,0,-1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,-1,1,0,0},{1,1,1,0,1,0,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,1,1,0,1,1,-1,0,0,0},{1,0,0,1,0,0,0,0,0,1,0,1,0,-1,-1,1,0,0,0,0,1,0,0,1,0,0,0,0,1,1},{0,0,0,0,0,1,0,0,-1,1,0,-1,1,0,1,0,0,1,0,1,-1,0,0,0,0,0,-1,1,1,0},{1,0,-1,0,1,-1,1,1,1,0,-1,0,1,1,1,1,1,1,1,1,1,-1,1,1,-1,0,1,0,1,1},{0,1,0,1,0,0,1,0,0,1,1,0,1,0,0,0,1,0,1,1,1,0,1,1,0,1,1,1,1,-1},{1,0,0,1,0,0,1,1,-1,0,1,-1,1,0,0,0,0,1,0,0,0,0,0,-1,1,1,1,0,0,1},{-1,0,1,1,-1,-1,0,-1,1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,-1,0,1,-1},{0,1,0,0,0,0,0,0,-1,0,1,1,-1,1,0,-1,0,1,1,1,0,0,1,0,0,0,1,0,1,0},{1,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,1,1,0,0,1,1,1,1,0,1,1,0},{0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,0,1,-1,0,1,1,0,0,1,1,0,0},{1,0,0,-1,1,0,1,1,1,1,1,0,0,1,-1,1,0,1,1,0,0,1,1,1,0,-1,0,0,0,0},{0,1,1,1,1,1,0,-1,-1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,-1,1,-1},{0,-1,0,1,0,1,1,0,0,0,1,1,1,0,1,-1,1,0,1,-1,0,-1,1,0,0,0,1,0,1,0},{1,1,0,1,0,0,1,0,1,1,0,0,1,-1,0,0,1,0,-1,1,0,1,1,1,0,1,0,1,1,1},{1,-1,1,0,1,0,1,1,0,1,1,0,0,1,0,1,-1,0,1,0,0,1,1,-1,0,-1,1,0,0,0},{0,0,0,1,-1,0,1,0,1,0,1,1,0,0,1,0,0,1,1,1,0,1,-1,0,1,-1,0,0,1,-1},{1,1,1,0,-1,1,0,0,0,1,1,0,-1,1,-1,1,1,1,-1,1,0,1,1,1,1,0,1,0,0,0}}
    };

    vector< int  > answers {
        5,
        11,
        15,
        83
    };
    int i = 0;

    // TODO: add return type and paramters.
    for (auto& dp : grid) {
        clock_t tstart = clock();
        auto res = cherryPickup::Solution().cherryPickup(dp);
        cout << endl << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
