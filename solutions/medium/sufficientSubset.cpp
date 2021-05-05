// sufficientSubset.cpp
// leetcode
//
// Created by  Song Ding on 6/12/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace sufficientSubset {
/*
// TODO: copy problem statement here
 Given the root of a binary tree, consider all root to leaf paths: paths from the root to any leaf.  (A leaf is a node with no children.)
 
 A node is insufficient if every such root to leaf path intersecting this node has sum strictly less than limit.
 
 Delete all insufficient nodes simultaneously, and return the root of the resulting binary tree.
 
 
 
 Example 1:
 
 
 Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
 
 Output: [1,2,3,4,null,null,7,8,9,null,14]
 Example 2:
 
 
 Input: root = [5,4,8,11,null,17,4,7,1,null,null,5,3], limit = 22
 
 Output: [5,4,8,11,null,17,4,7,null,null,null,5]
 
 
 Example 3:
 
 
 Input: root = [1,2,-3,-5,null,4,null], limit = -1
 
 Output: [1,null,-3,4]
 
 
 Note:
 
 The given tree will have between 1 and 5000 nodes.
 -10^5 <= node.val <= 10^5
 -10^9 <= limit <= 10^9
 */

class Solution {
public:
    /**
     * recursive:
     *  let each child return a list of leaf to current node sums; also from
     *  top down, there is a sum of root to current node.
     *  thus, at each node, a path sum can be computed.
     *
     */
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        set<int> childSums;
        recur(root, 0, limit, childSums);
        if (childSums.lower_bound(limit) == childSums.end()) {
            root = NULL;
        }
        return root;
    }

private:
    void recur(TreeNode* root, int sumAbove, int limit, set<int>& sums) {
        if (root->left == NULL && root->right == NULL) {
            sums.insert(sumAbove + root->val);
        } else {
            if (root->left) {
                set<int> lsums;
                recur(root->left, sumAbove+root->val, limit, lsums);
                sums.insert(lsums.begin(), lsums.end());
                if (lsums.lower_bound(limit) == lsums.end()) {
                    root->left = NULL;
                }
            }
            
            if (root->right) {
                set<int> rsums;
                recur(root->right, sumAbove+root->val, limit, rsums);
                sums.insert(rsums.begin(), rsums.end());
                if (rsums.lower_bound(limit) == rsums.end()) {
                    root->right = NULL;
                }
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
        int limit;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14},1},
        {{5,4,8,11,INT_MAX,17,4,7,1,INT_MAX,INT_MAX,5,3},22},
        {{1,2,-3,-5,INT_MAX,4,INT_MAX},-1}
    };

    vector< vector<int> > answers {
        {1,2,3,4,INT_MAX,INT_MAX,7,8,9,INT_MAX,14},
        {5,4,8,11,INT_MAX,17,4,7,INT_MAX,INT_MAX,INT_MAX,5},
        {1,INT_MAX,-3,4}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = sufficientSubset::Solution().sufficientSubset(toTree(dp.nodeVals), dp.limit);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
