// bstFromPreorder.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace bstFromPreorder {
/*
// TODO: copy problem statement here
 1008. Construct Binary Search Tree from Preorder Traversal
 Medium
 
 199
 
 9
 
 Favorite
 
 Share
 Return the root node of a binary search tree that matches the given preorder traversal.
 
 (Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)
 
 
 
 Example 1:
 
 Input: [8,5,1,7,10,12]
 Output: [8,5,10,1,7,null,12]
 
 
 
 Note:
 
 1 <= preorder.length <= 100
 The values of preorder are distinct.
 */

class Solution {
public:
    /**
     * recursive:
     *   the first node is root, and find the next value which is larger than 1st element
     *   this is the start of the right subtree.
     */
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int n = preorder.size();
        int rv = preorder[0];
        TreeNode* root = new TreeNode(rv);
        vector<int> left, right;
        vector<int>*p = &left;
        for (int i = 1; i < n; ++i) {
            if (preorder[i] > rv) {
                p = &right;
            }
            p->push_back(preorder[i]);
        }
        if (left.size()) {
            root->left = bstFromPreorder(left);
        }
        if (right.size()) {
            root->right = bstFromPreorder(right);
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
        vector<int> preorder;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{8,5,1,7,10,12}}
    };

    vector< vector<int> > answers {
        {8,5,10,1,7,INT_MAX,12}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = bstFromPreorder::Solution().bstFromPreorder(dp.preorder);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
