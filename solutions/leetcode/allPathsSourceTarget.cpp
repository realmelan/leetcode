// allPathsSourceTarget.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace allPathsSourceTarget {
/*
// TODO: copy problem statement here
 797. All Paths From Source to Target
 Medium
 
 396
 
 35
 
 Favorite
 
 Share
 Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.
 
 The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.
 
 Example:
 Input: [[1,2], [3], [3], []]
 Output: [[0,1,3],[0,2,3]]
 Explanation: The graph looks like this:
 0--->1
 |    |
 v    v
 2--->3
 There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
 Note:
 
 The number of nodes in the graph will be in the range [2, 15].
 You can print different paths in any order, but you should keep the order of nodes inside one path.
 */

class Solution {
public:
    /**
     * DFS:
     */
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> res;
        vector<int> path;
        
        int n = graph.size();
        dfs(0, n-1, graph, path, res);
        return res;
    }

private:
    void dfs(int c, int t, const vector<vector<int>>& graph, vector<int>& path, vector<vector<int>>& res) {
        if (c == t) {
            path.push_back(c);
            res.push_back(path);
            path.pop_back();
        } else {
            path.push_back(c);
            
            for (auto i : graph[c]) {
                dfs(i, t, graph, path, res);
            }
            
            path.pop_back();
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<vector<int>> graph;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{{1,2}, {3}, {3}, {}}}
    };

    vector< vector<vector<int>> > answers {
        {{0,1,3},{0,2,3}}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = allPathsSourceTarget::Solution().allPathsSourceTarget(dp.graph);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
