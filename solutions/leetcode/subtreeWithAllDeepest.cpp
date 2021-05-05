// subtreeWithAllDeepest.cpp
// leetcode
//
// Created by  Song Ding on 5/27/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace subtreeWithAllDeepest {
/*
// TODO: copy problem statement here
 865. Smallest Subtree with all the Deepest Nodes
 Medium
 
 348
 
 92
 
 Favorite
 
 Share
 Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.
 
 A node is deepest if it has the largest depth possible among any node in the entire tree.
 
 The subtree of a node is that node, plus the set of all descendants of that node.
 
 Return the node with the largest depth such that it contains all the deepest nodes in its subtree.
 
 
 
 Example 1:
 
 Input: [3,5,1,6,2,0,8,null,null,7,4]
 Output: [2,7,4]
 Explanation:
 
 
 
 We return the node with value 2, colored in yellow in the diagram.
 The nodes colored in blue are the deepest nodes of the tree.
 The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
 The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
 Both the input and output have TreeNode type.
 
 
 Note:
 
 The number of nodes in the tree will be between 1 and 500.
 The values of each node are unique.
 */

class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        TreeNode* res = root;
        int maxd = 0;
        getMaxDepthNode(root, 0, maxd, res);
        return res;
    }
    
    int getMaxDepthNode(TreeNode* cur, int l, int& maxd, TreeNode*& res) {
        if (cur->left == NULL && cur->right == NULL) {
            if (l > maxd) {
                maxd = l;
                res = cur;
            }
            return l;
        } else if (cur->left == NULL) {
            return getMaxDepthNode(cur->right, l+1, maxd, res);
        } else if (cur->right == NULL) {
            return getMaxDepthNode(cur->left, l+1, maxd, res);
        } else {
            int ld = getMaxDepthNode(cur->left, l+1, maxd, res);
            int rd = getMaxDepthNode(cur->right, l+1, maxd, res);
            if (ld == maxd && rd == maxd) {
                res = cur;
            }
            return max(ld, rd);
        }
    }
    /**
     * First of all, get the depth of each node using recusive traversal.
     * Then starting from root, and check whether current node's left and right child both have the
     * largest depth, if yes, then current node is the answer; otherwise,
     * pick the child node that has the largest depth.
     */
    TreeNode* subtreeWithAllDeepest2(TreeNode* root) {
        unordered_map<TreeNode*, int> depth;
        int maxd = getMaxDepth(root, 0, depth);
        TreeNode* cur = root;
        while (cur) {
            if (cur->left == NULL && cur->right == NULL) {
                break;
            } else if (cur->left == NULL) {
                cur = cur->right;
            } else if (cur->right == NULL) {
                cur = cur->left;
            } else {
                int leftd = depth[cur->left];
                int rightd = depth[cur->right];
                if (leftd == maxd && rightd == maxd) {
                    break;
                } else if (leftd == maxd) {
                    cur = cur->left;
                } else {
                    cur = cur->right;
                }
            }
        }
        return cur;
        
    }

private:
    int getMaxDepth(TreeNode* cur, int l, unordered_map<TreeNode*, int>& depth) {
        int maxd = l;
        if (cur->left == NULL && cur->right == NULL) {
            maxd = l;
        } else if (cur->left == NULL) {
            maxd = getMaxDepth(cur->right, l+1, depth);
        } else if (cur->right == NULL) {
            maxd = getMaxDepth(cur->left, l+1, depth);
        } else {
            maxd = max(getMaxDepth(cur->left, l+1, depth),
                       getMaxDepth(cur->right, l+1, depth));
        }
        depth[cur] = maxd;
        return maxd;
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> vals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{3,5,1,6,2,0,8,INT_MAX,INT_MAX,7,4}},
        {{0,1,3,INT_MAX,2}}
    };

    vector< int > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = subtreeWithAllDeepest::Solution().subtreeWithAllDeepest(toTree(dp.vals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
