// cloneGraph.cpp
// leetcode
//
// Created by  Song Ding on 6/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace cloneGraph {
/*
// TODO: copy problem statement here
 133. Clone Graph
 Medium
 
 789
 
 847
 
 Favorite
 
 Share
 Given a reference of a node in a connected undirected graph, return a deep copy (clone) of the graph. Each node in the graph contains a val (int) and a list (List[Node]) of its neighbors.
 
 
 
 Example:
 
 
 
 Input:
 {"$id":"1","neighbors":[{"$id":"2","neighbors":[{"$ref":"1"},{"$id":"3","neighbors":[{"$ref":"2"},{"$id":"4","neighbors":[{"$ref":"3"},{"$ref":"1"}],"val":4}],"val":3}],"val":2},{"$ref":"4"}],"val":1}
 
 Explanation:
 Node 1's value is 1, and it has two neighbors: Node 2 and 4.
 Node 2's value is 2, and it has two neighbors: Node 1 and 3.
 Node 3's value is 3, and it has two neighbors: Node 2 and 4.
 Node 4's value is 4, and it has two neighbors: Node 1 and 3.
 */

class Solution {
public:
    /**
     * BFS + visited
     */
    GraphNode* cloneGraph(GraphNode* node) {
        unordered_map<GraphNode*, GraphNode*> visited;
        GraphNode* ns = NULL;
        if (node) {
            queue<pair<GraphNode*, GraphNode*>> s;
            ns = new GraphNode(node->val, {});
            s.push(make_pair(node, ns));
            visited.insert(make_pair(node, ns));
            while (s.size()) {
                auto cp = s.front();
                s.pop();
                GraphNode* c = cp.first;
                GraphNode* nc = cp.second;
                for (auto b : c->neighbors) {
                    if (b) {
                        GraphNode* nb = NULL;
                        auto it = visited.find(b);
                        if (it != visited.end()) {
                            nb = it->second;
                        } else {
                            nb = new GraphNode(b->val, {});
                            visited.insert(make_pair(b, nb));
                            s.push(make_pair(b, nb));
                        }
                        nc->neighbors.push_back(nb);
                    }
                }
            }
        }
        return ns;
    }

private:
};

}
/*/
int main() {
    GraphNode* n1 = new GraphNode(1, {});
    GraphNode* n2 = new GraphNode(2, {});
    GraphNode* n3 = new GraphNode(3, {});
    GraphNode* n4 = new GraphNode(4, {});
    n1->neighbors.push_back(n2);
    n1->neighbors.push_back(n4);
    n2->neighbors.push_back(n1);
    n2->neighbors.push_back(n3);
    n3->neighbors.push_back(n2);
    n3->neighbors.push_back(n4);
    n4->neighbors.push_back(n1);
    n4->neighbors.push_back(n3);
    
    GraphNode* ns = cloneGraph::Solution().cloneGraph(n1);
    cout << ns << endl;
    return 0;
}
*/

/*/
int main() {
    // TODO: define parameter type here
    struct d {
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {}
    };

    vector<  > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = cloneGraph::Solution().cloneGraph(dp.);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
