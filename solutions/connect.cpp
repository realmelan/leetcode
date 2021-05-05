// connect.cpp
// leetcode
//
// Created by  Song Ding on 10/7/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace connect {
/*
// TODO: copy problem statement here
 117. Populating Next Right Pointers in Each Node II
 Medium

 1051

 156

 Favorite

 Share
 Given a binary tree

 struct Node {
   int val;
   Node *left;
   Node *right;
   Node *next;
 }
 Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

 Initially, all next pointers are set to NULL.

  

 Example:



 Input: {"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":null,"next":null,"right":{"$id":"6","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}

 Output: {"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":{"$id":"5","left":null,"next":null,"right":null,"val":7},"right":null,"val":5},"right":null,"val":4},"next":{"$id":"6","left":null,"next":null,"right":{"$ref":"5"},"val":3},"right":{"$ref":"4"},"val":2},"next":null,"right":{"$ref":"6"},"val":1}

 Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B.
  

 Note:

 You may only use constant extra space.
 Recursive approach is fine, implicit stack space does not count as extra space for this problem.
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    TreeNode* connect(TreeNode* root) {
        TreeNode* parent = root;
        TreeNode head(0);
        head.next = root;
        while (parent) {
            TreeNode* current = &head;
            while (parent) {
                if (parent->left) {
                    current->next = parent->left;
                    current = current->next;
                }
                if (parent->right) {
                    current->next = parent->right;
                    current = current->next;
                }
                parent = parent->next;
            }
            parent = head.next;
            head.next = NULL;
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
        vector<int> nodeVals;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{1,2,3,4,5,INT_MAX,7}},
    };

    vector< TreeNode* > answers {
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = connect::Solution().connect(toTree(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
