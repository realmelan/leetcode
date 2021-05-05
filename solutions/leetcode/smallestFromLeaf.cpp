// smallestFromLeaf.cpp
// leetcode
//
// Created by  Song Ding on 5/17/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace smallestFromLeaf {
/*
// TODO: copy problem statement here
 988. Smallest String Starting From Leaf
 Medium
 
 120
 
 19
 
 Favorite
 
 Share
 Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents 'b', and so on.
 
 Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.
 
 (As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a node that has no children.)
 
 
 
 Example 1:
 
 
 
 Input: [0,1,2,3,4,3,4]
 Output: "dba"
 Example 2:
 
 
 
 Input: [25,1,3,1,3,0,2]
 Output: "adz"
 Example 3:
 
 
 
 Input: [2,2,1,null,1,0,null,0]
 Output: "abc"
 
 
 Note:
 
 The number of nodes in the given tree will be between 1 and 8500.
 Each node in the tree will have a value between 0 and 25.
 */

class Solution {
public:
    /**
     * traversal the tree and find all possible strings that start
     * a leaf node, and choose the smallest.
     */
    string smallestFromLeaf(TreeNode* root) {
        string res;
        string path;
        smallestFromLeaf(root, path, res);
        return res;
    }

private:
    void smallestFromLeaf(TreeNode* cur, string path, string& res) {
        if (cur->left == NULL && cur->right == NULL) {
            path.insert(path.begin(), 'a' + cur->val);
            if (res.empty() || res > path) {
                res.swap(path);
            }
        } else {
            path.insert(path.begin(), 'a' + cur->val);
            if (cur->left != NULL) {
                smallestFromLeaf(cur->left, path, res);
            }
            if (cur->right != NULL) {
                smallestFromLeaf(cur->right, path, res);
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
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{0,1,2,3,4,3,4}},
        {{25,1,3,1,3,0,2}},
        {{2,2,1,INT_MAX,1,0,INT_MAX,0}}
    };

    vector< string > answers {
        "dba",
        "adz",
        "abc"
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = smallestFromLeaf::Solution().smallestFromLeaf(toTree(dp.nodeVals));
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
