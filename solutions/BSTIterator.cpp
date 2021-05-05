//
//  BSTIterator.cpp
//  leetcode
//
//  Created by Song Ding on 9/22/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace BSTIterator {
/*
// TODO: copy problem statement here
 173. Binary Search Tree Iterator
 Medium

 2814

 282

 Add to List

 Share
 Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

 Calling next() will return the next smallest number in the BST.

  

 Example:



 BSTIterator iterator = new BSTIterator(root);
 iterator.next();    // return 3
 iterator.next();    // return 7
 iterator.hasNext(); // return true
 iterator.next();    // return 9
 iterator.hasNext(); // return true
 iterator.next();    // return 15
 iterator.hasNext(); // return true
 iterator.next();    // return 20
 iterator.hasNext(); // return false
  

 Note:

 next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
 You may assume that next() call will always be valid, that is, there will be at least a next smallest number in the BST when next() is called.
*/
class BSTIterator {
    // TODO: copy function signature here
    public:
        BSTIterator(TreeNode* root) {
            cur = root;
            morris_move();
        }
        
        /** @return the next smallest number */
        int next() {
            int val = cur->val;
            move();
            return val;
        }
        
        /** @return whether we have a next smallest number */
        bool hasNext() {
            return cur;
        }
    private:
        // when to stop??
        void morris_move() {
            while (cur) {
                if (!cur->left) {
                    break;
                } else {
                    TreeNode* pred = cur->left;
                    while (pred->right != nullptr && pred->right != cur) {
                        pred = pred->right;
                    }
                    if (pred->right == cur) {
                        pred->right = nullptr;
                        break;
                    } else {
                        pred->right = cur;
                        cur = cur->left;
                    }
                }
            }
        }
        void move() {
            cur = cur->right;
            morris_move();
        }
        
        TreeNode* cur;
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
    };
    // TODO: prepare parameters here
    vector<struct param> params {
    };
    // TODO: provide expected results here
    vector<int> nodeVals{7,3,15,INT_MAX,INT_MAX,9,20};
    auto res = BSTIterator::BSTIterator(toTree(nodeVals));
    std::cout << res.next() << ","
    << res.next() << ","
    << res.hasNext() << ","
    << res.next() << ","
    << res.hasNext() << ","
    << res.next() << ","
    << res.hasNext() << ","
    << res.next() << ","
    << res.hasNext() << endl;

    return 0;
}
//*/
