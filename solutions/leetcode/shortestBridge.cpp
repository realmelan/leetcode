// shortestBridge.cpp
// leetcode
//
// Created by  Song Ding on 5/13/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace shortestBridge {
/*
 934. Shortest Bridge
 Medium
 
 268
 
 18
 
 Favorite
 
 Share
 In a given 2D binary array A, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)
 
 Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.
 
 Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)
 
 
 
 Example 1:
 
 Input: [[0,1],[1,0]]
 Output: 1
 Example 2:
 
 Input: [[0,1,0],[0,0,0],[0,0,1]]
 Output: 2
 Example 3:
 
 Input: [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
 Output: 1
 
 
 Note:
 
 1 <= A.length = A[0].length <= 100
 A[i][j] == 0 or A[i][j] == 1
 */
class Solution {
public:
    int shortestBridge2(vector<vector<int>>& A) {
        static const vector<int> dirs{0,1,0,-1,0};
        int r = A.size(), c = A[0].size();
        queue<pair<int,int>> b;
        queue<pair<int,int>> q;
        for (int i = 0; i < r && q.empty(); ++i) {
            for (int j = 0; j < c; ++j) {
                if (A[i][j]) {
                    q.emplace(i,j);
                    A[i][j] = 2;
                    break;
                }
            }
        }
        while (q.size()) {
            auto[x,y] = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i];
                int ny = y + dirs[i+1];
                if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                    if (A[nx][ny] == 0) {
                        b.emplace(nx, ny);
                        A[nx][ny] = 3;
                    } else if (A[nx][ny] == 1) {
                        q.emplace(nx, ny);
                        A[nx][ny] = 2;
                    }
                }
            }
        }
        int res = 0;
        while (b.size()) {
            ++res;
            int bn = b.size();
            while (bn--) {
                auto[x,y] = b.front();
                b.pop();
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirs[i];
                    int ny = y + dirs[i+1];
                    if (nx >= 0 && nx < r && ny >= 0 && ny < c) {
                        if (A[nx][ny] == 1) {
                            return res;
                        } else if (A[nx][ny] == 0) {
                            b.emplace(nx, ny);
                            A[nx][ny] = 3;
                        }
                    }
                }
            }
        }
        return -1;
    }
    /**
     * use id(x,y) to identify each position
     * use union-find to group two sets of positions, thus ids.
     * then expand one set of positions one step at a time and see whether
     * expanded position is in the other set.
     */
    int shortestBridge(vector<vector<int>>& A) {
        int n = A.size();
        unordered_set<int> g1, g2;
        vector<int> group(n*n, -1);
        int cid = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, ++cid) {
                if (A[i][j]) {
                    group[cid] = cid;
                }
            }
        }
        vector<vector<int>> steps {
            {0,1},{0,-1},{-1,0},{1,0}
        };
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (A[i][j] == 1) {
                    int cid = id(i, j, n);
                    for (const auto& s :steps) {
                        int ni = i + s[0];
                        int nj = j + s[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && A[ni][nj]) {
                            int nid = id(ni, nj, n);
                            int pc = find(cid, group);
                            int pn = find(nid, group);
                            if (pc < pn) {
                                group[pn] = pc;
                            } else {
                                group[pc] = pn;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (A[i][j]) {
                    find(id(i,j,n), group);
                }
            }
        }
        int p = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int cid = id(i, j, n);
                if (group[cid] >= 0) {
                    if (p == -1 || group[cid] == p) {
                        g1.insert(cid);
                        p = group[cid];
                    } else {
                        g2.insert(cid);
                    }
                }
            }
        }
        
        // starting from g1, and expand
        int res = 0;
        unordered_set<int> visited(g1);
        unordered_set<int> cur(g1);
        while (cur.size()) {
            ++res;
            unordered_set<int> next;
            for (auto c : cur) {
                int i = c / n;
                int j = c % n;
                for (const auto& s :steps) {
                    int ni = i + s[0];
                    int nj = j + s[1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                        int nid = id(ni, nj, n);
                        if (A[ni][nj]) {
                            if (g2.find(nid) != g2.end()) {
                                return res - 1;
                            }
                        } else {
                            if (visited.find(nid) == visited.end()) {
                                next.insert(nid);
                                visited.insert(nid);
                            }
                        }
                    }
                }
                
            }
            cur.swap(next);
        }
        
        return 0;
    }

private:
    int id(int x, int y, int c) {
        return x * c + y;
    }
    int find(int cid, vector<int>& group) {
        if (group[cid] != cid) {
            group[cid] = find(group[cid], group);
        }
        return group[cid];
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<vector<int>> > p {
        {{0,1},{1,0}},
        {{0,1,0},{0,0,0},{0,0,1}},
        {{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}},
        {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,0},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,1,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0}}
    };

    vector<  int > answers {
        1,
        2,
        1,
        1
    };
    int i = 1;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = shortestBridge::Solution().shortestBridge2(p[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
