// insertIntoBST.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace insertIntoBST {
/*
// TODO: copy problem statement here
 701. Insert into a Binary Search Tree
 Medium
 
 327
 
 39
 
 Favorite
 
 Share
 Given the root node of a binary search tree (BST) and a value to be inserted into the tree, insert the value into the BST. Return the root node of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.
 
 Note that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.
 
 For example,
 
 Given the tree:
 4
 / \
 2   7
 / \
 1   3
 And the value to insert: 5
 You can return this binary search tree:
 
 4
 /   \
 2     7
 / \   /
 1   3 5
 This tree is also valid:
 
 5
 /   \
 2     7
 / \
 1   3
 \
 4

 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL) {
            return new TreeNode(val);
        }
        
        TreeNode* c = root;
        TreeNode* p = NULL;
        while (c) {
            p = c;
            if (val < c->val) {
                c = c->left;
            } else {
                c = c->right;
            }
        }
        if (val > p->val) {
            p->right = new TreeNode(val);
        } else {
            p->left = new TreeNode(val);
        }
        return root;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
        int val;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{4,2,7,1,3},5},
        {{},1}
    };

    vector< vector<int> > answers {
        {4,2,7,1,3,5},
        {1}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = insertIntoBST::Solution().insertIntoBST(toTree(dp.nodeVals), dp.val);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
