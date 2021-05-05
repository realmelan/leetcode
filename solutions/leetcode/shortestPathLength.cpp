// shortestPathLength.cpp
// leetcode
//
// Created by  Song Ding on 10/9/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;
/**
 847. Shortest Path Visiting All Nodes
 Hard

 362

 41

 Favorite

 Share
 An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.

 graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.

 Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

  

 Example 1:

 Input: [[1,2,3],[0],[0],[0]]
 Output: 4
 Explanation: One possible path is [1,0,2,0,3]
 Example 2:

 Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
 Output: 4
 Explanation: One possible path is [0,1,4,2,3]
  

 Note:

 1 <= graph.length <= 12
 0 <= graph[i].length < graph.length
 */
namespace shortestPathLength {

class Solution {
public:
    /**
     * Use brutal force. Check the description that the length <= 12.
     * A state = nodes visited in lower 12 bits + current node in next 12 bits, cost.
     * Here, cost can be removed as it is BFS, using a counter would do.
     */
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        queue<pair<int,int>> states;
        unordered_set<int> visited;
        int end = 0;
        for (int i = 0; i < n; ++i) {
            int st = (i << 12) | (1 << i);
            states.push(make_pair(st, 0));
            visited.insert(st);
            end |= 1 << i;
        }
        
        while (states.size()) {
            int st = states.front().first;
            int cost = states.front().second;
            states.pop();
            
            if ((st & end) == end) {
                return cost;
            }
            
            int node = st >> 12;
            int nodeVisited = st & end;
            for (int i : graph[node]) {
                int nst = (i << 12) | nodeVisited | (1 << i);
                if (visited.find(nst) == visited.end()) {
                    states.push(make_pair(nst, cost + 1));
                    visited.insert(nst);
                }
            }
        }
        return -1;
        
    }
    int shortestPathLength2(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> states;
        states.reserve(n);
        unordered_set<int> visited;
        int end = 0;
        for (int i = 0; i < n; ++i) {
            int st = (i << 12) | (1 << i);
            states.push_back(st);
            visited.insert(st);
            end |= 1 << i;
        }
        
        int res = 0;
        while (states.size()) {
            vector<int> next;
            next.reserve(n);
            ++res;
            for (auto st : states) {
                int node = st >> 12;
                int nodeVisited = st & end;
                for (int i : graph[node]) {
                    int nst = (i << 12) | nodeVisited | (1 << i);
                    if ((nst & end) == end) {
                        return res;
                    } else if (visited.find(nst) == visited.end()) {
                        next.push_back(nst);
                        visited.insert(nst);
                    }
                }
            }
            states.swap(next);
        }
        return -1;
        
    }
    int shortestPathLength3(vector<vector<int>>& graph) {
        int n = graph.size(), ts = (1<<n)-1;
        vector<vector<int>> fl(1<<n, vector<int>(n, 10000));
        for (int i = 0; i < n; ++i) {
            fl[1<<i][i] = 0;
        }
        for (int r = 0; r < n; ++r) {
            for (int i = 1; i < (1<<n); ++i) {
                for (int j = 0; j < n; ++j) {
                    for (auto k : graph[j]) {
                        fl[i|(1<<k)][k] = min(fl[i|(1<<k)][k], fl[i][j]+1);
                    }
                }
            }
        }
        return *min_element(begin(fl[ts]), end(fl[ts]));
    }
    int shortestPathLength4(vector<vector<int>>& graph) {
        int n = graph.size(), ts = (1<<n)-1;
        vector<vector<int>> fl(1<<n, vector<int>(n, 10000));
        vector<vector<int>> dist(n, vector<int>(n, 10000));
        for (int i = 0; i < n; ++i) {
            fl[1<<i][i] = 0;
            dist[i][i] = 0;
            for (auto j : graph[i]) {
                dist[i][j] = dist[j][i] = 1;
            }
        }
        
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        for (int i = 1; i < (1<<n); ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    fl[i|(1<<k)][k] = min(fl[i|(1<<k)][k], fl[i][j]+dist[j][k]);
                }
            }
        }
        return *min_element(begin(fl[ts]), end(fl[ts]));
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> graph {
        //{1},{0,2,4},{1,3,4},{2},{1,2} // => 4
        {1,2,3},{0},{0},{0} // => 4
        //{1,4,6,8,9},{0,6},{9},{5},{0},{7,3},{0,1},{9,5},{0},{0,2,7} // => 12
        //{2,3},{7},{0,6},{0,4,7},{3,8},{7},{2},{5,3,1},{4} // => 11
    };

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = shortestPathLength::Solution().shortestPathLength4(graph);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
