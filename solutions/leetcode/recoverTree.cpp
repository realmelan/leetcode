// recoverTree.cpp
// leetcode
//
// Created by  Song Ding on 10/31/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace recoverTree {
/**
 99. Recover Binary Search Tree
 Hard

 971

 55

 Favorite

 Share
 Two elements of a binary search tree (BST) are swapped by mistake.

 Recover the tree without changing its structure.

 Example 1:

 Input: [1,3,null,null,2]

    1
   /
  3
   \
    2

 Output: [3,1,null,null,2]

    3
   /
  1
   \
    2
 Example 2:

 Input: [3,1,4,null,null,2]

   3
  / \
 1   4
    /
   2

 Output: [2,1,4,null,null,3]

   2
  / \
 1   4
    /
   3
 Follow up:

 A solution using O(n) space is pretty straight forward.
 Could you devise a constant space solution?
 */
class Solution {
public:
    /**
     * https://leetcode.com/problems/recover-binary-search-tree/discuss/32559/Detail-Explain-about-How-Morris-Traversal-Finds-two-Incorrect-Pointer
     * as recursive call takes average O(lgn) stack space and worst case O(n), it might not be able to counted as O(1) space.
     * However Morrais Traversal may help. Basically morrais traversal creates threading from predecessor to current node, so that
     * current node and its right subtree can be visited after visiting the predecessor. The threading is on a leaf node's right pointer,
     * and it will be reset to NULL after moving from it to its successor.
     */
    void recoverTree_morrais(TreeNode* root) {
        TreeNode* first = NULL, *second = NULL, *prev = NULL;
        TreeNode* cur = root;
        while (cur != NULL) {
            if (cur->left == NULL) {
                //cout << cur->val << ",";
                if (prev != NULL && prev->val > cur->val) {
                    if (first == NULL) {
                        first = prev;
                    }
                    second = cur;
                }
                prev = cur;
                cur = cur->right; // it leads to its successor
            } else {
                TreeNode* pred = cur->left;
                while (pred->right != NULL && pred->right != cur) {
                    pred = pred->right;
                }
                if (pred->right == NULL) { // create threading
                    pred->right = cur;
                    cur = cur->left; // after creating thread, move downward
                } else {
                    pred->right = NULL; // reset threading pointer
                    // after moving upward through threading, visit current node, and move the right subtree.
                    //cout << cur->val << ",";
                    if (prev != NULL && prev->val > cur->val) {
                        if (first == NULL) {
                            first = prev;
                        }
                        second = cur;
                    }
                    prev = cur;
                    cur = cur->right;
                }
            }
        }
        swap(first->val, second->val);
    }
    /**
     * https://leetcode.com/problems/recover-binary-search-tree/discuss/32535/No-Fancy-Algorithm-just-Simple-and-Powerful-In-Order-Traversal
     */
    void recoverTree(TreeNode* root) {
        TreeNode* prev = new TreeNode(INT_MIN), *first = NULL, *second = NULL;
        inorder(root, &prev, &first, &second);
        swap(first->val, second->val);
    }
    void inorder(TreeNode* root, TreeNode** prev, TreeNode** first, TreeNode** second) {
        if (!root) {
            return;
        }
        inorder(root->left, prev, first, second);
        if (*first == NULL && (*prev)->val > root->val) {
            *first = *prev;
        }
        if (*first != NULL && (*prev)->val > root->val) {
            *second = root;
        }
        *prev = root;
        
        inorder(root->right, prev, first, second);
    }
    /**
     * Do in-order traversal to find the node who is larger than its successor.
     *  keep the largest element encountered. When visiting a new node, compare it with the largest
     *  element. If it is smaller than the largest, then the largest element is the one
     *  which is out of place.
     *
     * Do reversed in-order traversal to find the node who is smaller than its predecessor
     *  Same as above, but keep the smallest element.
     */
    void recoverTree2(TreeNode* root) {
        if (root == NULL) {
            return;
        }
        TreeNode* e1 = NULL, *e2 = NULL;
        find(root, false, &e1);
        find(root, true, &e2);
        
        swap(e1->val, e2->val);
    }

private:
    bool find(TreeNode* root, bool reversed, TreeNode** res) {
        if (!reversed) {
            if (root->left) {
                if (find(root->left, reversed, res)) {
                    return true;
                }
            }
            
            if (*res == NULL) {
                *res = root;
            } else if ((*res)->val > root->val) {
                return true;
            } else {
                *res = root;
            }
            
            if (root->right) {
                if (find(root->right, reversed, res)) {
                    return true;
                }
            }
            return false;
        } else {
            if (root->right) {
                if (find(root->right, reversed, res)) {
                    return true;
                }
            }
            
            if (*res == NULL) {
                *res = root;
            } else if ((*res)->val < root->val) {
                return true;
            } else {
                *res = root;
            }
            
            if (root->left) {
                if (find(root->left, reversed, res)) {
                    return true;
                }
            }
            return false;
        }
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    TreeNode root(1);
    root.left = new TreeNode(3);
    root.right = new TreeNode(2);

    // TODO: add return type and paramters.
    clock_t tstart = clock();
    recoverTree::Solution().recoverTree_morrais(&root);
    cout << clock() - tstart << endl;
    return 0;
}
//*/
