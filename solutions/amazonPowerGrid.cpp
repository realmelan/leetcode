//
//  amazonPowerGrid.cpp
//  leetcode
//
//  Created by Song Ding on 11/12/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace amazonPowerGrid {
/*
// TODO: copy problem statement here
 Position: New Grad
 Platform: SHL
 Location: USA
 Date: Aug 2020

 Your team at amazon is overseeing the design of a new high-efficiency data center at HQ2. A power grid need to be generated for supplying power to N servers. All servers in the grid have to be connected such that they have access to power. The cost of connections between different servers varies.

 Assume that there are no ties, names of servers are unique, connections are directionless, there is at most one connection between a pair of servers, all costs are greater than zero, and a server does not connect to itself.

 Write an algorithm to minimize the cost of connecting all servers in the power grid.

 Input
 num, an Integer representing number of connections.
 connectons, representing a list of connections where each element of the list consists of two servers and the cost of connection between the servers.

 Note
 The cost of connection between the servers is always greater than 0.

 Example
 Input

 num = 5
 connection =
      [[A,B,1],
      [B,C,4],
      [B,D,6],
      [D,E,5],
      [C,E,1]]
 Output

 [[A,B,1],
 [B,C,4],
 [C,E,1],
 [D,E,5]]
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<vector<int>> amazonPowerGrid(vector<vector<int>>& connections) {
        // use priority queue to perform prim's minimum spanning tree
        int n = connections.size();
        int maxi = 0;
        unordered_map<int, unordered_map<int,int>> conns;
        vector<int> minCost(3, INT_MAX);
        for (auto& edge : connections) {
            conns[edge[0]][edge[1]] = edge[2];
            conns[edge[1]][edge[0]] = edge[2];
            maxi = max(maxi, max(edge[1], edge[0]));
            if (minCost[2] > edge[2]) {
                minCost = edge;
            }
        }
        auto cmp = [](const auto& a, const auto& b){
            return a[2] > b[2];
        };
        vector<vector<int>> res;
        unordered_set<int> added;
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        q.push(minCost);
        while (res.size() < maxi) {
            auto edge = q.top();q.pop();
            if (added.count(edge[0]) && added.count(edge[1])) {
                continue;
            }
            res.push_back(edge);
            added.insert(edge[0]);
            added.insert(edge[1]);
            
            for (auto p : conns[edge[0]]) {
                if (!added.count(p.first)) {
                    q.push({edge[0], p.first, p.second});
                }
            }
            for (auto p : conns[edge[1]]) {
                if (!added.count(p.first)) {
                    q.push({edge[1], p.first, p.second});
                }
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
        vector<vector<int>> connections;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{0,1,1},{1,2,4},{1,3,6},{3,4,5},{2,4,1}}},
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
        {{0,1,1},{1,2,4},{2,4,1},{3,4,5}},
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = amazonPowerGrid::Solution().amazonPowerGrid(dp.connections);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
