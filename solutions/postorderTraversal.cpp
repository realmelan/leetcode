//
//  postorderTraversal.cpp
//  leetcode
//
//  Created by Song Ding on 6/23/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace postorderTraversal {
/*
// TODO: copy problem statement here
 145. Binary Tree Postorder Traversal
 Hard

 1668

 87

 Add to List

 Share
 Given a binary tree, return the postorder traversal of its nodes' values.

 Example:

 Input: [1,null,2,3]
    1
     \
      2
     /
    3

 Output: [3,2,1]
 Follow up: Recursive solution is trivial, could you do it iteratively?
*/
class Solution {
public:
    // TODO: copy function signature here
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        // cur points to a node whose left child isn't visited yet.
        TreeNode* cur = root, *last = NULL;
        while (cur != nullptr || s.size()) {
            if (cur) {
                s.push(cur);
                cur = cur->left;
            } else {
                TreeNode* t = s.top();
                if (t->right != nullptr && t->right != last) {
                    cur = t->right;
                } else {
                    res.push_back(t->val);
                    last = t;
                    s.pop();
                }
            }
        }
        return res;
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
        {{1,INT_MAX,2,3}}
    };
    // TODO: provide expected results here
    vector<vector<int>> answers {
        {3,2,1}
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = postorderTraversal::Solution().postorderTraversal(toTree(dp.nodeVals));
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
