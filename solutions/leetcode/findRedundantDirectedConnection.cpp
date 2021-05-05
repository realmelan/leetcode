// findRedundantDirectedConnection.cpp
// leetcode
//
// Created by  Song Ding on 3/24/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findRedundantDirectedConnection {
/**
 685. Redundant Connection II
 Hard

 542

 169

 Favorite

 Share
 In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

 The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

 The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

 Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

 Example 1:
 Input: [[1,2], [1,3], [2,3]]
 Output: [2,3]
 Explanation: The given directed graph will be like this:
   1
  / \
 v   v
 2-->3
 Example 2:
 Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
 Output: [4,1]
 Explanation: The given directed graph will be like this:
 5 <- 1 -> 2
      ^    |
      |    v
      4 <- 3
 Note:
 The size of the input 2D-array will be between 3 and 1000.
 Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
 */
class Solution {
public:
    /**
     * https://leetcode.com/problems/redundant-connection-ii/discuss/108058/one-pass-disjoint-set-solution-with-explain
     * As in the post, there are 3 scenarios after inserting a new edge:
     * 1, one node with two parents, then remove the second edge
     * 2, a cycle, and one node with two parents, this happens when adding an edge from a descendant to a ancester and that
     *  ancester has a parent too.
     * 3, a cycle only, this happens when an edge is added from a descendant to tree root.
     *
     * Union-find can be used to find the node that has 2 parents, and detect cycle. A trick is to bypass the second edge if a double parent
     * node appears.
     */
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> p(n+1), another(n+1);
        for (int i = 0; i <= n; ++i) {
            p[i] = i;
        }
        int first = -1, second = -1, last = -1;
        for (int i = 0; i < n; ++i) {
            int s = edges[i][0];
            int c = edges[i][1];
            if (p[c] != c) {
                first = another[c];
                second = i;
                continue;
            }
            another[c] = i; // record edge that points to c.
            
            // detect cycle
            int ps = find(s, p);
            if (ps == c) {
                last = i;
            } else {
                p[c] = ps;
            }
        }
        if (last == -1) {
            return edges[second];
        } else if (first == -1) {
            return edges[last];
        } else {
            return edges[first];
        }
        
    }
    int find(int i, vector<int>& p) {
        if (i != p[i]) {
            p[i] = find(p[i], p);
        }
        return p[i];
    }
    
    vector<int> findRedundantDirectedConnection3(vector<vector<int>>& edges) {
        int n = edges.size();
        if (n == 0) {
            return vector<int>{};
        }
        
        vector<int> in(n + 1);
        for (const auto& e : edges) {
            ++in[e[1]];
        }
        
        
        int snode = -1;
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 2) {
                snode = i;
                break;
            }
        }
        
        // all nodes have 1 in-degree
        //remove all leaf nodes interatively till a cycle is left
        // find the last edge which is on the cycle.
        set<int> cycleNodes;
        for (int i = 1; i <= n; ++i) {
            cycleNodes.insert(i);
        }
        while (true) {
            set<int> ncycleNodes1; // nodes that are source of an edge
            set<int> ncycleNodes2; // nodes that are destination of an edge
            for (int i = 0; i < n; ++i) {
                const auto& e = edges[i];
                if (cycleNodes.count(e[0]) && cycleNodes.count(e[1])) {
                    ncycleNodes1.insert(e[0]);
                    ncycleNodes2.insert(e[1]);
                }
            }
            vector<int> t;
            set_intersection(ncycleNodes1.begin(), ncycleNodes1.end(), ncycleNodes2.begin(), ncycleNodes2.end(), std::back_inserter(t));
            
            if (t.size() == cycleNodes.size()) {
                break;
            }
            cycleNodes.clear();
            cycleNodes.insert(t.begin(), t.end());
        }
        
        if (cycleNodes.size()) {
            for (int i = n - 1; i >= 0; --i) {
                const auto& e = edges[i];
                if (cycleNodes.count(e[0]) && cycleNodes.count(e[1])
                    && (snode == -1 || e[1] == snode)) {
                    return e;
                }
            }
        } else {
            for (int i = n - 1; i >= 0; --i) {
                const auto& e = edges[i];
                if (snode != -1 && e[1] == snode) {
                    return e;
                }
            }
        }
        
        
        return vector<int>{};
        
    }
    /**
     */
    vector<int> findRedundantDirectedConnection1(vector<vector<int>>& edges) {
        vector<int> res;
        int tlen = edges.size();
        if (tlen <= 1) {
            return res;
        }
        
        set<vector<int>> current(edges.begin(), edges.end());
        
        while (true) {
            int len = current.size();
            vector<int> in(tlen + 1, 0);
            vector<int> out(tlen + 1, 0);
            for (const auto& e : current) {
                ++out[e[0]];
                ++in[e[1]];
            }
            
            bool removed = false;
            for (int i = 1; i <= tlen; ++i) {
                if (in[i] == 1 && out[i] == 0) {
                    removed = true;
                    for (auto it = current.begin();
                         it != current.end(); ++it) {
                        if ((*it)[1] == i) {
                            current.erase(it);
                            break;
                        }
                    }
                } else if (in[i] == 0 && out[i] == 1) {
                    removed = true;
                    for (auto it = current.begin();
                         it != current.end(); ++it) {
                        if ((*it)[0] == i) {
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
    /**
     find a root node whose in degree is 0, and walk through root node till
     an edge which results in already visited node.
     
     If a root node can't be found, then it is a cycle, and the last edge can
     be removed.
     */
    vector<int> findRedundantDirectedConnection2(vector<vector<int>>& edges) {
        int n = edges.size();
        if (n == 0) {
            return vector<int>{};
        }
        
        vector<int> degree(n + 1);
        vector<vector<int>> fromTo(n + 1);
        for (const auto& e : edges) {
            ++degree[e[1]];
            fromTo[e[0]].push_back(e[1]);
        }
        
        int root = -1;
        for (int i = 1; i < n; ++i) {
            if (degree[i] == 0) {
                root = i;
                break;
            }
        }
        
        if (root == -1) {
            return edges[n - 1];
        } else {
            // walk through root node
            vector<bool> visited(n, false);
            queue<pair<int,int>> path;
            path.push(make_pair(0, root));
            while (path.size()) {
                pair<int,int> from = path.front();
                if (visited[from.second]) {
                    return vector<int>{from.first, from.second};
                }
                visited[from.second] = true;
                path.pop();
                
                const vector<int>& tos = fromTo[from.second];
                if (tos.empty()) {
                    continue;
                }
                
                for (auto to : tos) {
                    path.push(make_pair(from.second, to));
                }
            }
            return vector<int>();
        }
        
    }
private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector<vector<int>> edges{
        //{2,1},{3,1},{4,2},{1,4}
        //{1,2},{3,1},{1,3},{1,4}
        //{1,2},{1,3},{2,3}
        //{4,2},{1,5},{5,2},{5,3},{2,4}
        {13,11},{16,5},{11,14},{7,10},{12,19},{20,6},{5,9},{3,16},{8,7},{15,2},{1,18},{14,8},{17,3},{6,12},{18,13},{9,15},{4,18},{10,20},{19,17},{2,4}
    };
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = findRedundantDirectedConnection::Solution().findRedundantDirectedConnection(edges);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
