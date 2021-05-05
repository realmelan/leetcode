// isCompleteTree.cpp
// leetcode
//
// Created by  Song Ding on 5/16/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace isCompleteTree {
/*
 958. Check Completeness of a Binary Tree
 Medium
 
 197
 
 5
 
 Favorite
 
 Share
 Given a binary tree, determine if it is a complete binary tree.
 
 Definition of a complete binary tree from Wikipedia:
 In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
 
 
 
 Example 1:
 
 
 
 Input: [1,2,3,4,5,6]
 Output: true
 Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
 Example 2:
 
 
 
 Input: [1,2,3,4,5,null,7]
 Output: false
 Explanation: The node with value 7 isn't as far left as possible.
 
 Note:
 
 The tree will have between 1 and 100 nodes.
 */
class Solution {
public:
    /**
     * Use a queue to traverse tree by depth.
     * These conditions should be met:
     * 1, During traversal, if a node is met with <=1 child node, then all
     * nodes encountered thereafter should have 0 child node.
     * 2, if a node is met with <=1 child node, then it should be at the last
     * level, which means the top of the stack should be NULL after traversal is done.
     *
     * Levels can be divided by inserting a NULL node after root node,
     * and then insert a NULL node when popping a NULL node from the stack.
     *
     *
     */
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> s;
        s.push(root);
        s.push(NULL);
        
        TreeNode* cur = NULL;
        bool inComplete = false;
        while (s.size()) {
            cur = s.front();
            s.pop();
            if (cur == NULL) {
                if (s.empty()) {
                    return true;
                } else {
                    s.push(NULL);
                }
            } else if (inComplete) {
                if (cur->left != NULL || cur->right != NULL) {
                    return false;
                }
            } else {
                if (cur->left) {
                    s.push(cur->left);
                    if (cur->right) {
                        s.push(cur->right);
                    } else {
                        inComplete = true;
                    }
                } else {
                    inComplete = true;
                    if (cur->right) {
                        return false;
                    }
                }
            }
        }
        return false;
    }

private:
};

}

/*/
int main() {
    // TODO: prepare parameters here
    vector< vector<int> > p {
        {1,2,3,4,5,6},
        {1,2,3,4,5,INT_MAX,7}
    };

    vector< bool  > answers {
        true,
        false
    };
    int i = 1;

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    auto res = isCompleteTree::Solution().isCompleteTree(toTree(p[i]));
    cout << clock() - tstart << endl;
    cout << res << endl;
    return 0;
}
//*/
