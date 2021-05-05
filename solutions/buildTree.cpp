// buildTree.cpp
// leetcode
//
// Created by  Song Ding on 6/5/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace buildTree {
/*
// TODO: copy problem statement here
 106. Construct Binary Tree from Inorder and Postorder Traversal
 Medium
 
 855
 
 18
 
 Favorite
 
 Share
 Given inorder and postorder traversal of a tree, construct the binary tree.
 
 Note:
 You may assume that duplicates do not exist in the tree.
 
 For example, given
 
 inorder = [9,3,15,20,7]
 postorder = [9,15,7,20,3]
 Return the following binary tree:
 
 3
 / \
 9  20
 /  \
 15   7
 */

class Solution {
public:
    /**
     * This recursive function builds the right child subtree first, thus depleting
     * postorder array one by one.
     */
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        unordered_map<int, int> index;
        for (int i = 0; i < n; ++i) {
            index[inorder[i]] = i;
        }
        return help(inorder, 0, n-1, postorder, index);
    }
    TreeNode* help(vector<int>& inorder, int start, int end, vector<int>& postorder, unordered_map<int, int>& index) {
        if (start > end) {
            return NULL;
        }
        
        int rv = postorder.back();
        postorder.pop_back();
        TreeNode* root = new TreeNode(rv);
        
        int split = index[rv];
        root->right = help(inorder, split+1, end, postorder, index);
        root->left = help(inorder, start, split-1, postorder, index);
        return root;
        
    }
    /**
     * recursive:
     *  the last element of postorder is the root node
     *  root node divides the inorder into two inorder parts.
     *  use length to divide the postorder into two parts.
     */
    TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        if (n <= 0) {
            return NULL;
        }
        
        int rv = postorder[n-1];
        TreeNode* root = new TreeNode(rv);
        
        vector<int> leftin, rightin;
        vector<int>* cv = &leftin;
        for (int i = 0; i < n; ++i) {
            if (inorder[i] == rv) {
                cv = &rightin;
            } else {
                cv->push_back(inorder[i]);
            }
        }
        
        vector<int> leftpost, rightpost;
        cv = &leftpost;
        for (int i = 0; i < n - 1; ++i) {
            if (leftpost.size() == leftin.size()) {
                cv = &rightpost;
            }
            cv->push_back(postorder[i]);
        }
        
        if (leftin.size()) {
            root->left = buildTree(leftin, leftpost);
        }
        if (rightin.size()) {
            root->right = buildTree(rightin, rightpost);
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
        vector<int> inorder;
        vector<int> postorder;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{9,3,15,20,7},{9,15,7,20,3}}
    };

    vector< vector<int> > answers {
        {3,9,20,INT_MAX,INT_MAX,15,7}
    };

    // TODO: update param3,9,ters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = buildTree::Solution().buildTree(dp.inorder, dp.postorder);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
