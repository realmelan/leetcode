//
//  HouseRobber.cpp
//  leetcode
//
//  Created by  Song Ding on 10/16/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include <stdio.h>
#include <unordered_map>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int v) : val(v), left(NULL), right(NULL) {
    }
};
int rob(TreeNode* root) {
    static unordered_map<TreeNode*, int> nodeMax;
    if (!root) {
        return 0;
    }
    if (nodeMax.find(root) != nodeMax.end()) {
        return nodeMax[root];
    }
    
    int leftMax = 0;
    int grandLeftMax = 0;
    if (root->left) {
        leftMax = rob(root->left);
        if (root->left->left) {
            grandLeftMax += rob(root->left->left);
        }
        if (root->left->right) {
            grandLeftMax += rob(root->left->right);
        }
    }
    
    int rightMax = 0;
    int grandRightMax = 0;
    if (root->right) {
        rightMax = rob(root->right);
        if (root->right->left) {
            grandRightMax += rob(root->right->left);
        }
        if (root->right->right) {
            grandRightMax += rob(root->right->right);
        }
    }
    
    int res = root->val + grandLeftMax + grandRightMax;
    if (res < leftMax + rightMax) {
        res = leftMax + rightMax;
    }
    
    nodeMax.insert(make_pair(root, res));
    return res;
}

/*
int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);
    
    cout << rob(root) << endl;
    return 0;
}
 */
