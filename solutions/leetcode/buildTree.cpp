//
//  buildTree.cpp
//  leetcode
//
//  Created by  Song Ding on 12/25/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace buildTree {
    /**
     * Definition for a binary tree node.
     * struct TreeNode {
     *     int val;
     *     TreeNode *left;
     *     TreeNode *right;
     *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     * };
     */
    class Solution {
    public:
        /**
         Recursively:
         using the root node to separate the left side and right side.
         */
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
            if (preorder.empty()) {
                return NULL;
            }
            int len = preorder.size();
            int rootVal = preorder[0];
            TreeNode* root = new TreeNode(rootVal);
            if (len == 1) {
                return root;
            }
            auto it = find(inorder.begin(), inorder.end(), rootVal);
            vector<int> leftInorder, leftPreorder;
            vector<int> rightInorder, rightPreorder;
            if (it == inorder.begin()) {
                rightInorder.insert(rightInorder.end(), it + 1, inorder.end());
                auto pit = preorder.begin();
                rightPreorder.insert(rightPreorder.end(), pit + 1, preorder.end());
                
                root->right = buildTree(rightPreorder, rightInorder);
            } else if (rootVal == inorder[len - 1]) {
                leftInorder.insert(leftInorder.end(), inorder.begin(), inorder.begin() + len - 1);
                leftPreorder.insert(leftPreorder.end(), preorder.begin() + 1, preorder.end());
                
                root->left = buildTree(leftPreorder, leftInorder);
            } else {
                leftInorder.insert(leftInorder.end(), inorder.begin(), it);
                rightInorder.insert(rightInorder.end(), it + 1, inorder.end());
                int leftSize = leftInorder.size();
                int rightSize = len - 1 - leftSize;
                auto pit = preorder.begin() + leftSize + 1;
                leftPreorder.insert(leftPreorder.end(), preorder.begin() + 1, pit);
                rightPreorder.insert(rightPreorder.end(), pit, preorder.end());
                
                root->left = buildTree(leftPreorder, leftInorder);
                root->right = buildTree(rightPreorder, rightInorder);
            }
            return root;
        }
    };
}
/*
int main() {
    vector<int> pre{1,2};
    vector<int> in{2,1};
    TreeNode* root = buildTree::Solution().buildTree(pre, in);
    return 0;
}
 */
