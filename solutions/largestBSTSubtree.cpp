// largestBSTSubtree.cpp
// leetcode
//
// Created by  Song Ding on 10/30/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace largestBSTSubtree {
/*
// TODO: copy problem statement here
 333. Largest BST Subtree

 Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.

 Note:
 A subtree must include all of its descendants.
 Here\'s an example:

     10
     / \\
    5  15
   / \\   \\
  1   8   7
 The Largest BST Subtree in this case is the highlighted one.
 The return value is the subtree\'s size, which is 3.
 Follow up:
 Can you figure out ways to solve it with O(n) time complexity?
 */

class Solution {
public:
    /**
     * first, have to check whether a subtree is a BST, and then count the # of nodes in the subtree.
     */
    int largestBSTSubtree(TreeNode* root) {
        int res = 0;
        if (root) {
            res = 1;
            dfs2(root, res);
        }
        return res;
    }

private:
    vector<int> dfs2(TreeNode* root, int& res) {
        if (root->left == NULL && root->right == NULL) {
            res = max(res, 1);
            return {root->val, root->val, 1};
        } else if (root->left == NULL) {
            vector<int> right = dfs2(root->right, res);
            if (root->val < right[0]) {
                res = max(res, 1+right[2]);
                return {root->val, right[1], 1+right[2]};
            } else {
                return {INT_MIN, INT_MAX, 0};
            }
        } else if (root->right == NULL) {
            vector<int> left = dfs2(root->left, res);
            if (root->val > left[1]) {
                res = max(res, 1+left[2]);
                return {left[0], root->val, 1+left[2]};
            } else {
                return {INT_MIN, INT_MAX, 0};
            }
        } else {
            vector<int> left = dfs2(root->left, res);
            vector<int> right = dfs2(root->right, res);
            if (root->val > left[1] && root->val < right[0]) {
                res = max(res, 1+left[2] + right[2]);
                return {left[0], right[1], 1+left[2]+right[2]};
            } else {
                return {INT_MIN, INT_MAX, 0};
            }
        }
    }
    
    void dfs(TreeNode* root, int& res) {
        if (root == NULL) {
            return;
        }
        if (isBst(root->left, INT_MIN, root->val) && isBst(root->right, root->val, INT_MAX)) {
            res = max(res, count(root));
        } else {
            dfs(root->left, res);
            dfs(root->right, res);
        }
    }
    bool isBst(TreeNode* root, int lb, int rb) {
        if (root == NULL) {
            return true;
        } else if (root->val <= lb || root->val >= rb) {
            return false;
        } else {
            return isBst(root->left, lb, root->val) && isBst(root->right, root->val, rb);
        }
    }
    int count(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        return 1 + count(root->left) + count(root->right);
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
        {{10,5,15,1,8,7,INT_MAX}},
    };

    vector< int > answers {
        3,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = largestBSTSubtree::Solution().largestBSTSubtree(toTree(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
