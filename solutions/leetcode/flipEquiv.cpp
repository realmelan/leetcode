// flipEquiv.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace flipEquiv {
/*
// TODO: copy problem statement here
 951. Flip Equivalent Binary Trees
 Medium
 
 219
 
 8
 
 Favorite
 
 Share
 For a binary tree T, we can define a flip operation as follows: choose any node, and swap the left and right child subtrees.
 
 A binary tree X is flip equivalent to a binary tree Y if and only if we can make X equal to Y after some number of flip operations.
 
 Write a function that determines whether two binary trees are flip equivalent.  The trees are given by root nodes root1 and root2.
 
 
 
 Example 1:
 
 Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
 Output: true
 Explanation: We flipped at nodes with values 1, 3, and 5.
 Flipped Trees Diagram
 
 
 Note:
 
 Each tree will have at most 100 nodes.
 Each value in each tree will be a unique integer in the range [0, 99].
 */

class Solution {
public:
    /**
     * recursive
     */
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if (root1 == NULL && root2 == NULL) {
            return true;
        } else if (root1 == NULL || root2 == NULL) {
            return false;
        } else {
            if (root1->val != root2->val) {
                return false;
            }
            
            TreeNode* left = root2->left;
            TreeNode* right = root2->right;
            if ((root1->left != NULL && left == NULL)
                || (root1->left == NULL && left != NULL)
                || (root1->left != NULL && left != NULL && root1->left->val != left->val)) {
                swap(left, right);
            }
            return flipEquiv(root1->left, left)
            && flipEquiv(root1->right, right);
        }
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> root1;
        vector<int> root2;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,4,5,6,INT_MAX,INT_MAX,INT_MAX,7,8},{1,3,2,INT_MAX,6,4,5,INT_MAX,INT_MAX,INT_MAX,INT_MAX,8,7}}
    };

    vector< bool > answers {
        true
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = flipEquiv::Solution().flipEquiv(toTree(dp.root1), toTree(dp.root2));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
