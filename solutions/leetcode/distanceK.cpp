// distanceK.cpp
// leetcode
//
// Created by  Song Ding on 5/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace distanceK {
/*
 863. All Nodes Distance K in Binary Tree
 Medium
 
 692
 
 13
 
 Favorite
 
 Share
 We are given a binary tree (with root node root), a target node, and an integer value K.
 
 Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.
 
 
 
 Example 1:
 
 Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2
 
 Output: [7,4,1]
 
 Explanation:
 The nodes that are a distance 2 from the target node (with value 5)
 have values 7, 4, and 1.
 
 
 
 Note that the inputs "root" and "target" are actually TreeNodes.
 The descriptions of the inputs above are just serializations of these objects.
 
 
 Note:
 
 The given tree is non-empty.
 Each node in the tree has unique values 0 <= node.val <= 500.
 The target node is a node in the tree.
 0 <= K <= 1000.
 */

class Solution {
public:
    /**
     * The Binary tree can be divided into two parts, subtree of target node
     * and the other tree excluding the subtree rooted at target.
     *
     * For the subtree rooted at target, it is easy to do a breadth traversal to
     * get all nodes at distance K if any.
     *
     * For nodes not in the subtree, then it must be in a subtree of one of ancestor
     * nodes of the target node; so
     * 1, find the ancestor nodes and their distance to target node
     * 2, for each ancestor node with a distance of D to target node, locate all nodes
     * that have a distance of (K - D) to the ancestor node.
     *
     */
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> res;
        
        vector<TreeNode*> ancestors;
        vector<TreeNode*> path{root};
        findAncestors(target, path, ancestors);
        
        int dist = 0;
        for (int i = ancestors.size() - 1; i >= 0 && K - dist >= 0; --i, ++dist) {
            TreeNode* an = ancestors[i];
            if (i == ancestors.size() - 1) {
                findNodesAtK(an, K - dist, res);
            } else {
                if (K - dist == 0) {
                    res.push_back(an->val);
                } else if (an->left == ancestors[i + 1]) {
                    findNodesAtK(an->right, K - dist - 1, res);
                } else {
                    findNodesAtK(an->left, K - dist - 1, res);
                }
            }
        }
        return res;
    }

private:
    void findAncestors(TreeNode* target, vector<TreeNode*> path, vector<TreeNode*>& res) {
        if (res.size()) {
            return;
        }
        
        TreeNode* cur = path.back();
        if (cur == target) {
            res.insert(res.end(), path.begin(), path.end());
        } else {
            if (cur->left) {
                path.push_back(cur->left);
                findAncestors(target, path, res);
                path.pop_back();
            }
            if (res.empty() && cur->right) {
                path.push_back(cur->right);
                findAncestors(target, path, res);
                path.pop_back();
            }
        }
    }
    void findNodesAtK(TreeNode* root, int K, vector<int>& res) {
        if (root != NULL) {
            if (K == 0) {
                res.push_back(root->val);
            } else {
                if (root->left) {
                    findNodesAtK(root->left, K - 1, res);
                }
                if (root->right) {
                    findNodesAtK(root->right, K - 1, res);
                }
            }
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{3,5,1,6,2,0,8,INT_MAX,INT_MAX,7,4}, 2},
        {{0,1,INT_MAX,3,2}, 1}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (const auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        TreeNode* root = toTree(dp.nodeVals);
        auto res = distanceK::Solution().distanceK(root, root->left->right, dp.K);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
