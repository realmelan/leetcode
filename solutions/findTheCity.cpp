//
//  findTheCity.cpp
//  leetcode
//
//  Created by Song Ding on 7/15/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace findTheCity {
/*
// TODO: copy problem statement here
 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
 Medium

 269

 22

 Add to List

 Share
 There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.

 Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.

 Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.

  

 Example 1:



 Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
 Output: 3
 Explanation: The figure above describes the graph.
 The neighboring cities at a distanceThreshold = 4 for each city are:
 City 0 -> [City 1, City 2]
 City 1 -> [City 0, City 2, City 3]
 City 2 -> [City 0, City 1, City 3]
 City 3 -> [City 1, City 2]
 Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
 Example 2:



 Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
 Output: 0
 Explanation: The figure above describes the graph.
 The neighboring cities at a distanceThreshold = 2 for each city are:
 City 0 -> [City 1]
 City 1 -> [City 0, City 4]
 City 2 -> [City 3, City 4]
 City 3 -> [City 2, City 4]
 City 4 -> [City 1, City 2, City 3]
 The city 0 has 1 neighboring city at a distanceThreshold = 2.
  

 Constraints:

 2 <= n <= 100
 1 <= edges.length <= n * (n - 1) / 2
 edges[i].length == 3
 0 <= fromi < toi < n
 1 <= weighti, distanceThreshold <= 10^4
 All pairs (fromi, toi) are distinct.
*/
class Solution {
public:
    // TODO: copy function signature here
    int findTheCity2(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<unordered_map<int,int>> conn(n);
        for (auto& e : edges) {
            conn[e[0]][e[1]] = e[2];
            conn[e[1]][e[0]] = e[2];
        }
        int minReach = n+1, res = n;
        for (int k = n-1; k >= 0; --k) {
            vector<int> dist(n, -1);
            priority_queue<pair<int,int>> q;
            q.emplace(distanceThreshold, k);
            while (!q.empty()) {
                auto [d, c] = q.top();
                q.pop();
                if (dist[c] < d) {
                    dist[c] = d;
                    for (auto [nc, w] : conn[c]) {
                        if (w <= d && d-w > dist[nc]) {
                            q.emplace(d-w, nc);
                        }
                    }
                }
            }
            int kreach = 0;
            for (auto d : dist) {
                kreach += (d >= 0 ? 1 : 0);
            }
            if (kreach < minReach) {
                minReach = kreach;
                res = k;
            }
        }
        return res;
    }
    // floyd-warshall algorithm to compute min distance of each pair of nodes.
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, 1000001));
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }
        for (auto& e : edges) {
            dist[e[0]][e[1]] = dist[e[1]][e[0]] = e[2];
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        int minReach = n+1, res = n;
        for (int i = n-1; i >= 0; --i) {
            int reach = 0;
            for (int j = 0; j < n; ++j) {
                if (dist[i][j] <= distanceThreshold) {
                    ++reach;
                }
            }
            if (reach < minReach) {
                minReach = reach;
                res = i;
            }
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
        int distanceThreshold;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {4,{{0,1,3},{1,2,1},{1,3,4},{2,3,1}},4},
        {5,{{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}},2},
        {6,{{0,1,10},{0,2,1},{2,3,1},{1,3,1},{1,4,1},{4,5,10}},20}
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
        0,
        
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findTheCity::Solution().findTheCity(dp.n, dp.edges, dp.distanceThreshold);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
