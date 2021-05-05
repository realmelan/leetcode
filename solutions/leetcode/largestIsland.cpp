// largestIsland.cpp
// leetcode
//
// Created by  Song Ding on 10/15/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace largestIsland {

class Solution {
public:
    /**
     * First of all, using disjoint set (union-find) to group cells into
     * islands, and calculate the size of each island.
     *
     * For all empty cells, check the 4 adjacent cells and see whether they belong to
     * any island, and add the areas together if there are any islands in adjacent cells.
     */
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> island(n * n, -1);
        int id = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, ++id) {
                if (grid[i][j] == 1) {
                    island[id] = id;
                }
            }
        }
        
        id = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, ++id) {
                if (grid[i][j] == 0) {
                    continue;
                }
                
                if (i - 1 >= 0 && grid[i-1][j] == 1) {
                    int nid = id - n;
                    int idp = find(island, id);
                    int nidp = find(island, nid);
                    if (idp < nidp) {
                        island[nidp] = idp;
                    } else {
                        island[idp] = nidp;
                    }
                }
                if (i + 1 < n && grid[i+1][j] == 1) {
                    int nid = id + n;
                    int idp = find(island, id);
                    int nidp = find(island, nid);
                    if (idp < nidp) {
                        island[nidp] = idp;
                    } else {
                        island[idp] = nidp;
                    }
                }
                
                if (j - 1 >= 0 && grid[i][j-1] == 1) {
                    int nid = id - 1;
                    int idp = find(island, id);
                    int nidp = find(island, nid);
                    if (idp < nidp) {
                        island[nidp] = idp;
                    } else {
                        island[idp] = nidp;
                    }
                }
                if (j + 1 < n && grid[i][j+1] == 1) {
                    int nid = id + 1;
                    int idp = find(island, id);
                    int nidp = find(island, nid);
                    if (idp < nidp) {
                        island[nidp] = idp;
                    } else {
                        island[idp] = nidp;
                    }
                }
            }
        }
        for (int i = 0; i < n*n; ++i) {
            if (island[i] != -1) {
                find(island, i);
            }
        }
        map<int, int> area;
        for (int i : island) {
            if (i != -1) {
                ++area[island[i]];
            }
        }
        
        int res = 0;
        for (const auto& p : area) {
            if (res < p.second) {
                res = p.second;
            }
        }
        id = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, ++id) {
                if (grid[i][j] == 1) {
                    continue;
                }
                
                unordered_set<int> added;
                int t = 1;
                if (i - 1 >= 0 && grid[i-1][j] == 1) {
                    int nid = id - n;
                    int is = island[nid];
                    if (added.find(is) == added.end()) {
                        t += area[is];
                        added.insert(is);
                    }
                }
                if (i + 1 < n && grid[i+1][j] == 1) {
                    int nid = id + n;
                    int is = island[nid];
                    if (added.find(is) == added.end()) {
                        t += area[is];
                        added.insert(is);
                    }
                }
                
                if (j - 1 >= 0 && grid[i][j-1] == 1) {
                    int nid = id - 1;
                    int is = island[nid];
                    if (added.find(is) == added.end()) {
                        t += area[is];
                        added.insert(is);
                    }
                }
                if (j + 1 < n && grid[i][j+1] == 1) {
                    int nid = id + 1;
                    int is = island[nid];
                    if (added.find(is) == added.end()) {
                        t += area[is];
                        added.insert(is);
                    }
                }
                
                if (t > res) {
                    res = t;
                }
            }
        }
        return res;
    }
    
    int largestIsland2(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        const vector<vector<int>> dirs {{0,1},{0,-1},{1,0},{-1,0}};
        int r = grid.size(), c = grid[0].size();
        int marea = 0;
        vector<int> p(r*c, -1);
        unordered_map<int, int> area;
        for (int i = 0, id = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j, ++id) {
                if (grid[i][j]) {
                    p[id] = id;
                    area[id] = 1;
                    marea = 1;
                }
            }
        }
        
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j]) {
                    for (const auto& d : dirs) {
                        int x = i + d[0];
                        int y = j + d[1];
                        if (x >= 0 && x < r && y >= 0 && y < c && grid[x][y]) {
                            int pid = find(i*c+j, p);
                            int npid = find(x*c+y, p);
                            if (pid < npid) {
                                p[npid] = pid;
                                area[pid] += area[npid];
                                area[npid] = 0;
                                marea = max(marea, area[pid]);
                            } else if (npid < pid) {
                                p[pid] = npid;
                                area[npid] += area[pid];
                                area[pid] = 0;
                                marea = max(marea, area[npid]);
                            }
                        }
                    }
                }
            }
        }
        
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j] == 0) {
                    set<int> visited;
                    int t = 1;
                    for (const auto& d : dirs) {
                        int x = i + d[0];
                        int y = j + d[1];
                        if (x >= 0 && x < r && y >= 0 && y < c && grid[x][y]) {
                            int pid = find(x*c+y, p);
                            if (!visited.count(pid)) {
                                t += area[pid];
                                visited.insert(pid);
                            }
                        }
                    }
                    marea = max(marea, t);
                }
            }
        }
        
        return marea;
    }
    int find(int i, vector<int>& p) {
        if (i != p[i]) {
            p[i] = find(p[i], p);
        }
        return p[i];
    }

private:
    int find(vector<int>& island, int id) {
        if (island[id] != id) {
            island[id] = find(island, island[id]);
        }
        return island[id];
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> grid {
        //{1,0},{0,1}
        {1,1},{1,0}
        //{1,1},{1,1}
        //{1,0,0,1,1},{1,0,0,1,0},{1,1,1,1,1},{1,1,1,0,1},{0,0,0,1,0}
        //{1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,1,1,1,0,1,0,0,1,0,1,0,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,1},{0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,1,0,0,0},{1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,1,0,0,1,0,1,1,0,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,0,0,0,0},{0,0,0,1,0,1,0,0,0,1,1,0,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,1,1,0},{0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,0,0,1,1,1,0,1,0,1,0,1,0,0,0,1,1,1,1,0,1,1,0,1,0,1,0,1,1},{0,0,0,1,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,0,1,0,1,1,0,0,1,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1},{0,0,0,0,0,1,0,0,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,0,0,1},{1,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1},{1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,0,1,0,0,0,1,1,1},{1,0,1,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,0,1,1,1,0,1},{1,1,1,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,1,1,0,0,1,1,0,1},{0,1,0,0,1,1,1,1,1,1,0,1,0,0,1,0,1,1,0,0,1,1,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,1,1,0,0},{0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,1,1,1,0,0,0,1,0,0,1,0,1,1,0,1,1,0,1,0,1,1,1,0,0},{0,0,0,0,1,0,1,0,1,1,1,1,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,1,1,0,0,1,1,1,0,1,0},{0,1,1,0,0,1,1,0,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0},{1,0,1,1,0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1},{0,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0},{0,1,1,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,0,0,0,1,1},{0,0,1,1,1,1,0,1,1,0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,0,1,0,0,1,1,1,0,0,0,0,1},{1,0,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,1,0},{0,1,0,1,1,1,0,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,0,0,1,0,1,0,0,0,1,1,0,1,1,0,1},{1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1,0,1,0,0,0,1,0,0,1,1,0,0,0,0,1},{0,1,1,0,1,1,1,1,0,0,1,0,0,1,1,0,1,1,0,0,1,0,1,1,1,0,0,1,0,1,1,1,1,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,1},{0,0,0,0,0,1,1,1,0,1,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1},{1,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,0,1,1,0,1,1,0,0,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,1,0,0,1,0,1,0,0,1},{1,0,1,0,1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0},{0,1,0,0,1,0,1,1,1,0,0,1,1,0,1,1,0,1,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,0,1,1,1,0,0,0,0,1,0,0,1,0,0},{0,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,0,1,0,1,1,0,1,1,0,1,1,1,1,0,0,1,0,1,1,1},{0,1,0,0,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,1,1,1,1,0,0,1,0,0,0,1,1,0,1,0,1,0},{1,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0},{0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,0,1,1,0,1,1,0,0,0,0,0,0,1,0,0,1},{0,1,1,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,1,1},{0,1,1,0,0,1,0,1,1,1,0,0,1,1,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,0,1,1,1,1,0,0,0,0,1,1,0,1,0,0,0,1,1,0,0},{0,0,1,1,1,0,1,0,1,1,1,0,0,1,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,1},{1,1,1,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,0,0,1,1,1,1,1},{1,1,1,0,1,1,0,0,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,1,1,0,0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,0,0,0,1,1,1,0,0},{1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,1,1,0,0,1,0,0,1,1,1,1,1,0,1,0,0,0,1,1},{0,0,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,1,1,0,1,0,1,1,0,1,0,0,1,1,1,0,1,0,1,0,0,0,0,0,1,0,1,1,0,1,1,0,1},{1,1,1,0,1,0,0,1,0,1,0,1,1,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,0,1,0,0,1,1,1},{0,1,0,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,1,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1},{0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,1,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,1,0},{0,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1,0,0,0,1,1,1,0,1,1,1,0,0,0,0,1,1,0,1,1},{0,0,1,1,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0},{1,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,0,1,1,0,1,0,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,1,0,1,0},{1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,0,1,1,0,0,1,1,1,0,0,1,0,1,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0},{1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,0,1,0,1},{0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,1,1,1,1,0,0,0},{1,0,0,0,0,1,0,0,1,1,0,1,1,0,0,1,0,0,0,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1,1,0,0,0,1,1},{1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,0,1,1,1,0,1,0,0,1,0,0,0,1,0,1,1,0,1,0,0,0,1,1,0,0,0,0,1,0,1,0,1}
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = largestIsland::Solution().largestIsland2(grid);
    //cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
