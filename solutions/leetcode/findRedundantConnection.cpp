//
//  findRedundantConnection.cpp
//  leetcode
//
//  Created by  Song Ding on 11/16/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace findRedundantConnection {
/**
 684. Redundant Connection
 Medium

 834

 204

 Favorite

 Share
 In this problem, a tree is an undirected graph that is connected and has no cycles.

 The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

 The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.

 Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

 Example 1:
 Input: [[1,2], [1,3], [2,3]]
 Output: [2,3]
 Explanation: The given undirected graph will be like this:
   1
  / \
 2 - 3
 Example 2:
 Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
 Output: [1,4]
 Explanation: The given undirected graph will be like this:
 5 - 1 - 2
     |   |
     4 - 3
 Note:
 The size of the input 2D-array will be between 3 and 1000.
 Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

 Update (2017-09-26):
 We have overhauled the problem description + test cases and specified clearly the graph is an undirected graph. For the directed graph follow up please see Redundant Connection II). We apologize for any inconvenience caused.
 */
    class Solution {
    public:
        /**
         use union-find to join nodes when they are connected by an edge.
         upon joining two nodes on an edge, the root is the same for both nodes, then this
         edge is redundant.
         */
        vector<int> findRedundantConnection(vector<vector<int>>& edges) {
            int n = edges.size();
            vector<int> p(n+1);
            for (int i = 0; i < n; ++i) {
                p[i] = i;
            }
            for (auto& e : edges) {
                int pu = find(e[0], p);
                int pv = find(e[1], p);
                if (pu == pv) {
                    return e;
                } else {
                    if (pu < pv) {
                        p[pv] = pu;
                    } else {
                        p[pu] = pv;
                    }
                }
            }
            return {};
        }
        int find(int i, vector<int>& p) {
            if (p[i] != i) {
                p[i] = find(p[i], p);
            }
            return p[i];
        }
        /**
         Looks like to find the last edge which is in a cycle.
         
         Remove all nodes that stick out as leaf, which is not in a cycle.
         These nodes has single degree. Check the left graph. If only a cycle
         is left, then find out the last edge from input edges that is in the
         cycle.
         */
        vector<int> findRedundantConnection_toplogicalsort(vector<vector<int>>& edges) {
            vector<int> res;
            int tlen = edges.size();
            if (tlen <= 1) {
                return res;
            }
            
            set<vector<int>> current(edges.begin(), edges.end());
            
            while (true) {
                int len = current.size();
                vector<int> count(tlen + 1, 0);
                for (const auto& e : current) {
                    ++count[e[0]];
                    ++count[e[1]];
                }
                
                bool removed = false;
                for (int i = 1; i <= tlen; ++i) {
                    if (count[i] == 1) {
                        removed = true;
                        for (auto it = current.begin();
                             it != current.end(); ++it) {
                            if ((*it)[0] == i || (*it)[1] == i) {
                                current.erase(it);
                                break;
                            }
                        }
                    }
                }
                if (!removed) {
                    break;
                }
            }
            set<int> cycleNodes;
            for (const auto& e : current) {
                cycleNodes.insert(e.begin(), e.end());
            }
            
            for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
                if (cycleNodes.count((*it)[0]) && cycleNodes.count((*it)[1])) {
                    return *it;
                }
            }
            return res;
        }
    };
}
/*
int main() {
    vector<vector<int>> edges{{1,2},{2,3},{3,4},{1,4},{1,5}};
    vector<int> res = findRedundantConnection::Solution().findRedundantConnection(edges);
    cout << res[0] << "," << res[1] << endl;
    return 0;
 }
 //*/
