//
//  completeBinaryTreeNodeCount.cpp
//  leetcode
//
//  Created by  Song Ding on 1/10/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace completeBinaryTreeNodeCount {
    class Solution {
    public:
        /**
         use breadth first search to reach the first node
         who does't have two children nodes. From this one onward,
         no node shall have any child node.
         */
        /**
         A half of a complete binary tree is a full binary tree,
         thus the # of nodes is determined by height of the half.
         */
        int countNodes(TreeNode* root) {
            int res = 0;
            TreeNode* current = root;
            int h = height(current);
            while (current) {
                int hr = height(current->right);
                if (hr == h - 1) {
                    res += 1 << h;
                    current = current->right;
                } else {
                    res += 1 << h - 1;
                    current = current->left;
                }
                --h;
            }
            return res;
        }
    private:
        int height(TreeNode* root) {
            return root == NULL ? -1 : 1 + height(root->left);
        }
    };
}
/*
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    cout << completeBinaryTreeNodeCount::Solution().countNodes(root) << endl;
    return 0;
}
 */
