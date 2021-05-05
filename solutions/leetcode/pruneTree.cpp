// pruneTree.cpp
// leetcode
//
// Created by  Song Ding on 5/8/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace pruneTree {

class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        bool ret = prune(root);
        if (ret) {
            return NULL;
        }
        return root;
    }

private:
    bool prune(TreeNode* c) {
        if (c == NULL) {
            return true;
        } else if (c->left == NULL && c->right == NULL) {
            return c->val == 0;
        } else {
            bool leftAllZero = true;
            if (c->left) {
                leftAllZero = prune(c->left);
            }
            if (leftAllZero) {
                c->left = NULL;
            }
            
            bool rightAllZero = true;
            if (c->right) {
                rightAllZero = prune(c->right);
            }
            if (rightAllZero) {
                c->right = NULL;
            }
            
            return leftAllZero && rightAllZero && c->val == 0;
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(0);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(1);
    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = pruneTree::Solution().pruneTree(root);
    cout << clock() - start << endl;
    //cout << res << endl;
    return 0;
}
//*/
