//
//  countSubgraphsForEachDiameter.cpp
//  leetcode
//
//  Created by Song Ding on 3/3/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace countSubgraphsForEachDiameter {
/*
// TODO: copy problem statement here
 1617. Count Subtrees With Max Distance Between Cities My SubmissionsBack to Contest
 User Accepted: 364
 User Tried: 565
 Total Accepted: 383
 Total Submissions: 1034
 Difficulty: Hard
 There are n cities numbered from 1 to n. You are given an array edges of size n-1, where edges[i] = [ui, vi] represents a bidirectional edge between cities ui and vi. There exists a unique path between each pair of cities. In other words, the cities form a tree.

 A subtree is a subset of cities where every city is reachable from every other city in the subset, where the path between each pair passes through only the cities from the subset. Two subtrees are different if there is a city in one subtree that is not present in the other.

 For each d from 1 to n-1, find the number of subtrees in which the maximum distance between any two cities in the subtree is equal to d.

 Return an array of size n-1 where the dth element (1-indexed) is the number of subtrees in which the maximum distance between any two cities is equal to d.

 Notice that the distance between the two cities is the number of edges in the path between them.

  

 Example 1:



 Input: n = 4, edges = [[1,2],[2,3],[2,4]]
 Output: [3,4,0]
 Explanation:
 The subtrees with subsets {1,2}, {2,3} and {2,4} have a max distance of 1.
 The subtrees with subsets {1,2,3}, {1,2,4}, {2,3,4} and {1,2,3,4} have a max distance of 2.
 No subtree has two nodes where the max distance between them is 3.
 Example 2:

 Input: n = 2, edges = [[1,2]]
 Output: [1]
 Example 3:

 Input: n = 3, edges = [[1,2],[2,3]]
 Output: [2,1]
  

 Constraints:

 2 <= n <= 15
 edges.length == n-1
 edges[i].length == 2
 1 <= ui, vi <= n
 All pairs (ui, vi) are distinct.
*/
class Solution {
public:
    // TODO: copy function signature here
    // floyd-warshall to compute distance b/w any two nodes
    // use state compression to enumerate all subsets and put it to each diameter
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        constexpr int INF = 1000;
        vector<vector<int>> dist(n+1,vector<int>(n+1,INF));
        for (int i = 1; i <= n; ++i) {
            dist[i][i] = 0;
        }
        for (auto& e : edges) {
            dist[e[0]][e[1]] = dist[e[1]][e[0]] = 1;
        }
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
        vector<unordered_set<int>> t(n-1);
        vector<int> md(1<<n, INF);
        for (int i = 0; i < n; ++i) {
            md[1<<i] = 0;
        }
        for (int st = 1; st < 1<<n; ++st) {
            if (md[st] == INF) {
                continue;
            }
            vector<int> nodes;
            int j = 0;
            while (st >= 1<<j) {
                if (st & (1<<j)) {
                    nodes.push_back(j+1);
                }
                ++j;
            }
            for (int i = 1; i <= n; ++i) {
                if ( !(st & (1<<(i-1))) ) {
                    int dirc = 0;
                    for (auto j : nodes) {
                        if (dist[i][j] == 1) {
                            // i is connected to tree st via j
                            dirc = j;
                            break;
                        }
                    }
                    if (dirc) {
                        int maxd = md[st];
                        for (auto j : nodes) {
                            maxd = max(maxd, dist[i][j]);
                        }
                        md[st|1<<(i-1)] = maxd;
                        t[maxd-1].insert(st|(1<<(i-1)));
                    }
                }
            }
        }
        vector<int> res;
        for (auto& p : t) {
            res.push_back(p.size());
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        int n;
        vector<vector<int>> edges;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {4,{{1,2},{2,3},{2,4}}},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = countSubgraphsForEachDiameter::Solution().countSubgraphsForEachDiameter(dp.n, dp.edges);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
