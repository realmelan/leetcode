//
//  delNodes.cpp
//  leetcode
//
//  Created by Song Ding on 12/28/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace delNodes {
/*
// TODO: copy problem statement here
 Given the root of a binary tree, each node in the tree has a distinct value.

 After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

 Return the roots of the trees in the remaining forest.  You may return the result in any order.

  

 Example 1:



 Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
 Output: [[1,2,null,4],[6],[7]]
  

 Constraints:

 The number of nodes in the given tree is at most 1000.
 Each node has a distinct value between 1 and 1000.
 to_delete.length <= 1000
 to_delete contains distinct values between 1 and 1000.
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> toDel(begin(to_delete), end(to_delete));
        vector<TreeNode*> res;
        if (toDel.size()) {
            TreeNode pivot(0);
            pivot.left = root;
            dfs(&pivot, res, toDel);
        } else {
            if (root) {
                res.push_back(root);
            }
        }
        return res;
    }
    void dfs(TreeNode* root, vector<TreeNode*>& res, unordered_set<int>& toDel) {
        if (root) {
            dfs(root->left, res, toDel);
            dfs(root->right, res, toDel);
            if (root->left && toDel.count(root->left->val)) {
                delete root->left;
                root->left = nullptr;
            }
            if (root->right && toDel.count(root->right->val)) {
                delete root->right;
                root->right = nullptr;
            }
            if (toDel.count(root->val)) {
                if (root->left && !toDel.count(root->left->val)) {
                    res.push_back(root->left);
                }
                if (root->right && !toDel.count(root->right->val)) {
                    res.push_back(root->right);
                }
            }
        }
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> nodeVals;
        vector<int> to_delete;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{1,2,3,INT_MAX,INT_MAX,INT_MAX,4},{1,2}}
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = delNodes::Solution().delNodes(toTree(dp.nodeVals), dp.to_delete);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
