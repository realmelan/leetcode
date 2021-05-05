// insertIntoMaxTree.cpp
// leetcode
//
// Created by  Song Ding on 5/31/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace insertIntoMaxTree {
/*
// TODO: copy problem statement here
 998. Maximum Binary Tree II
 Medium
 
 65
 
 155
 
 Favorite
 
 Share
 We are given the root node of a maximum tree: a tree where every node has a value greater than any other value in its subtree.
 
 Just as in the previous problem, the given tree was constructed from an list A (root = Construct(A)) recursively with the following Construct(A) routine:
 
 If A is empty, return null.
 Otherwise, let A[i] be the largest element of A.  Create a root node with value A[i].
 The left child of root will be Construct([A[0], A[1], ..., A[i-1]])
 The right child of root will be Construct([A[i+1], A[i+2], ..., A[A.length - 1]])
 Return root.
 Note that we were not given A directly, only a root node root = Construct(A).
 
 Suppose B is a copy of A with the value val appended to it.  It is guaranteed that B has unique values.
 
 Return Construct(B).
 
 
 
 Example 1:
 
 
 
 Input: root = [4,1,3,null,null,2], val = 5
 Output: [5,4,null,1,3,null,null,2]
 Explanation: A = [1,4,2,3], B = [1,4,2,3,5]
 Example 2:
 
 
 Input: root = [5,2,4,null,1], val = 3
 Output: [5,2,4,null,1,null,3]
 Explanation: A = [2,1,5,4], B = [2,1,5,4,3]
 Example 3:
 
 
 Input: root = [5,2,3,null,1], val = 4
 Output: [5,2,4,null,1,3]
 Explanation: A = [2,1,5,3], B = [2,1,5,3,4]
 
 
 Note:
 
 1 <= B.length <= 100
 */

class Solution {
public:
    /**
     *
     */
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        TreeNode pivot(0);
        pivot.right = root;
        
        TreeNode* p = &pivot;
        TreeNode* c = root;
        while (c && c->val >= val) {
            p = c;
            c = c->right;
        }
        
        p->right = new TreeNode(val);
        p->right->left = c;
        return pivot.right;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> nodeVals;
        int val;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{4,1,3,INT_MAX,INT_MAX,2}, 5},
        {{5,2,4,INT_MAX,1}, 3},
        {{5,2,3,INT_MAX,1},4}
    };

    vector< vector<int> > answers {
        {5,4,INT_MAX,1,3,INT_MAX,INT_MAX,2},
        {5,2,4,INT_MAX,1,INT_MAX,3},
        {5,2,4,INT_MAX,1,3}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = insertIntoMaxTree::Solution().insertIntoMaxTree(toTree(dp.nodeVals), dp.val);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
