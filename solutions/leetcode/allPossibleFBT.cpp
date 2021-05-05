// allPossibleFBT.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace allPossibleFBT {
/*
// TODO: copy problem statement here
 894. All Possible Full Binary Trees
 Medium
 
 400
 
 34
 
 Favorite
 
 Share
 A full binary tree is a binary tree where each node has exactly 0 or 2 children.
 
 Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one possible tree.
 
 Each node of each tree in the answer must have node.val = 0.
 
 You may return the final list of trees in any order.
 
 
 
 Example 1:
 
 Input: 7
 Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
 Explanation:
 
 
 
 Note:
 
 1 <= N <= 20
 */

class Solution {
public:
    /**
     * recursive
     */
    vector<TreeNode*> allPossibleFBT(int N) {
        vector<TreeNode*> res;
        if (N%2 == 0) {
            return res;
        } else if (N == 1) {
            res.push_back(new TreeNode(0));
        } else {
            for (int i = 1; i < N; i += 2) {
                auto left = allPossibleFBT(i);
                auto right = allPossibleFBT(N-1-i);
                
                for (auto l : left) {
                    for (auto r : right) {
                        TreeNode* c = new TreeNode(0);
                        c->left = l;
                        c->right = r;
                        res.push_back(c);
                    }
                }
            }
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int N;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {7}
    };

    vector< vector<vector<int>> > answers {
        {{0,0,0,INT_MAX,INT_MAX,0,0,INT_MAX,INT_MAX,0,0},{0,0,0,INT_MAX,INT_MAX,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,INT_MAX,INT_MAX,INT_MAX,INT_MAX,0,0},{0,0,0,0,0,INT_MAX,INT_MAX,0,0}}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = allPossibleFBT::Solution().allPossibleFBT(dp.N);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
