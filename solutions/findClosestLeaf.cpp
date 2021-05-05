// findClosestLeaf.cpp
// leetcode
//
// Created by  Song Ding on 10/16/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findClosestLeaf {
/*
// TODO: copy problem statement here

 */

class Solution {
public:
    /**
     * use a vector to record the path from root to k
     * for each ancestor of k, find the closest leaf on the subtree that doesn't have k,
     * then the closest leaf rooted at this ancestor is root to leaf + root to k.
     */
    int findClosestLeaf(TreeNode* root, int k) {
        vector<TreeNode*> path;
        findk(root, k, path);
        int minDist = INT_MAX;
        TreeNode* res = NULL;
        for (int i = 0; i < path.size()-1; ++i) {
            TreeNode* cur = path[i], *next = path[i+1], *leaf = NULL;
            int ld = 1+findleaf((cur->left == next ? cur->right : cur->left), &leaf);
            if (ld + path.size() - 1 - i < minDist) {
                minDist = ld + path.size() - i;
                res = leaf;
            }
        }
        TreeNode* kleaf = NULL;
        int kd = findleaf(path.back(), &kleaf);
        if (kd < minDist) {
            return kleaf->val;
        } else {
            return res->val;
        }
    }
    bool findk(TreeNode* root, int k, vector<TreeNode*>& path) {
        if (root->val == k) {
            path.push_back(root);
            return true;
        }
        if (root->left) {
            path.push_back(root);
            if (findk(root->left, k, path)) {
                return true;
            }
            path.pop_back();
        }
        if (root->right) {
            path.push_back(root);
            if (findk(root->right, k, path)) {
                return true;
            }
            path.pop_back();
        }
        return false;
    }
    int findleaf(TreeNode* root, TreeNode** leaf) {
        if (root->left == NULL && root->right == NULL) {
            *leaf = root;
            return 0;
        } else if (root->left == NULL) {
            return 1+findleaf(root->right, leaf);
        } else if (root->right == NULL) {
            return 1+findleaf(root->left, leaf);
        } else {
            TreeNode* lleaf = NULL, *rleaf = NULL;
            int ld = findleaf(root->left, &lleaf);
            int rd = findleaf(root->right, &rleaf);
            if (ld < rd) {
                *leaf = lleaf;
                return 1+ld;
            } else {
                *leaf = rleaf;
                return 1+rd;
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
        int k;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,3,2},1},
        {{1},1},
        {{1,2,3,4,INT_MAX,INT_MAX,INT_MAX,5,INT_MAX,6}, 2}
    };

    vector< int > answers {
        1,
        0,
        2,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = findClosestLeaf::Solution().findClosestLeaf(toTree(dp.nodeVals), dp.k);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
