//
//  isValidBST.cpp
//  leetcode
//
//  Created by Song Ding on 6/29/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace isValidBST {
/*
// TODO: copy problem statement here
 98. Validate Binary Search Tree
 Medium

 3790

 527

 Add to List

 Share
 Given a binary tree, determine if it is a valid binary search tree (BST).

 Assume a BST is defined as follows:

 The left subtree of a node contains only nodes with keys less than the node's key.
 The right subtree of a node contains only nodes with keys greater than the node's key.
 Both the left and right subtrees must also be binary search trees.
  

 Example 1:

     2
    / \
   1   3

 Input: [2,1,3]
 Output: true
 Example 2:

     5
    / \
   1   4
      / \
     3   6

 Input: [5,1,4,null,null,3,6]
 Output: false
 Explanation: The root node's value is 5 but its right child's value is 4.
*/
class Solution {
public:
    // TODO: copy function signature here
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        while (cur || !s.empty()) {
            if (cur) {
                s.push(cur);
                cur = cur->left;
            } else {
                cur = s.top();
                s.pop();
                if (prev && prev->val >= cur->val) {
                    return false;
                }
                prev = cur;
                cur = cur->right;
            }
        }
        return true;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nodeVals;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{2,1,3}},
    };
    // TODO: provide expected results here
    vector<bool> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = isValidBST::Solution().isValidBST(toTree(dp.nodeVals));
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
