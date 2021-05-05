//
//  findMinHeightTrees.cpp
//  leetcode
//
//  Created by  Song Ding on 1/7/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace findMinHeightTrees {
    class Solution {
    public:
        /**
         * if we start walking from leaves towards internal nodes, and the last one or two nodes are the roots
         * that have minimum height.
         * https://leetcode.com/problems/minimum-height-trees/discuss/76055/Share-some-thoughts
         */
        vector<int> findMinHeightTrees_topological(int n, vector<pair<int, int>>& edges) {
            vector<unordered_set<int>> conns(n);
            for (auto& p : edges) {
                conns[p.first].insert(p.second);
                conns[p.second].insert(p.first);
            }
            
            unordered_set<int> cur;
            for (int i = 0; i < n; ++i) {
                if (conns[i].size() <= 1) {
                    cur.insert(i);
                }
            }
            
            int nl = n;
            while (nl > 2) {
                unordered_set<int> next;
                for (auto c : cur) {
                    for (auto nc : conns[c]) {
                        conns[nc].erase(c);
                        if (conns[nc].size() == 1) {
                            next.insert(nc);
                        }
                    }
                    conns[c].clear();
                    --nl;
                }
                cur.swap(next);
            }
            return vector<int>(cur.begin(), cur.end());
        }
        /**
         Choose each one as root, and find the height, recursively.
         Note, partial results may be cached for reuse. For example, when
         finding height for root 0, heights for all trees rooted at 3 will
         already be computed.
         */
        vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
            set<pair<int, int>> wedges(edges.begin(), edges.end());
            vector<map<int, int>> results(n);
            
            int minHeight = n;
            vector<int> res;
            for (int i = 0; i < n; ++i) {
                int h = getHeight(i, wedges, results);
                if (h < minHeight) {
                    minHeight = h;
                    res.clear();
                    res.push_back(i);
                } else if (h == minHeight) {
                    res.push_back(i);
                }
            }
            return res;
        }
    private:
        int getHeight(int start, set<pair<int, int>>& wedges, vector<map<int, int>>& results) {
            vector<int> nodes;
            vector<pair<int, int>> saveEdges;
            for (auto it = wedges.begin(); it != wedges.end();) {
                if (it->first == start) {
                    nodes.push_back(it->second);
                    saveEdges.push_back(*it);
                    it = wedges.erase(it);
                } else if (it->second == start) {
                    nodes.push_back(it->first);
                    saveEdges.push_back(*it);
                    it = wedges.erase(it);
                } else {
                    ++it;
                }
            }
            
            if (nodes.empty()) {
                return 0;
            }
            
            int maxHeight = 0;
            for (int i = 0; i < nodes.size(); ++i) {
                auto it = results[start].find(nodes[i]);
                int h = 0;
                if (it != results[start].end()) {
                    h = it->second;
                } else {
                    h = getHeight(nodes[i], wedges, results) + 1;
                    results[start].insert(make_pair(nodes[i], h));
                }
                
                if (h > maxHeight) {
                    maxHeight = h;
                }
            }
            
            wedges.insert(saveEdges.begin(), saveEdges.end());
            return maxHeight;
        }
    };
}
/*
int main() {
    int n = 1;
    vector<pair<int, int>> edges{
        //{1,0},{1,2},{1,3}
    };
    vector<int> nodes = findMinHeightTrees::Solution().findMinHeightTrees_topological(n, edges);
    for (auto i : nodes) {
        cout << i << endl;
    }
    return 0;
}
// */
