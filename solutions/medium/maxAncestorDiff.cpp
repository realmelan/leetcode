// maxAncestorDiff.cpp
// leetcode
//
// Created by  Song Ding on 6/11/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace maxAncestorDiff {
/*
// TODO: copy problem statement here
 1026. Maximum Difference Between Node and Ancestor
 Medium
 
 124
 
 8
 
 Favorite
 
 Share
 Given the root of a binary tree, find the maximum value V for which there exists different nodes A and B where V = |A.val - B.val| and A is an ancestor of B.
 
 (A node A is an ancestor of B if either: any child of A is equal to B, or any child of A is an ancestor of B.)
 
 
 
 Example 1:
 
 
 
 Input: [8,3,10,1,6,null,14,null,null,4,7,13]
 Output: 7
 Explanation:
 We have various ancestor-node differences, some of which are given below :
 |8 - 3| = 5
 |3 - 7| = 4
 |8 - 1| = 7
 |10 - 13| = 3
 Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
 
 
 Note:
 
 The number of nodes in the tree is between 2 and 5000.
 Each node will have value between 0 and 100000.
 */

class Solution {
public:
    /**
     * recursive:
     *   recur() will return min/max value in the subtree rooted at root,
     *   and update mdiff with the diff found within subtree.
     */
    int maxAncestorDiff(TreeNode* root) {
        int res = 0;
        if (root != NULL) {
            recur(root, res);
        }
        return res;
    }

private:
    pair<int,int> recur(TreeNode* root, int& res) {
        int lmin = root->val;
        int lmax = root->val;
        int mdiff = 0;
        if (root->left != NULL) {
            auto p = recur(root->left, res);
            lmin = min(lmin, p.first);
            lmax = max(lmax, p.second);
            mdiff = max(mdiff, max(abs(root->val - p.first), abs(root->val - p.second)));
        }
        if (root->right != NULL) {
            auto p = recur(root->right, res);
            lmin = min(lmin, p.first);
            lmax = max(lmax, p.second);
            mdiff = max(mdiff, max(abs(root->val - p.first), abs(root->val - p.second)));
        }
        
        res = max(res, mdiff);
        return {lmin, lmax};
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{8,3,10,1,6,INT_MAX,14,INT_MAX,INT_MAX,4,7,13}}
    };

    vector< int > answers {
        7
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxAncestorDiff::Solution().maxAncestorDiff(toTree(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
