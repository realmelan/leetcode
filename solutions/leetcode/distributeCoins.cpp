// distributeCoins.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace distributeCoins {
/*
// TODO: copy problem statement here
 979. Distribute Coins in Binary Tree
 Medium
 
 468
 
 14
 
 Favorite
 
 Share
 Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.
 
 In one move, we may choose two adjacent nodes and move one coin from one node to another.  (The move may be from parent to child, or from child to parent.)
 
 Return the number of moves required to make every node have exactly one coin.
 
 
 
 Example 1:
 
 
 
 Input: [3,0,0]
 Output: 2
 Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.
 Example 2:
 
 
 
 Input: [0,3,0]
 Output: 3
 Explanation: From the left child of the root, we move two coins to the root [taking two moves].  Then, we move one coin from the root of the tree to the right child.
 Example 3:
 
 
 
 Input: [1,0,2]
 Output: 2
 Example 4:
 
 
 
 Input: [1,0,0,null,3]
 Output: 4
 
 
 Note:
 
 1<= N <= 100
 0 <= node.val <= N
 */

class Solution {
public:
    /**
     * recursive:
     * for each node, count the coin in the subtree, if it has less than its share
     * then it has to get it from its parent, and the parent may have to get them
     * from its other child.
     */
    int distributeCoins(TreeNode* root) {
        int res = 0;
        if (root != NULL) {
            recur(root, res);
        }
        return res;
    }

private:
    /**
     * returns how many coins need to be moved up or moved down from parent.
     * total records total number of moves as of now.
     */
    int recur(TreeNode* root, int& total) {
        int res = root->val - 1;
        if (root->left) {
            int t = recur(root->left, total);
            total += abs(t);
            res += t;
        }
        if (root->right) {
            int t = recur(root->right, total);
            total += abs(t);
            res += t;
        }
        return res;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{3,0,0}},
        {{0,3,0}},
        {{1,0,2}},
        {{1,0,0,INT_MAX,3}}
    };

    vector< int > answers {
        2,
        3,
        2,
        4
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = distributeCoins::Solution().distributeCoins(toTree(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
