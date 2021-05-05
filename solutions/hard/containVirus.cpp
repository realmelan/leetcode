// containVirus.cpp
// leetcode
//
// Created by  Song Ding on 9/13/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace containVirus {
/*
// TODO: copy problem statement here
 749. Contain Virus
 Hard
 
 51
 
 173
 
 Favorite
 
 Share
 A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.
 
 The world is modeled as a 2-D array of cells, where 0 represents uninfected cells, and 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.
 
 Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region -- the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night. There will never be a tie.
 
 Can you save the day? If so, what is the number of walls required? If not, and the world becomes fully infected, return the number of walls used.
 
 Example 1:
 Input: grid =
 [[0,1,0,0,0,0,0,1],
 [0,1,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,0]]
 Output: 10
 Explanation:
 There are 2 contaminated regions.
 On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:
 
 [[0,1,0,0,0,0,1,1],
 [0,1,0,0,0,0,1,1],
 [0,0,0,0,0,0,1,1],
 [0,0,0,0,0,0,0,1]]
 
 On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
 Example 2:
 Input: grid =
 [[1,1,1],
 [1,0,1],
 [1,1,1]]
 Output: 4
 Explanation: Even though there is only one cell saved, there are 4 walls built.
 Notice that walls are only built on the shared boundary of two different cells.
 Example 3:
 Input: grid =
 [[1,1,1,0,0,0,0,0,0],
 [1,0,1,0,1,1,1,1,1],
 [1,1,1,0,0,0,0,0,0]]
 Output: 13
 Explanation: The region on the left only builds two new walls.
 Note:
 The number of rows and columns of grid will each be in the range [1, 50].
 Each grid[i][j] will be either 0 or 1.
 Throughout the described process, there is always a contiguous viral region that will infect strictly more uncontaminated squares in the next round.
 */

class Solution {
public:
    /**
     * Union-find:
     *  find each region and # of cells that would be affected.
     *  keep both virus and would-be infected cells during union-find.
     *
     * How to deal with virus expansion?
     *  keep track of all cells that would be infected by a region.
     *  then, all these cells would be new virus front line, and again
     *  find all cells that would be infected.
     *
     * # of walls can be computed based on cells that would be infected:
     *  all adjacent cells that are virus should be built a wall (but what
     *  if two fronts are both virus?)
     *
     * Regions may union into a single region!
     */
    int containVirus(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        
        vector<int> p(id(row-1, col-1)+1);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                p[id(i,j)] = id(i,j);
            }
        }
        
        static const vector<vector<int>> adjs {{-1,0},{1,0},{0,-1},{0,1}};
        unordered_map<int, unordered_set<int>> infect;
        //vector<int> walls(id(row-1, col-1)+1, 0);
        unordered_map<int, int> walls;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if (grid[i][j] == 1) {
                    int cid = id(i,j);
                    for (const auto& adj : adjs) {
                        int ni = i + adj[0];
                        int nj = j + adj[1];
                        if (ni >= 0 && ni < row && nj >= 0 && nj < col) {
                            int nid = id(ni, nj);
                            int pid = find(cid, p);
                            int npid = find(nid, p);
                            if (grid[ni][nj] == 0) {
                                infect[pid].insert(nid);
                                walls[pid] += 1;
                            } else if (npid < pid) {
                                p[pid] = npid;
                                infect[npid].insert(infect[pid].begin(), infect[pid].end());
                                infect[pid].clear();
                                walls[npid] += walls[pid];
                                walls[pid] = 0;
                            } else if (npid > pid) {
                                p[npid] = pid;
                                infect[pid].insert(infect[npid].begin(), infect[npid].end());
                                infect[npid].clear();
                                walls[pid] += walls[npid];
                                walls[npid] = 0;
                            }
                        }
                    }
                } // when cell is a virus
            }
        }
        
        // find out list of regions
        unordered_set<int> regions;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int cid = id(i,j);
                if (grid[i][j] == 1 && p[cid] == cid) {
                    regions.insert(cid);
                }
            }
        }
        
        int res = 0;
        // loop until all virus regions are blocked.
        unordered_set<int> blocked;
        while (true) {
            int max_infect = 0;
            int mid = -1;
            for (auto it = regions.begin(); it != regions.end();) {
                int rid = *it;
                if (infect[rid].empty()) {
                    it = regions.erase(it);
                    continue;
                } else if (infect[rid].size() > max_infect) {
                    max_infect = infect[rid].size();
                    mid = rid;
                }
                ++it;
            }
            if (max_infect == 0) {
                break;
            }
            
            res += walls[mid];
            regions.erase(mid);
            blocked.insert(mid);
            // expand other region
            unordered_map<int, unordered_set<int>> ninfect;
            unordered_map<int, int> nwalls;
            
            // mark all infected cells 1
            for (auto rid : regions) {
                for (auto cellid : infect[rid]) {
                    int i = 0, j = 0;
                    toxy(cellid, i, j);
                    grid[i][j] = 1;
                    p[cellid] = rid;
                }
            }
            
            unordered_set<int> marked;
            for (auto rid : regions) {
                // update infect again for next day
                int i = 0;
                for (auto cellid : infect[rid]) {
                    if (marked.find(cellid) != marked.end()) {
                        continue;
                    }
                    marked.insert(cellid);
                    int i = 0, j = 0;
                    toxy(cellid, i, j);
                    for (const auto& adj : adjs) {
                        int ni = i + adj[0];
                        int nj = j + adj[1];
                        int pid = find(rid, p);
                        if (ni >= 0 && ni < row && nj >= 0 && nj < col) {
                            int nid = id(ni,nj);
                            if (grid[ni][nj] == 0) {
                                ++nwalls[pid];
                                ninfect[pid].insert(nid);
                            } else {
                                int npid = find(nid, p);
                                if (blocked.find(npid) != blocked.end() || npid == pid) {
                                    continue; // a blocked virus or self-region
                                }
                                // it may be a virus from another region!
                                // union them
                                if (npid < pid) {
                                    p[pid] = npid;
                                    ninfect[npid].insert(ninfect[pid].begin(), ninfect[pid].end());
                                    ninfect[pid].clear();
                                    nwalls[npid] += nwalls[pid];
                                    nwalls[pid] = 0;
                                } else {
                                    p[npid] = pid;
                                    ninfect[pid].insert(ninfect[npid].begin(), ninfect[npid].end());
                                    ninfect[npid].clear();
                                    nwalls[pid] += nwalls[npid];
                                    nwalls[npid] = 0;
                                }
                            }
                        }
                    }
                }
            }
            infect.swap(ninfect);
            walls.swap(nwalls);
        }
        return res;
    }
private:
    int id(int r, int c) {
        return (r << 6) | c;
    }
    void toxy(int id, int& x, int& y) {
        y = id & 0x3F;
        x = id >> 6;
    }
    int find(int id, vector<int>& p) {
        if (p[id] != id) {
            p[id] = find(p[id], p);
        }
        return p[id];
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
        {{  {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,1},
            {1,1,0,1,1},
            {0,1,1,1,0},
        }},
        {{  {0,1,0,0,0,0,0,1},
            {0,1,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,1},
            {0,0,0,0,0,0,0,0}
        }},
        {{  {1,1,1},
            {1,0,1},
            {1,1,1}
        }},
        
        {{  {1,1,1,0,0,0,0,0,0},
            {1,0,1,0,1,1,1,1,1},
            {1,1,1,0,0,0,0,0,0}
        }},
        {{
          {0,0,0,0,0,0,0,0,0,0},
          {0,0,0,0,0,0,0,1,0,0},
          {1,0,0,0,0,0,0,0,0,0},
          {0,0,1,0,0,0,1,0,0,0},
          {0,0,0,0,0,0,1,0,0,0},
          {0,0,0,0,0,0,0,0,0,0},
          {0,0,0,0,0,0,0,0,0,0},
          {0,0,0,0,0,0,0,0,1,0},
          {0,0,0,0,1,0,1,0,0,0},
          {0,0,0,0,0,0,0,0,0,0}
        }},
    };

    vector< int > answers {
        14,
        10,
        4,
        13,
        56
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = containVirus::Solution().containVirus(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
