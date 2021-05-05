// isBipartite.cpp
// leetcode
//
// Created by  Song Ding on 5/6/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isBipartite {
/*
 785. Is Graph Bipartite?
 Medium
 
 605
 
 74
 
 Favorite
 
 Share
 Given an undirected graph, return true if and only if it is bipartite.
 
 Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.
 
 The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.
 
 Example 1:
 Input: [[1,3], [0,2], [1,3], [0,2]]
 Output: true
 Explanation:
 The graph looks like this:
 0----1
 |    |
 |    |
 3----2
 We can divide the vertices into two groups: {0, 2} and {1, 3}.
 Example 2:
 Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
 Output: false
 Explanation:
 The graph looks like this:
 0----1
 | \  |
 |  \ |
 3----2
 We cannot find a way to divide the set of nodes into two independent subsets.
 
 
 Note:
 
 graph will have length in range [1, 100].
 graph[i] will contain integers in range [0, graph.length - 1].
 graph[i] will not contain i or duplicate values.
 The graph is undirected: if any element j is in graph[i], then i will be in graph[j].
 */

class Solution {
public:
    /**
     * start from the first edge and put the two nodes in two sets.
     * loop through nodes in either set, and the nodes connected will
     * go to the next set. This goes on until:
     * 1, all nodes are grouped into the two sets
     * 2, or there is an edge that are in both sets.
     *
     */
    bool isBipartite(vector<vector<int>>& graph) {
        unordered_set<int> done;
        for (int i = 0; i < graph.size(); ++i) {
            if (done.find(i) != done.end()) {
                continue;
            }
            unordered_set<int> f1{i};
            unordered_set<int> f2;
            bool inf1 = true;
            unordered_set<int> cur{i};
            while (cur.size()) {
                unordered_set<int> next;
                if (inf1) {
                    for (auto j : cur) {
                        for (auto k : graph[j]) {
                            if (f1.find(k) != f1.end()) {
                                return false;
                            } else if (f2.find(k) == f2.end()) {
                                next.insert(k);
                            }
                        }
                        done.insert(j);
                    }
                    f2.insert(next.begin(), next.end());
                    inf1 = false;
                } else {
                    for (auto j : cur) {
                        for (auto k : graph[j]) {
                            if (f2.find(k) != f2.end()) {
                                return false;
                            } else if (f1.find(k) == f1.end()) {
                                next.insert(k);
                            }
                        }
                        done.insert(j);
                    }
                    f1.insert(next.begin(), next.end());
                    inf1 = true;
                }
                cur.swap(next);
            }
        }
        return true;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<vector<int>> > params {
        {{1,3}, {0,2}, {1,3}, {0,2}},
        {{1,2,3}, {0,2}, {0,1,3}, {0,2}}
        
    };

    vector<  bool > answers {
        true,
        false
    };
    int i = 1;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = isBipartite::Solution().isBipartite(params[i]);
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
