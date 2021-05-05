// bstToGst.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace bstToGst {
/*
// TODO: copy problem statement here
 1038. Binary Search Tree to Greater Sum Tree
 Medium
 
 130
 
 14
 
 Favorite
 
 Share
 Given the root of a binary search tree with distinct values, modify it so that every node has a new value equal to the sum of the values of the original tree that are greater than or equal to node.val.
 
 As a reminder, a binary search tree is a tree that satisfies these constraints:
 
 The left subtree of a node contains only nodes with keys less than the node's key.
 The right subtree of a node contains only nodes with keys greater than the node's key.
 Both the left and right subtrees must also be binary search trees.
 
 
 Example 1:
 
 
 
 Input: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
 
 
 Note:
 
 The number of nodes in the tree is between 1 and 100.
 Each node will have value between 0 and 100.
 The given tree is a binary search tree.
 */

class Solution {
public:
    /**
     * method 1:
     *   1, calculate sum of each subtree.
     *   2, gst(node at left) = gst(parent) + sum(node) - sum(left child)
            gst(node at right) = sum(node) - sum(left child)
     *
     * method 2:
     *  get all node values in sorted order by inorder traversal.
     *  starting from the right end, get accumulative sum for each element.
     *  traversal down BST to assign values to node.
     *
     */
    TreeNode* bstToGst(TreeNode* root) {
        vector<int> sum(101, 0);
        subSum(root, sum);
        
        transform(root, 0, sum);
        
        return root;
        
    }

private:
    int subSum(TreeNode* root, vector<int>& sum) {
        if (root == NULL) {
            return 0;
        }
        int res = root->val;
        if (root->left) {
            res += subSum(root->left, sum);
        }
        if (root->right) {
            res += subSum(root->right, sum);
        }
        sum[root->val] = res;
        return res;
    }
    
    void transform(TreeNode* root, int pgst, vector<int>& sum) {
        int res = pgst + sum[root->val];
        if (root->left) {
            res -= sum[root->left->val];
        }
        
        if (root->left) {
            transform(root->left, res, sum);
        }
        if (root->right) {
            transform(root->right, res - root->val - sum[root->right->val], sum);
        }
        root->val = res;
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
        {{4,1,6,0,2,5,7,INT_MAX,INT_MAX,INT_MAX,3,INT_MAX,INT_MAX,INT_MAX,8}}
    };

    vector< vector<int> > answers {
        {30,36,21,36,35,26,15,INT_MAX,INT_MAX,INT_MAX,33,INT_MAX,INT_MAX,INT_MAX,8}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = bstToGst::Solution().bstToGst(toTree(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
