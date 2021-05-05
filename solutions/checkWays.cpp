//
//  checkWays.cpp
//  leetcode
//
//  Created by Song Ding on 1/24/21.
//  Copyright © 2021 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace checkWays {
/*
// TODO: copy problem statement here
 1719. Number Of Ways To Reconstruct A Tree My SubmissionsBack to Contest
 User Accepted: 8
 User Tried: 133
 Total Accepted: 8
 Total Submissions: 320
 Difficulty: Hard
 You are given an array pairs, where pairs[i] = [xi, yi], and:

 There are no duplicates.
 xi < yi
 Let ways be the number of rooted trees that satisfy the following conditions:

 The tree consists of nodes whose values appeared in pairs.
 A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
 Note: the tree does not have to be a binary tree.
 Two ways are considered to be different if there is at least one node that has different parents in both ways.

 Return:

 0 if ways == 0
 1 if ways == 1
 2 if ways > 1
 A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.

 An ancestor of a node is any node on the path from the root to that node (excluding the node itself). The root has no ancestors.

  

 Example 1:


 Input: pairs = [[1,2],[2,3]]
 Output: 1
 Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
 Example 2:


 Input: pairs = [[1,2],[2,3],[1,3]]
 Output: 2
 Explanation: There are multiple valid rooted trees. Three of them are shown in the above figures.
 Example 3:

 Input: pairs = [[1,2],[2,3],[2,4],[1,5]]
 Output: 0
 Explanation: There are no valid rooted trees.
  

 Constraints:

 1 <= pairs.length <= 105
 1 <= xi < yi <= 500
 The elements in pairs are unique.
*/
class Solution {
public:
    // TODO: copy function signature here
    // https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/discuss/1011335/c%2B%2B-bitset-20-lines
    int checkWays(vector<vector<int>>& pairs) {
        unordered_map<int, bitset<501>> conns;
        unordered_set<int> nodes;
        for (auto& p : pairs) {
            nodes.insert(p[0]);
            nodes.insert(p[1]);
            conns[p[0]].set(p[1]);
            conns[p[0]].set(p[0]);
            conns[p[1]].set(p[0]);
            conns[p[1]].set(p[1]);
        }
        // first check whether there is root nodes
        int cnt = 0;
        for (auto i : nodes) {
            if (conns[i].count() == nodes.size()) {
                ++cnt;
            }
        }
        if (!cnt) {
            return 0;
        }
        // for each pair of edge, check whether the two have same connected nodes.
        // one must have a super set then the other as one is parent of the other
        int res = 1;
        for (auto& e : pairs) {
            bool p0 = (conns[e[0]] | conns[e[1]]) == conns[e[0]];
            bool p1 = (conns[e[0]] | conns[e[1]]) == conns[e[1]];
            if (!p0 && !p1) {
                return 0;
            } else if (p0 && p1) {
                res = 2;
            }
        }
        return res;
    }
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> pairs;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{1,2},{2,3}}},
        {{{3,5},{4,5},{2,5},{1,5},{1,4},{2,4}}},
        {{{3,4},{2,3},{4,5},{2,4},{2,5},{1,5},{1,4}}},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = checkWays::Solution().checkWays(dp.pairs);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
