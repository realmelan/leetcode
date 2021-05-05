//
//  binaryTreeToLinkedList.cpp
//  leetcode
//
//  Created by  Song Ding on 12/12/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace binaryTreeToLinkedList {
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
        void flatten(TreeNode* root) {
            if (root == NULL) {
                return;
            }
            recur(root);
        }
    private:
        TreeNode* recur(TreeNode* root) {
            if (root->left == NULL && root->right == NULL) {
                return root;
            }
            
            TreeNode* right = root->right;
            TreeNode* rightEnd = NULL;
            if (root->right) {
                rightEnd = recur(root->right);
            }
            
            TreeNode* leftEnd = NULL;
            if (root->left) {
                leftEnd = recur(root->left);
                leftEnd->right = root->right;
                root->right = root->left;
                root->left = NULL;
            }
            
            if (rightEnd) {
                return rightEnd;
            } else {
                return leftEnd;
            }
        }
    };
}
/*
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    
    binaryTreeToLinkedList::Solution().flatten(root);
    
    return 0;
}
 */
