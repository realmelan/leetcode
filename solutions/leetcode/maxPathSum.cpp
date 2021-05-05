// maxPathSum.cpp
// leetcode
//
// Created by  Song Ding on 3/25/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxPathSum {

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = 0;
        if (root != NULL) {
            dfs(root, res);
        }
        return res;
    }

private:
    int dfs(TreeNode* node, int& res) {
        if (node->left == NULL && node->right == NULL) {
            return node->val;
        }
        
        int val = node->val;
        int leftMax = INT_MIN;
        if (node->left) {
            leftMax = dfs(node->left, res);
        }
        
        int rightMax = INT_MIN;
        if (node->right) {
            rightMax = dfs(node->right, res);
        }
        
        int sum = val;
        if (leftMax > 0) {
            sum += leftMax;
        }
        if (rightMax > 0) {
            sum += rightMax;
        }
        
        if (sum > res) {
            res = sum;
        }
        
        return val + max(0, max(leftMax, rightMax));
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    // TODO: add return type and paramters.
    clock_t start = clock();
    auto res = maxPathSum::Solution().maxPathSum(root);
    cout << clock() - start << endl;
    cout << res << endl;
    return 0;
}
//*/
