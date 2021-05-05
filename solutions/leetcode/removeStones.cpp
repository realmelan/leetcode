// removeStones.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace removeStones {
/*
// TODO: copy problem statement here
 947. Most Stones Removed with Same Row or Column
 Medium
 
 399
 
 110
 
 Favorite
 
 Share
 On a 2D plane, we place stones at some integer coordinate points.  Each coordinate point may have at most one stone.
 
 Now, a move consists of removing a stone that shares a column or row with another stone on the grid.
 
 What is the largest possible number of moves we can make?
 
 
 
 Example 1:
 
 Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
 Output: 5
 Example 2:
 
 Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
 Output: 3
 Example 3:
 
 Input: stones = [[0,0]]
 Output: 0
 
 
 Note:
 
 1 <= stones.length <= 1000
 0 <= stones[i][j] < 10000
 */

class Solution {
public:
    /**
     * each connected group of stones can be removed until one
     * is left.
     *
     * Use union-find to group stones, and result would be # of total
     * stones - # of groups.
     */
    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, int> group;
        unordered_map<int, unordered_set<int>> xs, ys;
        for (const auto& v : stones) {
            int vid = id(v[0], v[1]);
            group[vid] = vid;
            
            xs[v[0]].insert(vid);
            ys[v[1]].insert(vid);
        }
        
        for (const auto& p : xs) {
            int ming = INT_MAX;
            for (auto vid : p.second) {
                ming = min(ming, find(vid, group));
            }
            for (auto vid : p.second) {
                group[vid] = ming;
            }
        }
        for (const auto& p : ys) {
            int ming = INT_MAX;
            unordered_set<int> gs;
            for (auto vid : p.second) {
                int gid = find(vid, group);
                ming = min(ming, gid);
                gs.insert(gid);
            }
            for (auto gid : gs) {
                group[gid] = ming;
            }
        }
        for (const auto& p : group) {
            find(p.first, group);
        }
        
        unordered_set<int> gnum;
        for (const auto& p : group) {
            gnum.insert(p.second);
        }
        return stones.size() - gnum.size();
    }

private:
    int id(int x, int y) {
        return x * 10000 + y;
    }
    int find(int vid, unordered_map<int, int>& group) {
        if (group[vid] != vid) {
            group[vid] = find(group[vid], group);
        }
        return group[vid];
    }
    /*
     A better one!
    public int removeStones(int[][] stones) {
        int[] roots = new int[20000];
        for (int i = 0; i < 20000; ++i) {
            roots[i] = i;
        }
        for (int[] stone : stones) {
            roots[findRoot(roots, stone[0])] = findRoot(roots, stone[1] + 10000);
        }
        Set<Integer> seen = new HashSet<>();
        for (int[] stone : stones) {
            seen.add(findRoot(roots, stone[0]));
        }
        return stones.length - seen.size();
    }
    
    private int findRoot(int[] roots, int x) {
        if (roots[x] != x) {
            roots[x] = findRoot(roots, roots[x]);
        }
        return roots[x];
    }
     */
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> stones;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}}},
        {{{0,0},{0,2},{1,1},{2,0},{2,2}}},
        {{{0,0}}},
        {{{5,9},{9,0},{0,0},{7,0},{4,3},{8,5},{5,8},{1,1},{0,6},{7,5},{1,6},{1,9},{9,4},{2,8},{1,3},{4,2},{2,5},{4,1},{0,2},{6,5}}}
    };

    vector< int > answers {
        5,
        3,
        0,
        19
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = removeStones::Solution().removeStones(dp.stones);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
