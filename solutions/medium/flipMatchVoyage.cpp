// flipMatchVoyage.cpp
// leetcode
//
// Created by  Song Ding on 6/9/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace flipMatchVoyage {
/*
// TODO: copy problem statement here
 971. Flip Binary Tree To Match Preorder Traversal
 Medium
 
 119
 
 52
 
 Favorite
 
 Share
 Given a binary tree with N nodes, each node has a different value from {1, ..., N}.
 
 A node in this binary tree can be flipped by swapping the left child and the right child of that node.
 
 Consider the sequence of N values reported by a preorder traversal starting from the root.  Call such a sequence of N values the voyage of the tree.
 
 (Recall that a preorder traversal of a node means we report the current node's value, then preorder-traverse the left child, then preorder-traverse the right child.)
 
 Our goal is to flip the least number of nodes in the tree so that the voyage of the tree matches the voyage we are given.
 
 If we can do so, then return a list of the values of all nodes flipped.  You may return the answer in any order.
 
 If we cannot do so, then return the list [-1].
 
 
 
 Example 1:
 
 
 
 Input: root = [1,2], voyage = [2,1]
 Output: [-1]
 Example 2:
 
 
 
 Input: root = [1,2,3], voyage = [1,3,2]
 Output: [1]
 Example 3:
 
 
 
 Input: root = [1,2,3], voyage = [1,2,3]
 Output: []
 
 
 Note:
 
 1 <= N <= 100
 */

class Solution {
public:
    /**
     * start from root node, compare left child against the value
     * just after root value in voyage:
     *  if it's a match, find index of right child value, and recursively
     *    call flip on both left and right child
     *  if not a match, check whether it matches value of right child
     *    return false if not; otherwise, a flip is needed and find the value
     *    for left child, and recursively check flip on left and right child.
     */
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> res;
        unordered_map<int, int> index;
        int n = voyage.size();
        for (int i = 0; i < n; ++i) {
            index[voyage[i]] = i;
        }
        if (!checkFlip(root, voyage, index, 0, n-1, res)) {
            res.clear();
            res.push_back(-1);
        }
        return res;
    }

private:
    bool checkFlip(TreeNode* root, vector<int>& voyage, unordered_map<int,int>& index, int start, int end, vector<int>& res) {
        if (start > end || root->val != voyage[start]) {
            return false;
        } else if (root->left == NULL && root->right == NULL) {
            return start == end;
        } else if (root->left == NULL || root->right == NULL) {
            TreeNode* child = root->left;
            if (!child) {
                child = root->right;
            }
            return checkFlip(child, voyage, index, start+1, end, res);
        } else {
            if (voyage[start+1] == root->left->val) {
                int rval = root->right->val;
                int rid = index[rval];
                return checkFlip(root->left, voyage, index, start+1, rid-1, res)
                && checkFlip(root->right, voyage, index, rid, end, res);
            } else if (voyage[start+1] == root->right->val) {
                res.push_back(root->val);
                int lval = root->left->val;
                int lid = index[lval];
                return checkFlip(root->left, voyage, index, lid, end, res)
                && checkFlip(root->right, voyage, index, start+1, lid-1, res);
            } else {
                return false;
            }
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
        vector<int> voyage;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        //{{1,2},{2,1}},
        //{{1,2,3},{1,3,2}},
        //{{1,2,3},{1,2,3}}
        {{5,1,2,INT_MAX,INT_MAX,4,3},{5,2,3,4,1}}
    };

    vector< vector<int> > answers {
        {-1},
        {1},
        {},
        {5,2}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = flipMatchVoyage::Solution().flipMatchVoyage(toTree(dp.nodeVals), dp.voyage);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
