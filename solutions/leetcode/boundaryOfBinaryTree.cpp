// boundaryOfBinaryTree.cpp
// leetcode
//
// Created by  Song Ding on 4/5/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace boundaryOfBinaryTree {

class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> res;
        if (root) {
            res.push_back(root->val);
            // get left most path
            TreeNode* c = root->left;
            while (c) {
                if (c->left == NULL && c->right == NULL) {
                    break;
                }
                res.push_back(c->val);
                if (c->left) {
                    c = c->left;
                } else {
                    c = c->right;
                }
            }
        
            // get all leaf nodes
            dfs(root, res);
            
            // get right most path
            c = root->right;
            while (c) {
                if (c->left == NULL && c->right == NULL) {
                    break;
                }
                res.push_back(c->val);
                if (c->right) {
                    c = c->right;
                } else {
                    c = c->left;
                }
            }
        }
        return res;
    }
private:
    void dfs(TreeNode* node, vector<int>& res) {
        if (node->left == NULL && node->right == NULL) {
            res.push_back(node->val);
        } else {
            if (node->left) {
                dfs(node->left, res);
            }
            if (node->right) {
                dfs(node->right, res);
            }
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(4);
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = boundaryOfBinaryTree::Solution().boundaryOfBinaryTree(root);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
